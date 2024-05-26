/** @file
  This sample application bases on HelloWorld PCD setting
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __LVGL_DXE_H__
#define __LVGL_DXE_H__
#include "LVGLInit.h"
#endif

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

#include "libefifs/EFIFS.h"
//#include <stdlib.h>
//#include <string.h>
#include "lvgl/src/others/file_explorer/lv_file_explorer.h"


extern EFI_BOOT_SERVICES         *gBS;
extern EFI_SYSTEM_TABLE			 *gST;
extern EFI_RUNTIME_SERVICES 	 *gRT;

extern EFI_HANDLE				 gImageHandle;

static EFI_GUID GraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
static EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput = NULL;

void RegisterFS();
static lv_fs_drv_t fs;

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

  EFI_STATUS Status;

    Status = gBS->LocateProtocol(&GraphicsOutputProtocolGuid, NULL, (VOID **) &GraphicsOutput);
    if (EFI_ERROR(Status)) {
        GraphicsOutput = NULL;
		Print(L"Loading Graphics_Output_Protocol error!\n");
		return EFI_SUCCESS;
	}	

	Print(L"Max mode     =[%d] \n",GraphicsOutput->Mode->MaxMode);
	Print(L"Current mode =[%d] \n",GraphicsOutput->Mode->Mode);
	Print(L"Version      =[%d] \n",GraphicsOutput->Mode->Info->Version);
	Print(L"Screen Width =[%d] \n",GraphicsOutput->Mode->Info->HorizontalResolution);
	Print(L"Screen height=[%d] \n",GraphicsOutput->Mode->Info->VerticalResolution);
	Print(L"Format       =[%d] \n",GraphicsOutput->Mode->Info->PixelFormat);
	Print(L"Num of pixel =[%d] \n",GraphicsOutput->Mode->Info->PixelsPerScanLine);

  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION * info;
  UINTN Size;

  for(int i=0;i<GraphicsOutput->Mode->MaxMode;i++)
  {
    Status=GraphicsOutput->QueryMode(GraphicsOutput,i,&Size,&info);
    Print(L"%d Screen Size : [%d * %d] \n",i+1,info->HorizontalResolution,info->VerticalResolution);
  }

  //return EFI_SUCCESS;  

  LVGLInitScreen();
  //ShowMsgBox(wg,"Hello World!","Message");
  //ShowFS(wg);
  InitEfiFs();
  //RegisterFS();
  lv_example_file_explorer_1();
  Evt_Exit();
  return EFI_SUCCESS;
}

bool ready(lv_fs_drv_t *drv)
{
  return true;
}

void RegisterFS()
{
  lv_fs_drv_init(&fs);
  fs.letter = 'A';                         /*An uppercase letter to identify the drive */
  fs.cache_size = 0;           /*Cache size for reading in bytes. 0 to not cache.*/

  fs.ready_cb = ready;               /*Callback to tell if the drive is ready to use */
  fs.open_cb = NULL;                 /*Callback to open a file */
  fs.close_cb = NULL;               /*Callback to close a file */
  fs.read_cb = NULL;                 /*Callback to read a file */
  fs.write_cb = NULL;               /*Callback to write a file */
  fs.seek_cb = NULL;                 /*Callback to seek in a file (Move cursor) */
  fs.tell_cb = NULL;                 /*Callback to tell the cursor position  */

  fs.dir_open_cb = NULL;         /*Callback to open directory to read its content */
  fs.dir_read_cb = NULL;         /*Callback to read a directory's content */
  fs.dir_close_cb = NULL;       /*Callback to close a directory */

  fs.user_data = NULL;             /*Any custom data if required*/

  lv_fs_drv_register(&fs);                 /*Finally register the drive*/
}



static void file_explorer_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        const char * cur_path =  lv_file_explorer_get_current_path(obj);
        const char * sel_fn = lv_file_explorer_get_selected_file_name(obj);
        LV_LOG_USER("%s%s", cur_path, sel_fn);
    }
}

void lv_example_file_explorer_1(void)
{
    lv_obj_t * file_explorer = lv_file_explorer_create(lv_screen_active());
    lv_file_explorer_set_sort(file_explorer, LV_EXPLORER_SORT_KIND);


    /* linux */
    lv_file_explorer_open_dir(file_explorer, "A:/");

#if LV_FILE_EXPLORER_QUICK_ACCESS
    // char * envvar = "HOME";
    // char home_dir[LV_FS_MAX_PATH_LENGTH];
    // strcpy(home_dir, "A:");
    /* get the user's home directory from the HOME environment variable*/
    // strcat(home_dir, getenv(envvar));
    // LV_LOG_USER("home_dir: %s\n", home_dir);
    // lv_file_explorer_set_quick_access_path(file_explorer, LV_EXPLORER_HOME_DIR, home_dir);
    // char video_dir[LV_FS_MAX_PATH_LENGTH];
    // strcpy(video_dir, home_dir);
    // strcat(video_dir, "/Videos");
    // lv_file_explorer_set_quick_access_path(file_explorer, LV_EXPLORER_VIDEO_DIR, video_dir);
    // char picture_dir[LV_FS_MAX_PATH_LENGTH];
    // strcpy(picture_dir, home_dir);
    // strcat(picture_dir, "/Pictures");
    // lv_file_explorer_set_quick_access_path(file_explorer, LV_EXPLORER_PICTURES_DIR, picture_dir);
    // char music_dir[LV_FS_MAX_PATH_LENGTH];
    // strcpy(music_dir, home_dir);
    // strcat(music_dir, "/Music");
    // lv_file_explorer_set_quick_access_path(file_explorer, LV_EXPLORER_MUSIC_DIR, music_dir);
    // char document_dir[LV_FS_MAX_PATH_LENGTH];
    // strcpy(document_dir, home_dir);
    // strcat(document_dir, "/Documents");
    // lv_file_explorer_set_quick_access_path(file_explorer, LV_EXPLORER_DOCS_DIR, document_dir);

    lv_file_explorer_set_quick_access_path(file_explorer, LV_EXPLORER_FS_DIR, "A:/");
#endif

    lv_obj_add_event_cb(file_explorer, file_explorer_event_handler, LV_EVENT_ALL, NULL);
}



