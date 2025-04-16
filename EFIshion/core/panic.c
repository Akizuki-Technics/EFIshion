#include "panic.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/GraphicsOutput.h>

// 进入Panic模式，显示错误信息
EFI_STATUS EFIAPI PanicMode() {
    EFI_STATUS Status;

    // 清空屏幕
    Status = ClearScreen();
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // 显示Panic信息
    Status = ShowPanicMessage(EFI_ABORTED);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // 等待用户按键
    return WaitForKeyPress();
}

// 显示Panic错误消息
EFI_STATUS EFIAPI ShowPanicMessage(EFI_STATUS Status) {
    // 这里的`Print`函数是用于输出信息的
    Print(L"EFIshion Panic Mode: %r\n", Status);
    Print(L"Your EFIshion has encountered an error and needs to be fixed.\n");
    Print(L"If this is the first time you see this screen, you can upload the latest log at 'EFIshion config' in your OS.\n");
    Print(L"To continue booting your system, EFIshion will load the next boot selection for you.\n");
    Print(L"Press any key to continue...\n");

    return EFI_SUCCESS;
}

// 等待用户按键，按下任意键继续
EFI_STATUS EFIAPI WaitForKeyPress() {
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;

    // 等待按键
    Status = gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &Key);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // 用户按下任何键后继续
    return EFI_SUCCESS;
}

// 清空屏幕内容（如果需要）
EFI_STATUS ClearScreen() {
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput;

    // 获取图形输出协议
    Status = gBootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GraphicsOutput);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // 清屏：设定背景为纯黑色
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL BlackPixel = {0, 0, 0, 0};
    Status = GraphicsOutput->Blt(GraphicsOutput, &BlackPixel, EfiBltVideoFill, 0, 0, 0, 0, 800, 600, 0);
    return Status;
}
