#include "EFIFS.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/FileSystemVolumeLabelInfo.h>
#include <Protocol/DevicePathToText.h>
#include <Library/DevicePathLib.h>
#include <Guid/FileInfo.h>
#include <Guid/FileSystemInfo.h>

EFI_HANDLE DiskDrives[26]={0};
UINTN DiskCount=0;
EFI_FILE_HANDLE DiskRoot[26]={0};
void* OpenedDir=0;
int DirIndex=0;
DirFilePTR *DirFiles;
int FileMaxCount=0;


CHAR16 *LibStrDuplicate(IN CHAR16 *Src)
{
  CHAR16  *Dest;
  UINTN   Size;

  Size = StrSize (Src);
  Dest = AllocateZeroPool (Size);
  
  if (Dest != NULL) {
    CopyMem (Dest, Src, Size);
  }

  return Dest;
}

EFI_FILE_HANDLE LibOpenRoot(IN EFI_HANDLE DeviceHandle)
{
  EFI_STATUS                       Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *Volume;
  EFI_FILE_HANDLE                  File;

  File = NULL;

  //
  // File the file system interface to the device
  //
  Status = gBS->HandleProtocol (
                  DeviceHandle,
                  &gEfiSimpleFileSystemProtocolGuid,
                  (VOID *)&Volume
                  );

  //
  // Open the root directory of the volume
  //
  if (!EFI_ERROR (Status)) {
    Status = Volume->OpenVolume (
                       Volume,
                       &File
                       );
  }

  //
  // Done
  //
  return EFI_ERROR (Status) ? NULL : File;
}

CHAR16 *LibDevicePathToStr(IN EFI_DEVICE_PATH_PROTOCOL *DevPath)
{
  EFI_STATUS                        Status;
  CHAR16                            *ToText;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL  *DevPathToText;

  if (DevPath == NULL) {
    return NULL;
  }

  Status = gBS->LocateProtocol (
                  &gEfiDevicePathToTextProtocolGuid,
                  NULL,
                  (VOID **)&DevPathToText
                  );

  if(Status == EFI_SUCCESS)
  {
    ToText = DevPathToText->ConvertDevicePathToText (
                              DevPath,
                              FALSE,
                              TRUE
                              );
  
  }
  else
  {
    ToText=L"";
  }
  return ToText;
}

VOID *LibFileInfo(IN EFI_FILE_HANDLE FHand, IN EFI_GUID *InfoType)
{
  EFI_STATUS     Status;
  EFI_FILE_INFO  *Buffer;
  UINTN          BufferSize;

  Buffer     = NULL;
  BufferSize = 0;

  Status = FHand->GetInfo (
                    FHand,
                    InfoType,
                    &BufferSize,
                    Buffer
                    );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    Buffer = AllocatePool (BufferSize);
    
  }

  Status = FHand->GetInfo (
                    FHand,
                    InfoType,
                    &BufferSize,
                    Buffer
                    );

  return Buffer;
}

EFI_STATUS LibFindFiles(IN EFI_FILE_HANDLE FileHandle, IN UINT16 *FileName, IN EFI_HANDLE DeviceHandle)
{
  EFI_FILE_INFO  *DirInfo;
  UINTN          BufferSize;
  UINTN          DirBufferSize;
  UINTN          Pass;
  EFI_STATUS     Status;
  UINTN          OptionNumber;

  OptionNumber = 0;

  DirBufferSize = sizeof (EFI_FILE_INFO) + 1024;
  DirInfo       = AllocateZeroPool (DirBufferSize);
  if (DirInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Get all files in current directory
  // Pass 1 to get Directories
  // Pass 2 to get files that are EFI images
  //
  Status = EFI_SUCCESS;
  int k=0;
  for (Pass = 1; Pass <= 2; Pass++) {
    FileHandle->SetPosition (FileHandle, 0);
    for ( ; ;) {
      BufferSize = DirBufferSize;
      Status     = FileHandle->Read (FileHandle, &BufferSize, DirInfo);
      if (EFI_ERROR (Status) || (BufferSize == 0)) {
        Status = EFI_SUCCESS;
        break;
      }

      if ((((DirInfo->Attribute & EFI_FILE_DIRECTORY) != 0) && (Pass == 2)) ||
          (((DirInfo->Attribute & EFI_FILE_DIRECTORY) == 0) && (Pass == 1))
          )
      {
        //
        // Pass 1 is for Directories
        // Pass 2 is for file names
        //
        continue;
      }

      char *fn=malloc(sizeof(char)*1024);      
      WideStrToAsciiStr(DirInfo->FileName,fn);

      DirFilePTR ptr={fn,DirInfo->FileSize};

      DirFiles[k]=ptr;
      //Print(L"%x %a %s %a\n",k,DirFiles[k].FileName,DirInfo->FileName,DirFiles[0].FileName);
      k++;
      OptionNumber++;
      //InsertTailList (&gFileExplorerPrivate.FsOptionMenu->Head, &NewMenuEntry->Link);
    }
  }

  //gFileExplorerPrivate.FsOptionMenu->MenuNumber = OptionNumber;

//Done:
  FileMaxCount=OptionNumber;

  for(int i=0;i<FileMaxCount;i++)
  {
    //Print(L"%x=%a\n",i,DirFiles[i].FileName);
  }

  FreePool (DirInfo);

  return Status;
}

void LoadFileSystem()
{
    EFI_STATUS Status;
    EFI_HANDLE *SimpleFsHandle;
    UINT16                        *VolumeLabel;
    UINTN                         Index;
    UINTN                         OptionNumber;
    EFI_FILE_SYSTEM_VOLUME_LABEL  *Info;
    EFI_FILE_SYSTEM_INFO  *SysInfo;
    UINTN                 SysInfoSize;
    EFI_FILE_PROTOCOL     *EfiFpHandle;
    
    //LabelAppendText(label1,"","Loading File System ... ");

    Status = gBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        &DiskCount,
        &SimpleFsHandle
        );

    
    //LabelAppendText(label1,"",Status == EFI_SUCCESS ? "SUCCESS": "FAILED");
    //LabelAppendText(label1,"","\n");

    if (!EFI_ERROR (Status)) {
        //
        // Find all the instances of the File System prototocol
        //
        for (Index = 0; Index < DiskCount || Index==26; Index++) {
            //
            // Allocate pool for this load option
            //
            EFI_FILE_HANDLE FileHandle;
            CHAR16* HelpString;
            CHAR16* FileName;
            //EFI_DEVICE_PATH_PROTOCOL *DevicePath;


            DiskDrives[Index] = SimpleFsHandle[Index];
            FileHandle   = LibOpenRoot (DiskDrives[Index]);
            if (FileHandle == NULL) {                
                continue;
            }

            HelpString   = LibDevicePathToStr (DevicePathFromHandle (DiskDrives[Index]));
            FileName   = LibStrDuplicate (L"\\");
            //DevicePath = FileDevicePath (DiskDrives[Index], FileName);            

            //
            // Get current file system's Volume Label
            //
            Info = (EFI_FILE_SYSTEM_VOLUME_LABEL *)LibFileInfo (FileHandle, &gEfiFileSystemVolumeLabelInfoIdGuid);
            if (Info == NULL) {
                VolumeLabel = L"<UNSUPPORTED>";
            } else {
                VolumeLabel = Info->VolumeLabel;
            if (*VolumeLabel == 0x0000) {
                VolumeLabel = L"<NONAME>";
            }

            char buf[1024]={0},buf2[1024]={0},buf3[1024]={0};
            WideStrToAsciiStr(HelpString,buf);
            WideStrToAsciiStr(FileName,buf2);
            WideStrToAsciiStr(VolumeLabel,buf3);

            

            SysInfo     = NULL;
            SysInfoSize = 0;
            
            EfiFpHandle=FileHandle;

            Status      = EfiFpHandle->GetInfo (
                                        EfiFpHandle,
                                        &gEfiFileSystemInfoGuid,
                                        &SysInfoSize,
                                        SysInfo
                                        );

            if (Status == EFI_BUFFER_TOO_SMALL) {
              SysInfo = AllocateZeroPool (SysInfoSize);
              Status  = EfiFpHandle->GetInfo (
                                      EfiFpHandle,
                                      &gEfiFileSystemInfoGuid,
                                      &SysInfoSize,
                                      SysInfo
                                      );           
            
            }

            if(Status == EFI_SUCCESS)
            {
              //LabelAppendUINT64(label1,"",SysInfo->VolumeSize);
              //LabelAppendText(label1,",", "TOTAL\n");
              //LabelAppendUINT64(label1,"",SysInfo->FreeSpace);
              //LabelAppendText(label1,",", "FREE\n");
              //LabelAppendUINT64(label1,"",SysInfo->Size);
              //LabelAppendText(label1,",", "SIZE\n");
              //LabelAppendUINT64(label1,"",SysInfo->BlockSize);
              //LabelAppendText(label1,",", "BLOCK\n");

              
            }

            
            if (Info != NULL) {
                FreePool (Info);
            }

            //LibFindFiles(EfiFpHandle,NULL,DiskDrives[Index]);

            //LabelAppendText(label1,"","----------------------\n");

            }

          OptionNumber++;
        }
    }

    if (DiskCount != 0) {
        FreePool (SimpleFsHandle);
    }

    //LabelAppendText(label1,"\n","BOOT DONE");

}

#if USE_LVGL

static lv_fs_drv_t fs[26]={0};

static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    //lv_fs_res_t res;

    void * f = NULL;    

    if((mode | LV_FS_MODE_RD) == LV_FS_MODE_RD) 
    {
      EFI_HANDLE dd=(EFI_HANDLE)drv->user_data;
      int pi=drv->letter-'A';

      if(dd==NULL) return NULL;
      DiskRoot[pi]=LibOpenRoot(dd);

      if(DiskRoot[pi]==NULL) return NULL;

      CHAR16 *TFP=malloc(sizeof(CHAR16)*1024);
      char PATH[1024]={0};
      strrep_const(path,"/","\\",PATH);
      AsciiStrToWideStr(PATH,TFP);

      EFI_FILE_PROTOCOL *FILE;
      EFI_STATUS Status=DiskRoot[pi]->Open(DiskRoot[pi],&FILE,TFP,EFI_FILE_MODE_READ,0);
      if(Status==EFI_SUCCESS)
      {
        //Print(L"FILE OPEN SUCCESS\n");
        //res = LV_FS_RES_OK;
        return FILE;
      }
      else
      {
        //Print(L"FILE OPEN FAILED\n");
        //res = LV_FS_RES_FS_ERR;
        return NULL;
      }
    }
    else
    {
      //Print(L"MODE NOT SUPPORTED\n");
      //res=LV_FS_RES_DENIED;
      return NULL;
    }

    return f;
}

static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    lv_fs_res_t res = LV_FS_RES_OK;   

    EFI_FILE_PROTOCOL *FP=(EFI_FILE_PROTOCOL *)file_p;

    FP->Close(FP);

    //Print(L"FILE CLOSED\n");

    return res;
}

/*
  CHAR16 BUF[1000]={0};
  UINTN size=1000ull;
  UINT64 POS=0;
  FILE->Read(FILE,&size, BUF);
  FILE->GetPosition(FILE,&POS);
  Print(L"%s\n%d\t%d\n",BUF,POS,size);
  FILE->Close(FILE);
*/


static void * fs_dir_open(lv_fs_drv_t * drv, const char * path)
{
    void * dir = NULL;
    
    EFI_HANDLE dd=(EFI_HANDLE)drv->user_data;
    int pi=drv->letter-'A';

    if(dd==NULL) return NULL;
    DiskRoot[pi]=LibOpenRoot(dd);

    if(DiskRoot[pi]==NULL) return NULL;

    CHAR16 TFP[1024]={0};
    char PATH[1024]={0};
    strrep_const(path,"/","\\",PATH);
    AsciiStrToWideStr(PATH,TFP);
    EFI_FILE_PROTOCOL *FILE;
    EFI_STATUS Status=DiskRoot[pi]->Open(DiskRoot[pi],&FILE,TFP,EFI_FILE_MODE_READ,0);
    if(Status != EFI_SUCCESS) {
      //Print(L"OPEN DIR FAILED: %s\n",TFP);
      return NULL;
    }

    dir = FILE;      
    OpenedDir=dir;
    DirIndex=-1;
    DirFiles=malloc(sizeof(DirFilePTR)*1024);
    
    //Print(L"OPENED DIR: %a:%s\n",&drv->letter,TFP);    
    return dir;
}

static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    lv_fs_res_t res = LV_FS_RES_OK;

    EFI_FILE_PROTOCOL *fp=(EFI_FILE_PROTOCOL*)file_p;

    UINTN Size=btr;

    //Print(L"READ %x BYTES BEGIN\n",btr);

    EFI_STATUS Status=fp->Read(fp,&Size,buf);

    if(Status==EFI_SUCCESS)
    {
      *br=Size & 0xFFFFFFFF;
      //Print(L"READ %d BYTES SUCCESS %x\n",Size,*br);
    }

    return res;
}

static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/

    return res;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    //Print(L"SEEK\n");
    lv_fs_res_t res = LV_FS_RES_OK;

    EFI_STATUS Status=EFI_SUCCESS;

    EFI_FILE_PROTOCOL *fp=(EFI_FILE_PROTOCOL*)file_p;

    EFI_FILE_INFO  *DirInfo;
    UINTN          BufferSize;
    UINTN          DirBufferSize;

    DirBufferSize = sizeof (EFI_FILE_INFO) + 1024;
    DirInfo       = AllocateZeroPool (DirBufferSize);
    if (DirInfo == NULL) 
    {
      return LV_FS_RES_FS_ERR;
    }

    if(Status != EFI_SUCCESS)
    {
      return LV_FS_RES_OUT_OF_MEM;
    }

    BufferSize = DirBufferSize;
    Status     = fp->GetInfo(fp,&gEfiFileInfoGuid,&BufferSize,DirInfo);

    if (Status == EFI_BUFFER_TOO_SMALL) {
      DirInfo = AllocateZeroPool (BufferSize);    
    }

    Status     = fp->GetInfo(fp,&gEfiFileInfoGuid,&BufferSize,DirInfo);

    if(Status!=EFI_SUCCESS)
    {
      //Print(L"Get File Info Failed %x\n",Status);
    }

    UINTN pos_t=pos;

    switch (whence)
    {
    case LV_FS_SEEK_SET:
      break;
    case LV_FS_SEEK_CUR:
      UINTN pos2=0;
      //EFI_STATUS Status=fp->GetPosition(fp,&pos2);
      pos_t=pos2 + pos;
    case LV_FS_SEEK_END:
      pos_t=DirInfo->FileSize;
      //Print(L"%s %d Bytes\n",DirInfo->FileName,DirInfo->FileSize);
    default:
      break;
    }

    Status=fp->SetPosition(fp,pos_t);
    if(Status==EFI_SUCCESS)
    {
      //Print(L"SEEK %d at %x SUCCESS\n",pos_t,whence);
    }    
    else
    {
      //Print(L"SEEK %x FAILED\n",pos);
    }

    return res;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    //Print(L"TELL\n");
    lv_fs_res_t res = LV_FS_RES_OK;

    EFI_FILE_PROTOCOL *fp=(EFI_FILE_PROTOCOL*)file_p;

    UINTN pos=0;

    EFI_STATUS Status=fp->GetPosition(fp,&pos);
    if(Status==EFI_SUCCESS)
    {
      //Print(L"TELL %d SUCCESS\n",pos);
      *pos_p=pos & 0xFFFFFFFF;
    }
    else
    {
      //Print(L"TELL %x FAILED\n",pos);
    }

    return res;
}

static lv_fs_res_t fs_dir_read(lv_fs_drv_t * drv, void * rddir_p, char * fn, uint32_t fn_len)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    if(DirIndex==-1)
    {
      //FIRST READ FILE LIST
      EFI_STATUS Status=LibFindFiles((EFI_FILE_HANDLE)rddir_p,NULL,(EFI_HANDLE)drv->user_data);
      if(Status != EFI_SUCCESS)
      {
        return LV_FS_RES_NOT_EX;
      }
      else
      {
        DirIndex=0;
      }
    }

    if(DirIndex < FileMaxCount)
    {
      fn=DirFiles[DirIndex].FileName;
      fn_len=lv_strlen(fn); 
      CHAR16 sfn[1024]={0};
      AsciiStrToWideStr(fn,sfn);

      DirIndex++;
      
      //Print(L"%x/%x: %a %s %s\n",DirIndex-1,FileMaxCount,fn,sfn,L"DIR READ OK");
    }
    else
    {
      fn="";
      fn_len=0;
      //Print(L"%x %s\n",DirIndex,L"DIR READ END");
    }
    
    res=LV_FS_RES_OK;
    return res;
}

static lv_fs_res_t fs_dir_close(lv_fs_drv_t * drv, void * rddir_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    OpenedDir=NULL;
    DirIndex=-1;
    FileMaxCount=0;
    realloc(DirFiles,sizeof(char*)*1024);

    //Print(L"DIR CLOSED\n");
    
    res=LV_FS_RES_OK;
    return res;
}

void RegisterLVGLFs()
{
  unsigned char LETTER='A';

  for(unsigned char i=0;i<DiskCount;i++)
  {
    
    lv_fs_drv_init(&(fs[i]));
    fs[i].letter = LETTER+i;                         /*An uppercase letter to identify the drive */
    fs[i].cache_size = 0;           /*Cache size for reading in bytes. 0 to not cache.*/

    fs[i].open_cb = fs_open;                 /*Callback to open a file */
    fs[i].close_cb = fs_close;               /*Callback to close a file */
    fs[i].read_cb = fs_read;                 /*Callback to read a file */
    fs[i].write_cb = fs_write;               /*Callback to write a file */
    fs[i].seek_cb = fs_seek;                 /*Callback to seek in a file (Move cursor) */
    fs[i].tell_cb = fs_tell;                 /*Callback to tell the cursor position  */

    fs[i].dir_open_cb = fs_dir_open;         /*Callback to open directory to read its content */
    fs[i].dir_read_cb = fs_dir_read;         /*Callback to read a directory's content */
    fs[i].dir_close_cb = fs_dir_close;       /*Callback to close a directory */

    fs[i].user_data = DiskDrives[i];             /*Any custom data if required*/

    lv_fs_drv_register(&(fs[i]));                 /*Finally register the drive*/

  }
}

void TestFs()
{
  lv_fs_dir_t dir;
  lv_fs_res_t res;
  res = lv_fs_dir_open(&dir, "B:/");
  if(res != LV_FS_RES_OK) {
    //Print(L"ERROR 1\n");
    };

  char fn[256];
  while(1) {
      res = lv_fs_dir_read(&dir, fn, sizeof(fn));
      if(res != LV_FS_RES_OK) {
          //Print(L"ERROR 2\n");
          break;
      }

      /*fn is empty, if not more files to read*/
      if(lv_strlen(fn) == 0) {
          break;
      }

      CHAR16* lfn=malloc(sizeof(CHAR16)*1024);
      AsciiStrToWideStr(fn,lfn);

      //Print(L"READ: %s\n", fn);
  }

  //Print(L"READ DONE\n");

  lv_fs_dir_close(&dir);
}

#endif

void InitEfiFs()
{
  LoadFileSystem();
  #if USE_LVGL
  RegisterLVGLFs();
  TestFs();
  #endif
}