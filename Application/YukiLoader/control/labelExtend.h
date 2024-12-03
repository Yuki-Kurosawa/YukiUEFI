/** @file
  This file is part of Yuki Loader
  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
  SPDX-License-Identifier: MIT
**/

#include <lvgl/lvgl.h>
#include <Uefi.h>

void LabelAppendText(lv_obj_t *lbl,char* split,char* text);
void LabelAppendUINT16(lv_obj_t *lbl,char* split,UINT16 num);
void LabelAppendUINT32(lv_obj_t *lbl,char* split,UINT32 num);
void LabelAppendUINT64(lv_obj_t *lbl,char* split,UINT64 num);