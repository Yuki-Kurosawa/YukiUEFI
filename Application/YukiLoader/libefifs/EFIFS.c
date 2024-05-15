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

      // if (!(((DirInfo->Attribute & EFI_FILE_DIRECTORY) != 0) /*|| LibIsSupportedFileType (DirInfo->FileName)*/)) {
      //   //
      //   // Slip file unless it is a directory entry or a .EFI file
      //   //
      //   continue;
      // }

      char fn[1024]={0};
      WideStrToAsciiStr(DirInfo->FileName,fn);
      //LabelAppendText(label1,"",fn);
      
      if((DirInfo->Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY)
      {
        //LabelAppendText(label1," ","<DIR>");
      }
      else{
        //LabelAppendUINT64(label1," ",DirInfo->FileSize);
        //LabelAppendText(label1," ","Bytes");
      }
      
      //LabelAppendText(label1,"","\n");

      //NewMenuEntry = LibCreateMenuEntry ();
      //if (NULL == NewMenuEntry) {
      //  Status = EFI_OUT_OF_RESOURCES;
      //  goto Done;
      //}

      //NewFileContext               = (FILE_CONTEXT *)NewMenuEntry->VariableContext;
      //NewFileContext->DeviceHandle = DeviceHandle;
      //NewFileContext->FileName     = LibAppendFileName (FileName, DirInfo->FileName);
      //if (NewFileContext->FileName == NULL) {
      //  LibDestroyMenuEntry (NewMenuEntry);
      //  Status = EFI_OUT_OF_RESOURCES;
      //  goto Done;
      //}

      //NewFileContext->FileHandle = FileHandle;
      //NewFileContext->DevicePath = FileDevicePath (NewFileContext->DeviceHandle, NewFileContext->FileName);
      //NewMenuEntry->HelpString   = NULL;
      //NewFileContext->IsDir      = (BOOLEAN)((DirInfo->Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY);

      // if (NewFileContext->IsDir) {
      //   BufferSize                  = StrLen (DirInfo->FileName) * 2 + 6;
      //   NewMenuEntry->DisplayString = AllocateZeroPool (BufferSize);
      //   UnicodeSPrint (
      //     NewMenuEntry->DisplayString,
      //     BufferSize,
      //     L"<%s>",
      //     DirInfo->FileName
      //     );
      // } else {
      //   NewMenuEntry->DisplayString = LibStrDuplicate (DirInfo->FileName);
      // }

      // NewMenuEntry->DisplayStringToken = HiiSetString (
      //                                      gFileExplorerPrivate.FeHiiHandle,
      //                                      0,
      //                                      NewMenuEntry->DisplayString,
      //                                      NULL
      //                                      );

      // NewFileContext->IsRoot = FALSE;

      OptionNumber++;
      //InsertTailList (&gFileExplorerPrivate.FsOptionMenu->Head, &NewMenuEntry->Link);
    }
  }

  //gFileExplorerPrivate.FsOptionMenu->MenuNumber = OptionNumber;

//Done:

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

            //LabelAppendText(label1,"","FOUND:");
            //LabelAppendText(label1," ",buf);
            //LabelAppendText(label1,",",buf2);
            //LabelAppendText(label1,",",buf3);
            //LabelAppendText(label1,"","\n");

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

            LibFindFiles(EfiFpHandle,NULL,DiskDrives[Index]);

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
