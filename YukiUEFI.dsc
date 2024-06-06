##  @file
# YukiUEFI Package
#
# Copyright (c) 2007 - 2021, Intel Corporation. All rights reserved.<BR>
# Copyright (c) 2018 - 2020, Arm Limited. All rights reserved.<BR>
# Copyright (c) 2020, Hewlett Packard Enterprise Development LP. All rights reserved.<BR>
#
#    SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

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
  GCC:*_*_*_CC_FLAGS     = -nostdinc -nostdlib -I${HOME}/edk2/YukiPkg/Libs/libc/StdLib/Include -I${HOME}/edk2/YukiPkg/Libs/libc/StdLib/Include/X64 -I${HOME}/edk2/YukiPkg/Libs/libjpeg-turbo -D_BASETSD_H_=1 -DBITS_IN_JSAMPLE=8

[Components]
#  YukiPkg/Application/HelloWorld/HelloWorld.infwhe
  YukiPkg/Application/YukiLoader/YukiLoader.inf
  