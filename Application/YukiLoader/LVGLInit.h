/** @file
  This file is part of Yuki Loader
  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
  SPDX-License-Identifier: MIT
**/

#include <lvgl/lvgl.h>
#include "events.h"

#include "control/MsgBox.h"

#ifndef LVGLINIT_H
#define LVGLINIT_H

void LVGLInitScreen(int32_t width, int32_t height);
extern lv_group_t * wg;
void Draw();

#endif
