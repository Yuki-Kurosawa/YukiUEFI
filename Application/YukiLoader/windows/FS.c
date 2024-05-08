#include "FS.h"
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

lv_obj_t * label1;
void LoadFileSystem();

void wtom(CHAR16 *w,CHAR8 *buffer)
{
	//wcstombs(buffer,w,1024);
  UnicodeStrToAsciiStrS(w,buffer,1024);
  Print(L"%a\n",buffer);
}


void ShowFS(lv_group_t * g)
{
    label1 = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_text(label1, "");
    lv_obj_set_width(label1, 1080);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 0, 0);

    LoadFileSystem();

}

/**
  Duplicate a string.

  @param Src             The source.

  @return A new string which is duplicated copy of the source.
  @retval NULL If there is not enough memory.

**/
CHAR16 *
LibStrDuplicate (
  IN CHAR16  *Src
  )
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

EFI_FILE_HANDLE
LibOpenRoot (
  IN EFI_HANDLE  DeviceHandle
  )
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

/**
  This function converts an input device structure to a Unicode string.

  @param DevPath                  A pointer to the device path structure.

  @return A new allocated Unicode string that represents the device path.

**/
CHAR16 *
LibDevicePathToStr (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
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
  
  ToText = DevPathToText->ConvertDevicePathToText (
                            DevPath,
                            FALSE,
                            TRUE
                            );
  

  return ToText;
}

/**

  Function gets the file information from an open file descriptor, and stores it
  in a buffer allocated from pool.

  @param FHand           File Handle.
  @param InfoType        Info type need to get.

  @retval                A pointer to a buffer with file information or NULL is returned

**/
VOID *
LibFileInfo (
  IN EFI_FILE_HANDLE  FHand,
  IN EFI_GUID         *InfoType
  )
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

/**
  Find files under current directory.

  All files and sub-directories in current directory
  will be stored in DirectoryMenu for future use.

  @param FileHandle    Parent file handle.
  @param FileName      Parent file name.
  @param DeviceHandle  Driver handle for this partition.

  @retval EFI_SUCCESS         Get files from current dir successfully.
  @return Other value if can't get files from current dir.

**/
EFI_STATUS
LibFindFiles (
  IN EFI_FILE_HANDLE  FileHandle,
  IN UINT16           *FileName,
  IN EFI_HANDLE       DeviceHandle
  )
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

      if (!(((DirInfo->Attribute & EFI_FILE_DIRECTORY) != 0) || LibIsSupportedFileType (DirInfo->FileName))) {
        //
        // Slip file unless it is a directory entry or a .EFI file
        //
        continue;
      }

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

Done:

  FreePool (DirInfo);

  return Status;
}


void LoadFileSystem()
{
    EFI_STATUS Status;
    UINTN NoSimpleFsHandles;
    EFI_HANDLE *SimpleFsHandle;
    UINT16                        *VolumeLabel;
    UINTN                         Index;
    UINTN                         OptionNumber;
    EFI_FILE_SYSTEM_VOLUME_LABEL  *Info;
    EFI_FILE_SYSTEM_INFO  *SysInfo;
    UINTN                 SysInfoSize;
    EFI_FILE_PROTOCOL     *EfiFpHandle;
    
    LabelAppendText(label1,"","Loading File System ... ");

    Status = gBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        &NoSimpleFsHandles,
        &SimpleFsHandle
        );

    
    LabelAppendText(label1,"",Status == EFI_SUCCESS ? "SUCCESS": "FAILED");
    LabelAppendText(label1,"","\n");

    if (!EFI_ERROR (Status)) {
        //
        // Find all the instances of the File System prototocol
        //
        for (Index = 0; Index < NoSimpleFsHandles; Index++) {
            //
            // Allocate pool for this load option
            //
            EFI_HANDLE *DeviceHandle;
            EFI_FILE_HANDLE FileHandle;
            CHAR16* HelpString;
            CHAR16* FileName;
            EFI_DEVICE_PATH_PROTOCOL *DevicePath;


            DeviceHandle = SimpleFsHandle[Index];
            FileHandle   = LibOpenRoot (DeviceHandle);
            if (FileHandle == NULL) {                
                continue;
            }

            HelpString   = LibDevicePathToStr (DevicePathFromHandle (DeviceHandle));
            FileName   = LibStrDuplicate (L"\\");
            DevicePath = FileDevicePath (DeviceHandle, FileName);

            

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
            wtom(HelpString,buf);
            wtom(FileName,buf2);
            wtom(VolumeLabel,buf3);

            LabelAppendText(label1,"","FOUND:");
            LabelAppendText(label1," ",buf);
            LabelAppendText(label1,",",buf2);
            LabelAppendText(label1,",",buf3);
            LabelAppendText(label1,"","\n");

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
              LabelAppendUINT64(label1,"",SysInfo->VolumeSize);
              LabelAppendText(label1,",", "TOTAL\n");
              LabelAppendUINT64(label1,"",SysInfo->FreeSpace);
              LabelAppendText(label1,",", "FREE\n");
              LabelAppendUINT64(label1,"",SysInfo->Size);
              LabelAppendText(label1,",", "SIZE\n");
              LabelAppendUINT64(label1,"",SysInfo->BlockSize);
              LabelAppendText(label1,",", "BLOCK\n");
            }

            
            if (Info != NULL) {
                FreePool (Info);
            }

        }


        OptionNumber++;

    }
  }

    if (NoSimpleFsHandles != 0) {
        FreePool (SimpleFsHandle);
    }

    LabelAppendText(label1,"\n","BOOT DONE");

}