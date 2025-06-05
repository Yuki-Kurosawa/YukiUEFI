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
#include "loading.h"


void frmLoading_Init()
{
	static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_LEFT);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Loading ...");
    lv_obj_set_align(label,LV_ALIGN_TOP_LEFT);
}