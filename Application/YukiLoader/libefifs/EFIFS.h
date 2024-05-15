#include <lvgl/lvgl.h>
#include "../control/labelExtend.h"
#include "../libfunc/func.h"

CHAR16 *LibStrDuplicate(IN CHAR16 *Src);
EFI_FILE_HANDLE LibOpenRoot(IN EFI_HANDLE DeviceHandle);
CHAR16 *LibDevicePathToStr(IN EFI_DEVICE_PATH_PROTOCOL *DevPath);
VOID *LibFileInfo(IN EFI_FILE_HANDLE FHand, IN EFI_GUID *InfoType);
EFI_STATUS LibFindFiles(IN EFI_FILE_HANDLE FileHandle, IN UINT16 *FileName, IN EFI_HANDLE DeviceHandle);
void LoadFileSystem();

extern EFI_HANDLE DiskDrives[26];
extern UINTN DiskCount;