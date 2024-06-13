#include "labelExtend.h"

void LabelAppendText(lv_obj_t *lbl,char* split,char* text)
{
    char before[102400];
    memset(before,0,sizeof(before));
    lv_strcpy(before,lv_label_get_text(lbl));
    lv_label_set_text_fmt(lbl,"%s%s%s",before,split,text);
}

void LabelAppendUINT16(lv_obj_t *lbl,char* split,UINT16 num)
{
    char before[102400];
    memset(before,0,sizeof(before));
    lv_strcpy(before,lv_label_get_text(lbl));
    lv_label_set_text_fmt(lbl,"%s%s%u",before,split,num);
}

void LabelAppendUINT32(lv_obj_t *lbl,char* split,UINT32 num)
{
    char before[102400];
    memset(before,0,sizeof(before));
    lv_strcpy(before,lv_label_get_text(lbl));
    lv_label_set_text_fmt(lbl,"%s%s%u",before,split,num);
}

void LabelAppendUINT64(lv_obj_t *lbl,char* split,UINT64 num)
{
    char before[102400];
    memset(before,0,sizeof(before));
    lv_strcpy(before,lv_label_get_text(lbl));
    lv_label_set_text_fmt(lbl,"%s%s%llu",before,split,num);
}
