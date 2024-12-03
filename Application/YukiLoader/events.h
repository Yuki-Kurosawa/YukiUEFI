/** @file
  This file is part of Yuki Loader
  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
  SPDX-License-Identifier: MIT
**/

#include <lvgl/lvgl.h>

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

void my_disp_flush(lv_display_t * disp, const lv_area_t * area, lv_color32_t * color32_p);
void Evt_Exit();
lv_indev_t * lv_uefi_keyboard_create(void);

EFI_STATUS
EFIAPI
EfiMouseInit (
  VOID
  );

lv_indev_t * lv_uefi_mouse_create(lv_display_t * disp);