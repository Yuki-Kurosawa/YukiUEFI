#include <lvgl/lvgl.h>
#include "events.h"

#include "windows/MsgBox.h"

#ifndef LVGLINIT_H
#define LVGLINIT_H

void LVGLInitScreen();
extern lv_group_t * wg;
void Draw();

#endif
