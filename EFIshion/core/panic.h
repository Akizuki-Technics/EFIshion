#ifndef _EFI_PANIC_H_
#define _EFI_PANIC_H_

#include <Uefi.h>

// 进入Panic模式，显示错误信息
EFI_STATUS EFIAPI PanicMode();

// 显示Panic错误消息
EFI_STATUS EFIAPI ShowPanicMessage(EFI_STATUS Status);

// 显示提示信息，让用户按键继续
EFI_STATUS EFIAPI WaitForKeyPress();

#endif
