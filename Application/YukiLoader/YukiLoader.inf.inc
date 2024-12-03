### @file
#  This file is part of Yuki Loader
#  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
#  SPDX-License-Identifier: MIT
###



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

  libfunc/func.c
  libefifs/EFIFS.c
    
  windows/MsgBox.c

  Entry.c
  YukiLoaderStr.uni
  #windows/FS.c
  

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
  gEfiFileInfoGuid

