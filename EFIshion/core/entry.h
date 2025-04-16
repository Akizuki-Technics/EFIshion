#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>

/**
  InitSystem - 系统初始化函数

  此函数初始化 EFIshion 所需的所有系统资源与协议，
  如图形输出、文件系统、内存分配等。此处仅作简单示例。

  @return EFI_STATUS   EFI_SUCCESS 表示初始化成功。
**/
static inline EFI_STATUS
InitSystem (
  VOID
  )
{
    // 示例：打印初始化提示信息
    Print(L"Initializing EFIshion system...\n");

    // 这里可以添加其他初始化代码，比如加载协议、设备初始化等

    return EFI_SUCCESS;
}

/**
  BootLoop - 主引导循环

  此函数进入 EFIshion 的主引导循环，显示 UI 供用户选择启动项。
  目前仅作为示例，简单等待用户按键，然后返回成功。

  @return EFI_STATUS   EFI_SUCCESS 表示成功退出引导循环。
**/
static inline EFI_STATUS
BootLoop (
  VOID
  )
{
    EFI_STATUS Status;
    UINTN WaitIndex;
    EFI_INPUT_KEY Key;

    Print(L"Entering Boot Loop...\n");
    Print(L"Press any key to exit boot loop...\n");

    // 等待键盘输入
    Status = gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, &WaitIndex);
    if (EFI_ERROR(Status)) {
        Print(L"WaitForEvent failed: %r\n", Status);
        return Status;
    }

    // 读取按键（不关心键值，此处仅作为暂停示例）
    Status = gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
    if (EFI_ERROR(Status)) {
        Print(L"ReadKeyStroke failed: %r\n", Status);
        return Status;
    }

    Print(L"Exiting Boot Loop...\n");
    return EFI_SUCCESS;
}

#endif // _ENTRY_H_
