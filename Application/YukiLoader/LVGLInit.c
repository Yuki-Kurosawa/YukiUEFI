/** @file
  This file is part of Yuki Loader
  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
  SPDX-License-Identifier: MIT
**/

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
lv_group_t * wg;

void LVGLInitScreen(int32_t width, int32_t height)
{
    lv_init();

    lv_display_t *display = lv_display_create(width,height);

    lv_color32_t *buf1; 
	uint32_t buf_size = 4 * width * height; // 4 bytes per pixel (RGBA)
	buf1=lv_malloc(buf_size);
    lv_display_set_buffers(display, buf1, NULL, buf_size, LV_DISPLAY_RENDER_MODE_DIRECT);

    lv_display_set_flush_cb(display, (lv_display_flush_cb_t)my_disp_flush);

    lv_uefi_keyboard_create();

    if (EfiMouseInit () == EFI_SUCCESS) {
        lv_uefi_mouse_create(display);
    }

    wg = lv_group_create();
    lv_group_set_default(wg);

    lv_indev_t * indev = NULL;
    for(;;) {
        indev = lv_indev_get_next(indev);
        if(!indev) {
            break;
        }

        lv_indev_type_t indev_type = lv_indev_get_type(indev);
        if(indev_type == LV_INDEV_TYPE_KEYPAD) {
            lv_indev_set_group(indev, wg);
        }

        if(indev_type == LV_INDEV_TYPE_ENCODER) {
            lv_indev_set_group(indev, wg);
        }
    }    
    
}

void lv_example_freetype_1(void)
{
    /*Create a font*/
    lv_font_t * font = lv_freetype_font_create("A:/simhei.ttf",
                                               LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                               24,
                                               LV_FREETYPE_FONT_STYLE_NORMAL);

    if(!font) {
        LV_LOG_ERROR("freetype font create failed.");
        return;
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "欢迎");
    lv_obj_set_align(label,LV_ALIGN_TOP_LEFT);
}

void lv_example_freetype_2(void)
{
    /*Create a font*/
    lv_font_t * font = lv_freetype_font_create("A:/msmincho.ttc",
                                               LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                               24,
                                               LV_FREETYPE_FONT_STYLE_NORMAL);

    if(!font) {
        LV_LOG_ERROR("freetype font create failed.");
        return;
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "よこそ");
    lv_obj_set_align(label,LV_ALIGN_TOP_RIGHT);
}

void Draw()
{
    
    lv_example_freetype_1();
    lv_example_freetype_2();

    lv_obj_t * img = lv_image_create(lv_screen_active());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    lv_image_set_src(img, "A:/front.png");
    lv_obj_center(img);

}
