/** @file
  This file is part of Yuki Loader
  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
  SPDX-License-Identifier: MIT
**/

#include "MsgBox.h"

lv_group_t *mg;


void msgbox_event_cb(lv_event_t * e)
{
    lv_obj_t * msgbox = lv_event_get_user_data(e);

    lv_msgbox_close(msgbox);
    lv_group_focus_freeze(mg, false);
}

void ShowMsgBox(lv_group_t * g,char* msg,char* title)
{
    mg=g;

    lv_obj_t * mbox = lv_msgbox_create(NULL);
    lv_msgbox_add_title(mbox, title);
    lv_msgbox_add_text(mbox, msg);

    lv_obj_t * btn = lv_msgbox_add_footer_button(mbox, "OK");
    lv_obj_add_event_cb(btn, msgbox_event_cb, LV_EVENT_CLICKED, mbox);
    lv_group_focus_obj(btn);
    lv_obj_add_state(btn, LV_STATE_FOCUS_KEY);
    lv_group_focus_freeze(g, true);

    lv_obj_align(mbox, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * bg = lv_obj_get_parent(mbox);
    lv_obj_set_style_bg_opa(bg, LV_OPA_70, 0);
    lv_obj_set_style_bg_color(bg, lv_palette_main(LV_PALETTE_GREY), 0);
}



void ShowMsgBoxLite(lv_group_t * g,char* msg)
{
    ShowMsgBox(g,msg,"");
}