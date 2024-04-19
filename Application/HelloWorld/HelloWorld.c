/** @file
  This sample application bases on HelloWorld PCD setting
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __LVGL_DXE_H__
#define __LVGL_DXE_H__

#include "lvgl/lvgl.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#endif

#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/SimplePointer.h>
#include <Protocol/AbsolutePointer.h>

#include "lvgl/demos/lv_demos.h"

BOOLEAN  mEscExit = FALSE;



// https://github.com/lvgl/lv_web_emscripten/blob/master/mouse_cursor_icon.c
#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_MOUSE_CURSOR_ICON
#define LV_ATTRIBUTE_IMG_MOUSE_CURSOR_ICON
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_MOUSE_CURSOR_ICON uint8_t mouse_cursor_icon_map[] = {
  0x78, 0x78, 0x78, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x69, 0x69, 0x69, 0xff, 0xed, 0xed, 0xed, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x1b, 0x1b, 0x1b, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0xec, 0xec, 0xec, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xdc, 0xdc, 0xdc, 0xff, 0x16, 0x16, 0x16, 0xff, 0x75, 0x75, 0x75, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xd6, 0xd6, 0xd6, 0xff, 0x13, 0x13, 0x13, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0x11, 0x11, 0x11, 0xff, 0x87, 0x87, 0x87, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc9, 0xc9, 0xc9, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xf4, 0xf4, 0xf4, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x97, 0x97, 0x97, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xf0, 0xf0, 0xf0, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbb, 0xbb, 0xbb, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x9f, 0x9f, 0x9f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xed, 0xed, 0xed, 0xff, 0xf4, 0xf4, 0xf4, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb4, 0xb4, 0xb4, 0xff, 0x10, 0x10, 0x10, 0xff, 0xa6, 0xa6, 0xa6, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xe9, 0xe9, 0xe9, 0xff, 0xf1, 0xf1, 0xf1, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0x11, 0x11, 0x11, 0xff, 0xae, 0xae, 0xae, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xe6, 0xe6, 0xe6, 0xff, 0xed, 0xed, 0xed, 0xff, 0xf4, 0xf4, 0xf4, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa3, 0xa3, 0xa3, 0xff, 0x13, 0x13, 0x13, 0xff, 0xb4, 0xb4, 0xb4, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xe3, 0xe3, 0xe3, 0xff, 0xea, 0xea, 0xea, 0xff, 0xf1, 0xf1, 0xf1, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0x2d, 0x2d, 0x2d, 0xff, 0x0b, 0x0b, 0x0b, 0xff, 0x0b, 0x0b, 0x0b, 0xff, 0x0b, 0x0b, 0x0b, 0xff, 0x01, 0x01, 0x01, 0xff, 0x13, 0x13, 0x13, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xdf, 0xdf, 0xdf, 0xff, 0xe6, 0xe6, 0xe6, 0xff, 0xd7, 0xd7, 0xd7, 0xff, 0x9c, 0x9c, 0x9c, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0x91, 0x91, 0x91, 0xff, 0x2a, 0x2a, 0x2a, 0xff, 0x94, 0x94, 0x94, 0xff, 0xa3, 0xa3, 0xa3, 0xff, 0xa6, 0xa6, 0xa6, 0xff, 0xac, 0xac, 0xac, 0xff, 0xce, 0xce, 0xce, 0xff, 
  0x00, 0x00, 0x00, 0xff, 0xdc, 0xdc, 0xdc, 0xff, 0xcb, 0xcb, 0xcb, 0xff, 0x1f, 0x1f, 0x1f, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0xeb, 0xeb, 0xeb, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0x13, 0x13, 0x13, 0xff, 0x98, 0x98, 0x98, 0xff, 0xe5, 0xe5, 0xe5, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0x1b, 0x1b, 0x1b, 0xff, 0x4e, 0x4e, 0x4e, 0xff, 0x38, 0x38, 0x38, 0xff, 0x80, 0x80, 0x80, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0x81, 0x81, 0x81, 0xff, 0x40, 0x40, 0x40, 0xff, 0xe4, 0xe4, 0xe4, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x19, 0x19, 0x19, 0xff, 0x54, 0x54, 0x54, 0xff, 0xba, 0xba, 0xba, 0xff, 0xb1, 0xb1, 0xb1, 0xff, 0x12, 0x12, 0x12, 0xff, 0xed, 0xed, 0xed, 0xff, 0xef, 0xef, 0xef, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0x01, 0x01, 0xff, 0x5d, 0x5d, 0x5d, 0xff, 0xbe, 0xbe, 0xbe, 0xff, 0xed, 0xed, 0xed, 0x54, 0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0xff, 0x83, 0x83, 0x83, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0x40, 0x40, 0x40, 0xff, 0x76, 0x76, 0x76, 0xff, 0xec, 0xec, 0xec, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x81, 0x81, 0x81, 0xff, 0xca, 0xca, 0xca, 0xff, 0xec, 0xec, 0xec, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0xbd, 0xbd, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x45, 0x45, 0x45, 0xff, 0x14, 0x14, 0x14, 0xff, 0x91, 0x91, 0x91, 0xff, 0xf3, 0xf3, 0xf3, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb3, 0xb3, 0xb3, 0xff, 0x6f, 0x6f, 0x6f, 0xff, 0x9a, 0x9a, 0x9a, 0xff, 0xd7, 0xd7, 0xd7, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0xec, 0xec, 0x35, 0xf3, 0xf3, 0xf3, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t mouse_cursor_icon = {
  .header.cf = LV_COLOR_FORMAT_ARGB8888,
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.w = 13,
  .header.h = 21,
  .data_size = 273 * 4,
  .data = mouse_cursor_icon_map,
};


static void keypad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
  EFI_STATUS     Status;
  EFI_INPUT_KEY  ReadKey;

  Status =  gST->ConIn->ReadKeyStroke (gST->ConIn, &ReadKey);
  if (!EFI_ERROR (Status)) {
    switch (ReadKey.UnicodeChar) {
      case CHAR_CARRIAGE_RETURN:
        data->key = LV_KEY_ENTER;
        break;

      case CHAR_BACKSPACE:
        data->key = LV_KEY_BACKSPACE;
        break;

      case CHAR_NULL:
        switch (ReadKey.ScanCode) {
        case SCAN_UP:
          data->key = LV_KEY_UP;
          break;
        
        case SCAN_DOWN:
          data->key = LV_KEY_DOWN;
          break;

        case SCAN_RIGHT:
          data->key = LV_KEY_RIGHT;
          break;

        case SCAN_LEFT:
          data->key = LV_KEY_LEFT;
          break;

        case SCAN_ESC:
          data->key = LV_KEY_ESC;
          mEscExit = TRUE;
          break;

        case SCAN_DELETE:
          data->key = LV_KEY_DEL;
          break;

        case SCAN_PAGE_DOWN:
          data->key = LV_KEY_NEXT;
          break;

        case SCAN_PAGE_UP:
          data->key = LV_KEY_PREV;
          break;

        case SCAN_HOME:
          data->key = LV_KEY_HOME;
          break;

        case SCAN_END:
          data->key = LV_KEY_END;
          break;

        default:
          break;
        }
        break;

      case CHAR_LINEFEED:
      case CHAR_TAB:
        break;

      default:
        data->key = ReadKey.UnicodeChar;
        break;
    }

    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }

}


lv_indev_t * lv_uefi_keyboard_create(void)
{
    lv_indev_t * indev = lv_indev_create();
    LV_ASSERT_MALLOC(indev);
    if(indev == NULL) {
        return NULL;
    }

    lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev, keypad_read);

    return indev;
}



EFI_ABSOLUTE_POINTER_PROTOCOL  *mAbsPointer = NULL;
EFI_SIMPLE_POINTER_PROTOCOL    *mSimplePointer = NULL;

EFI_STATUS
EFIAPI
EfiMouseInit (
  VOID
  )
{
  EFI_STATUS  Status1;
  EFI_STATUS  Status2;

  Status1 = gBS->HandleProtocol(
                  gST->ConsoleInHandle,
                  &gEfiSimplePointerProtocolGuid,
                  (VOID**)&mSimplePointer
                  );

  Status2 = gBS->HandleProtocol(
                    gST->ConsoleInHandle,
                    &gEfiAbsolutePointerProtocolGuid,
                    (VOID**)&mAbsPointer
                    );

  if (EFI_ERROR (Status1) && EFI_ERROR (Status2)) {
    return EFI_UNSUPPORTED;
  } else {
    return EFI_SUCCESS;
  }

}


static void mouse_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
  EFI_STATUS                  Status = EFI_UNSUPPORTED;
  // EFI_SIMPLE_POINTER_STATE    SimpleState;
  EFI_ABSOLUTE_POINTER_STATE  AbsState;

  lv_display_t *disp = lv_indev_get_driver_data(indev_drv);

  int32_t hor_res = lv_display_get_horizontal_resolution(disp);
  int32_t ver_res = lv_display_get_vertical_resolution(disp);

  // Status = mSimplePointer->GetState (mSimplePointer, &SimpleState);

  if (mAbsPointer != NULL && !EFI_ERROR (gBS->CheckEvent (mAbsPointer->WaitForInput))) {
    Status = mAbsPointer->GetState (mAbsPointer, &AbsState);
  }

  if (!EFI_ERROR (Status)) {
    data->point.x = (AbsState.CurrentX * hor_res) / (0xFFFF + 1);
    data->point.y = (AbsState.CurrentY * ver_res) / (0xFFFF + 1);
    data->state = (AbsState.ActiveButtons & BIT0) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED; // left button
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }

  gBS->Stall (2000);

}


lv_indev_t * lv_uefi_mouse_create(lv_display_t * disp)
{
    lv_indev_t * indev = lv_indev_create();
    LV_ASSERT_MALLOC(indev);
    if(indev == NULL) {
      return NULL;
    }

    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, mouse_read);
    lv_indev_set_driver_data (indev, disp);

    LV_IMG_DECLARE(mouse_cursor_icon);
    lv_obj_t * mouse_cursor = lv_image_create(lv_screen_active());
    lv_image_set_src(mouse_cursor, &mouse_cursor_icon);
    lv_indev_set_cursor(indev, mouse_cursor);

    return indev;
}


void my_disp_flush(lv_display_t * disp, const lv_area_t * area, lv_color32_t * color32_p)
{
  EFI_GRAPHICS_OUTPUT_PROTOCOL       *GraphicsOutput;
  EFI_STATUS                         Status;
  UINTN                              Width, Heigth;

  Status = gBS->LocateProtocol (&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **) &GraphicsOutput);
  if (EFI_ERROR(Status)) {
    return;
  }

  Width = area->x2 - area->x1 + 1;
  Heigth = area->y2 - area->y1 + 1;

  Status =  GraphicsOutput->Blt (
                              GraphicsOutput,
                              (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)color32_p,
                              EfiBltBufferToVideo,
                              0,
                              0,
                              (UINTN)area->x1,
                              (UINTN)area->y1,
                              Width,
                              Heigth,
                              0
                              );


  lv_display_flush_ready(disp);
}



//
// String token ID of help message text.
// Shell supports to find help message in the resource section of an application image if
// .MAN file is not found. This global variable is added to make build tool recognizes
// that the help string is consumed by user and then build tool will add the string into
// the resource section. Thus the application can use '-?' option to show help message in
// Shell.
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_STRING_ID  mStringHelpTokenId = STRING_TOKEN (STR_HELLO_WORLD_HELP_INFORMATION);

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
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

  lv_demo_keypad_encoder();
  //lv_demo_widgets();

  while (1) {
    lv_tick_inc(5);
    lv_task_handler();
    if (mEscExit) {
      break;
    }
  }

  lv_deinit();

  gST->ConOut->ClearScreen (gST->ConOut);
  gST->ConOut->SetCursorPosition (gST->ConOut, 0, 0);

  return EFI_SUCCESS;
}
