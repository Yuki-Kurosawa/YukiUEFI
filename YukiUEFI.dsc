### @file
#  This file is part of Yuki Loader
#  Copyright (C) 2024 Yuki Kurosawa. All Rights Reserved <BR/>
#  SPDX-License-Identifier: MIT
###



[Defines]
  PLATFORM_NAME                  = YukiUEFI
  PLATFORM_GUID                  = 28D5A65A-BAC5-48B2-8E60-4C8CF03716C1
  PLATFORM_VERSION               = 1.02
  DSC_SPECIFICATION              = 0x00010006
  OUTPUT_DIRECTORY               = Build/YukiPkg
  SUPPORTED_ARCHITECTURES        = IA32|X64|EBC|ARM|AARCH64|RISCV64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

!include MdePkg/MdeLibs.dsc.inc

[LibraryClasses]
  #
  # Entry point
  #
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  
  #
  # Basic
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  PciSegmentLib|MdePkg/Library/BasePciSegmentLibPci/BasePciSegmentLibPci.inf
  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  SortLib|MdeModulePkg/Library/BaseSortLib/BaseSortLib.inf

  #
  # UEFI & PI
  #
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  PeiServicesTablePointerLib|MdePkg/Library/PeiServicesTablePointerLib/PeiServicesTablePointerLib.inf
  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf
  UefiBootManagerLib|MdeModulePkg/Library/UefiBootManagerLib/UefiBootManagerLib.inf
  VariablePolicyLib|MdeModulePkg/Library/VariablePolicyLib/VariablePolicyLib.inf

  #
  # Generic Modules
  #
  UefiUsbLib|MdePkg/Library/UefiUsbLib/UefiUsbLib.inf
  UefiScsiLib|MdePkg/Library/UefiScsiLib/UefiScsiLib.inf
  SecurityManagementLib|MdeModulePkg/Library/DxeSecurityManagementLib/DxeSecurityManagementLib.inf
  TimerLib|MdePkg/Library/BaseTimerLibNullTemplate/BaseTimerLibNullTemplate.inf
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  CustomizedDisplayLib|MdeModulePkg/Library/CustomizedDisplayLib/CustomizedDisplayLib.inf
  FrameBufferBltLib|MdeModulePkg/Library/FrameBufferBltLib/FrameBufferBltLib.inf

  #
  # Misc
  #
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
  DebugAgentLib|MdeModulePkg/Library/DebugAgentLibNull/DebugAgentLibNull.inf
  PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
  ResetSystemLib|MdeModulePkg/Library/BaseResetSystemLibNull/BaseResetSystemLibNull.inf
  SmbusLib|MdePkg/Library/DxeSmbusLib/DxeSmbusLib.inf
  S3BootScriptLib|MdeModulePkg/Library/PiDxeS3BootScriptLib/DxeS3BootScriptLib.inf
  CpuExceptionHandlerLib|MdeModulePkg/Library/CpuExceptionHandlerLibNull/CpuExceptionHandlerLibNull.inf
  PlatformBootManagerLib|MdeModulePkg/Library/PlatformBootManagerLibNull/PlatformBootManagerLibNull.inf
  PciHostBridgeLib|MdeModulePkg/Library/PciHostBridgeLibNull/PciHostBridgeLibNull.inf
  TpmMeasurementLib|MdeModulePkg/Library/TpmMeasurementLibNull/TpmMeasurementLibNull.inf
  AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
  VarCheckLib|MdeModulePkg/Library/VarCheckLib/VarCheckLib.inf
  FileExplorerLib|MdeModulePkg/Library/FileExplorerLib/FileExplorerLib.inf
  NonDiscoverableDeviceRegistrationLib|MdeModulePkg/Library/NonDiscoverableDeviceRegistrationLib/NonDiscoverableDeviceRegistrationLib.inf

  FmpAuthenticationLib|MdeModulePkg/Library/FmpAuthenticationLibNull/FmpAuthenticationLibNull.inf
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf
  BmpSupportLib|MdeModulePkg/Library/BaseBmpSupportLib/BaseBmpSupportLib.inf
  SafeIntLib|MdePkg/Library/BaseSafeIntLib/BaseSafeIntLib.inf
  DisplayUpdateProgressLib|MdeModulePkg/Library/DisplayUpdateProgressLibGraphics/DisplayUpdateProgressLibGraphics.inf
  VariablePolicyHelperLib|MdeModulePkg/Library/VariablePolicyHelperLib/VariablePolicyHelperLib.inf
  MmUnblockMemoryLib|MdePkg/Library/MmUnblockMemoryLib/MmUnblockMemoryLibNull.inf
  VariableFlashInfoLib|MdeModulePkg/Library/BaseVariableFlashInfoLib/BaseVariableFlashInfoLib.inf

  #Std LibC  
  ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
  FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
  SortLib|MdeModulePkg/Library/UefiSortLib/UefiSortLib.inf
  ShellCEntryLib|ShellPkg/Library/UefiShellCEntryLib/UefiShellCEntryLib.inf

  #
  # C Standard Libraries
  #
  LibC|YukiPkg/Libs/libc/StdLib/LibC/LibC.inf
  LibCType|YukiPkg/Libs/libc/StdLib/LibC/Ctype/Ctype.inf
  LibLocale|YukiPkg/Libs/libc/StdLib/LibC/Locale/Locale.inf
  LibMath|YukiPkg/Libs/libc/StdLib/LibC/Math/Math.inf
  LibSignal|YukiPkg/Libs/libc/StdLib/LibC/Signal/Signal.inf
  LibStdio|YukiPkg/Libs/libc/StdLib/LibC/Stdio/Stdio.inf
  LibStdLib|YukiPkg/Libs/libc/StdLib/LibC/StdLib/StdLib.inf
  LibString|YukiPkg/Libs/libc/StdLib/LibC/String/String.inf
  LibTime|YukiPkg/Libs/libc/StdLib/LibC/Time/Time.inf
  LibUefi|YukiPkg/Libs/libc/StdLib/LibC/Uefi/Uefi.inf
  LibWchar|YukiPkg/Libs/libc/StdLib/LibC/Wchar/Wchar.inf

# Common Utilities for Networking Libraries
  LibNetUtil|YukiPkg/Libs/libc/StdLib/LibC/NetUtil/NetUtil.inf

# Additional libraries for POSIX functionality.
  LibPosix|YukiPkg/Libs/libc/StdLib/PosixLib/PosixLib.inf   # Combines LibErr, LibGen, LibGlob, LibStringlist, GetPass into one library

  LibErr|YukiPkg/Libs/libc/StdLib/PosixLib/Err/LibErr.inf
  LibGen|YukiPkg/Libs/libc/StdLib/PosixLib/Gen/LibGen.inf
  LibGlob|YukiPkg/Libs/libc/StdLib/PosixLib/Glob/LibGlob.inf
  LibStringlist|YukiPkg/Libs/libc/StdLib/PosixLib/Stringlist/LibStringlist.inf
  LibIIO|YukiPkg/Libs/libc/StdLib/LibC/Uefi/InteractiveIO/IIO.inf

# Additional, non-standard, libraries
  LibContainer|YukiPkg/Libs/libc/StdLib/LibC/Containers/ContainerLib.inf

# Libraries for device abstractions within the Standard C Library
# Applications should not directly access any functions defined in these libraries.
  LibGdtoa|YukiPkg/Libs/libc/StdLib/LibC/gdtoa/gdtoa.inf
  DevConsole|YukiPkg/Libs/libc/StdLib/LibC/Uefi/Devices/daConsole.inf
  DevShell|YukiPkg/Libs/libc/StdLib/LibC/Uefi/Devices/daShell.inf       # DEPRECATED!  Please use DevMedia for new code.
  DevMedia|YukiPkg/Libs/libc/StdLib/LibC/Uefi/Devices/daShell.inf
  DevUtility|YukiPkg/Libs/libc/StdLib/LibC/Uefi/Devices/daUtility.inf

  LuaLib|YukiPkg/Libs/libc/AppPkg/Applications/Lua/LuaLib.inf           # Lua language library

  DevicePathLib|MdePkg/Library/UefiDevicePathLibDevicePathProtocol/UefiDevicePathLibDevicePathProtocol.inf

[LibraryClasses.common.UEFI_APPLICATION]
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  DebugLib|MdePkg/Library/UefiDebugLibStdErr/UefiDebugLibStdErr.inf
  FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf

[BuildOptions.common]
  GCC:*_*_*_CC_FLAGS     = -nostdinc -nostdlib -I${HOME}/edk2/YukiPkg/Libs/libc/StdLib/Include -I${HOME}/edk2/YukiPkg/Libs/libc/StdLib/Include/X64 -I${HOME}/edk2/YukiPkg/Libs/libjpeg-turbo -D_BASETSD_H_=1 -DBITS_IN_JSAMPLE=8 -I${HOME}/edk2/YukiPkg/Libs/libpng -I${HOME}/edk2/YukiPkg/Libs/libz -I${HOME}/edk2/YukiPkg/Libs/freetype2/include  '-DFT_CONFIG_MODULES_H=<lvgl/src/libs/freetype/ftmodule.h>' '-DFT_CONFIG_OPTIONS_H=<lvgl/src/libs/freetype/ftoption.h>' -DFT2_BUILD_LIBRARY #-I${HOME}/edk2/YukiPkg/Libs/ffmpeg -I/ffmpeg/include/libavcodec -I/ffmpeg/include/libavdevice  -I/ffmpeg/include/libavformat  -I/ffmpeg/include/libavutil  -I/ffmpeg/include/libswscale -DHAVE_FAST_64BIT=1 -DHAVE_COPYSIGN=1 -I${HOME}/edk2/YukiPkg/Libs/ffmpeg/compat/atomics/dummy -DARCH_X86=1 '-DPRId64="ld"' -DHAVE_PRAGMA_DEPRECATED=false -DFF_ENABLE_DEPRECATION_WARNINGS= -DFF_DISABLE_DEPRECATION_WARNINGS= '-DPRIu32="u"' -DHAVE_FAST_UNALIGNED=0 -DCONFIG_MEMORY_POISONING=0 '-DPRIu64="u"' '-DPRIX64="lx"' '-DNULL_IF_CONFIG_SMALL(x)=NULL'   '-DFFMPEG_CONFIGURATION=""' '-DFFMPEG_LICENSE=""' '-DPRIi64="li"' '-DPRIx64="lx"' '-DPRId32="d"' '-DSIZE_SPECIFIER="zu"' '-DPRIu16="u"' '-DPRIu8="u"' -DSUINT=unsigned '-DPRIx32="x"' -DCONFIG_ZLIB=0 '-DPRIX32="x"' '-DPTRDIFF_SPECIFIER="td"' -DHAVE_DOS_PATHS=0 -DSWS_MAX_FILTER_SIZE=256 -DHAVE_BIGENDIAN=0 -DHAVE_MMXEXT=0 -Dattribute_align_arg= -DHAVE_ALTIVEC=0 -DHAVE_MMX=0 -DHAVE_LASX=0 -DHAVE_LSX=0 -DHAVE_MMX_INLINE=0 -DHAVE_MMXEXT_INLINE=0 -DHAVE_NEON=0 -DCONFIG_SWSCALE_ALPHA=1 -DHAVE_THREADS=0 -DCONFIG_FRAME_THREAD_ENCODER=0 -DCONFIG_SMALL=0 -DCONFIG_GRAY=0 -DSUINT32=uint32_t -DCONFIG_H264_SEI=1 -DCONFIG_HEVC_SEI=0 -DCONFIG_ERROR_RESILIENCE=1 -DCONFIG_MPEGVIDEODEC=0

[Components]
#  YukiPkg/Application/HelloWorld/HelloWorld.inf
  YukiPkg/Application/YukiLoader/YukiLoader.inf
  