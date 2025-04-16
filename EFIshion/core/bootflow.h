#ifndef _BOOTFLOW_H_
#define _BOOTFLOW_H_

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

// 判断是否使用快速启动（可从设置中读取）
static inline BOOLEAN
ShouldUseQuickBoot (
  VOID
  )
{
    // TODO: 实际从配置文件或变量中判断是否启用快速启动
    Print(L"[Bootflow] Checking if quick boot is enabled...\n");
    return TRUE;
}

// 读取上次扫描结果以跳过扫描
static inline EFI_STATUS
PreloadScanData (
  VOID
  )
{
    Print(L"[Bootflow] Attempting to preload last scan data...\n");

    // TODO: 读取 lastscan.ini 并解析记录
    // 模拟读取成功
    return EFI_SUCCESS;
}

// 执行完整扫描流程（如未启用快速启动）
static inline EFI_STATUS
PerformScan (
  VOID
  )
{
    Print(L"[Bootflow] Performing full boot entry scan...\n");

    // TODO: 实现扫描 UEFI 启动项、MBR 等
    return EFI_SUCCESS;
}

// 第一次使用时执行 OOBE 引导流程
static inline EFI_STATUS
StartOOBE (
  VOID
  )
{
    Print(L"[Bootflow] Starting first-time setup (OOBE)...\n");

    // TODO: 实现语言选择、主题选择、动画能力检测
    return EFI_SUCCESS;
}

// 检测动画流畅度（是否启用动态 UI）
static inline BOOLEAN
DetectSystemCapability (
  VOID
  )
{
    Print(L"[Bootflow] Testing system capability for animation...\n");

    // TODO: 简单性能测试逻辑
    return TRUE;  // 支持动画
}

// 完成引导准备，进入主 UI 或直接引导系统
static inline EFI_STATUS
FinalizeBoot (
  VOID
  )
{
    Print(L"[Bootflow] Finalizing boot and showing UI...\n");

    // TODO: 加载主题，显示启动项界面
    return EFI_SUCCESS;
}

#endif // _BOOTFLOW_H_
