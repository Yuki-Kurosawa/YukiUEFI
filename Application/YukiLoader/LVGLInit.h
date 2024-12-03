/** @file
  This file is part of Yuki Loader
  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
  SPDX-License-Identifier: MIT
**/

#include <lvgl/lvgl.h>
#include "events.h"

#include "windows/MsgBox.h"

#ifndef LVGLINIT_H
#define LVGLINIT_H

void LVGLInitScreen();
extern lv_group_t * wg;
void Draw();

#endif
