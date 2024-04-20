#include "LVGLInit.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/SimplePointer.h>
#include <Protocol/AbsolutePointer.h>

EFI_SIMPLE_POINTER_PROTOCOL    *mSimplePointer1 = NULL;

void LVGLInitScreen()
{
    lv_init();

    lv_display_t *display = lv_display_create(1280,800);

    static lv_color32_t buf1[1280*800];
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_FULL);

    lv_display_set_flush_cb(display, (lv_display_flush_cb_t)my_disp_flush);

    lv_uefi_keyboard_create();

    if (EfiMouseInit () == EFI_SUCCESS) {
        lv_uefi_mouse_create(display);
    }
}
