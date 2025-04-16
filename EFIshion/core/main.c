#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PrintLib.h>
#include "entry.h"
#include "bootflow.h"

EFI_STATUS EFIAPI UefiMain (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
    EFI_STATUS Status;

    // 初始化系统资源
    Status = InitSystem();
    if (EFI_ERROR(Status)) {
        Print(L"System initialization failed\n");
        return Status;
    }

    // 判断是否为首次使用
    if (IsFirstBoot()) {
        StartOOBE();  // 引导首次使用配置流程
    }

    // 判断是否使用快速启动机制
    if (ShouldUseQuickBoot()) {
        PreloadScanData();  // 快速启动：加载上次扫描结果
    } else {
        PerformScan();      // 常规启动：执行扫描
    }

    // 完成引导，进入主 UI 或直接跳转到启动项
    Status = FinalizeBoot();
    if (EFI_ERROR(Status)) {
        Print(L"Booting process failed\n");
        return Status;
    }

    return EFI_SUCCESS;
}
