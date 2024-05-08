## @file
#  Sample UEFI Application Reference EDKII Module.
#
#  This is a sample shell application that will print "UEFI Hello World!" to the
#  UEFI Console based on PCD setting.
#
#  It demos how to use EDKII PCD mechanism to make code more flexible.
#
#  Copyright (c) 2008 - 2018, Intel Corporation. All rights reserved.<BR>
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
#
##

[Defines]
  INF_VERSION                    = 0x00010005
  BASE_NAME                      = YukiLoader
  MODULE_UNI_FILE                = YukiLoader.uni
  FILE_GUID                      = DF3CCCF4-D43B-4CFF-B255-D0A661E0B2B1
  MODULE_TYPE                    = UEFI_APPLICATION
  VERSION_STRING                 = 1.0
  ENTRY_POINT                    = UefiMain

#
#  This flag specifies whether HII resource section is generated into PE image.
#
  UEFI_HII_RESOURCE_SECTION      = TRUE

#
# The following information is for reference only and not required by the build tools.
#
#  VALID_ARCHITECTURES           = IA32 X64 EBC
#

[Sources]
  LVGLInit.c
  events.c

  control/labelExtend.c
    
  windows/MsgBox.c

  Entry.c
  YukiLoaderStr.uni
  windows/FS.c
  

[Packages]
  MdePkg/MdePkg.dec
  MdeModulePkg/MdeModulePkg.dec

[LibraryClasses]
  UefiApplicationEntryPoint
  UefiLib
  PcdLib
  DevicePathLib
  BaseLib
  MemoryAllocationLib

[UserExtensions.TianoCore."ExtraFiles"]
  YukiLoaderExtra.uni

[Guids]
  gEfiFileSystemVolumeLabelInfoIdGuid
  gEfiFileSystemInfoGuid
