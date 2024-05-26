#include "../libfunc/func.h"

#define USE_LVGL 1

#if USE_LVGL
    #include <lvgl/lvgl.h>
    #include "../control/labelExtend.h"
#endif

#ifndef EFIFS_H
#define EFIFS_H

CHAR16 *LibStrDuplicate(IN CHAR16 *Src);
EFI_FILE_HANDLE LibOpenRoot(IN EFI_HANDLE DeviceHandle);
CHAR16 *LibDevicePathToStr(IN EFI_DEVICE_PATH_PROTOCOL *DevPath);
VOID *LibFileInfo(IN EFI_FILE_HANDLE FHand, IN EFI_GUID *InfoType);
EFI_STATUS LibFindFiles(IN EFI_FILE_HANDLE FileHandle, IN UINT16 *FileName, IN EFI_HANDLE DeviceHandle);
void LoadFileSystem();
void InitEfiFs();

extern EFI_HANDLE DiskDrives[26];
extern UINTN DiskCount;
extern EFI_FILE_HANDLE DiskRoot[26];

#endif
