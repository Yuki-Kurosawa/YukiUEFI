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


extern EFI_BOOT_SERVICES         *gBS;
extern EFI_SYSTEM_TABLE			 *gST;
extern EFI_RUNTIME_SERVICES 	 *gRT;

extern EFI_HANDLE				 gImageHandle;

static EFI_GUID GraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
static EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput = NULL;

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

  return EFI_SUCCESS;

  LVGLInitScreen();
  //ShowMsgBox(wg,"Hello World!","Message");
  ShowFS(wg);
  Evt_Exit();
  return EFI_SUCCESS;
}

