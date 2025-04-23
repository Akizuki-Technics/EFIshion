# EFIshion 启动器项目概述

## 🧠 项目定位与目标
EFIshion 是一个面向现代化、高自定义、视觉流畅的 UEFI 启动管理器，融合 rEFInd 的多启动能力，并引入更友好和灵活的用户体验。核心目标如下：

- **高度模块化与面向对象的代码结构（使用 C/C++）**
- **自定义程度极高的主题系统（支持自定义按钮布局、图像、色调等）**
- **动态加载语言包与主题配置，支持多语言（目前为 zh_CN 和 en_US）**
- **主动与被动错误管理机制，包含非致命 Pop-Up 与 Panic 模式**
- **插件系统支持小工具扩展（如 diskpart、chkdsk、分区工具）**
- **安全模式、多级主题回退机制**
- **首次使用引导（OOBE）与配置向导**
- **基于配置缓存的快速启动机制（lastscan.ini）**
- **图形性能测试、主题制作工具、日志查看导出功能**

---

## 📁 目录结构规划

```
EFIshion/
├── config/                # 配置读取和 OOBE 引导流程
├── core/                  # 核心启动流程、启动项识别、语言处理、panic处理等
│   ├── main.c             # 主入口函数
│   ├── lang.h/.c          # 内外部语言系统
│   ├── panic.h/.c         # Panic 模块
│   └── bootflow.h/.c      # 启动流程控制与 fallback 逻辑
├── lang/                  # 外部语言包目录（可扩展语言）
├── panic/                 # 最低级错误处理支持
├── scan/                  # EFI 文件识别、启动项列表构建
├── ui/                    # GUI 绘制、用户交互与主题加载
plugins/                   # 小工具插件模块目录（如 diskpart、dism）
theme/                     # 主题目录
    ├── default/           # 默认主题
    ├── example_minimum/   # 最简 TUI 示例，仅供参考，不用于实际 fallback
    └── minimum (hardcoded) # 最简 fallback 主题，代码内嵌，不能修改
```

---

## 🎨 主题系统（Theme）

- 主题内容存放在 theme/ 下，每个子文件夹为一个主题。一个合法的主题最少需要有一个theme.ini作为TUI配置。类似于CSS，剩余的内容可以从目录中读取（如 button1.png、banner.bmp 等）
- 支持：背景图、字体文件、图标、布局配置（theme.ini）
- default 为默认主题，minimum 为硬编码的回退 TUI 样式，不提供给用户修改
- theme.ini 提供类似 CSS 的功能：按钮位置、字体大小、透明度、颜色等

### fallback 逻辑：
```
user theme => default theme =>（warning）minimum TUI => LOADER PANIC
```

---

## 🌐 多语言支持

- 内嵌语言：zh_CN / en_US
- 外部语言包路径：/lang/zh_CN.lang、/lang/en_US.lang
- 若当前语言为 zh_CN 或 en_US 且存在外部更新包，则优先加载外部语言包
- 若语言不为 zh_CN 或 en_US，尝试加载对应 .lang 文件，失败则 fallback 至 en_US 内嵌语言
- 若 fallback 失败（即语言不受支持也无 en_US 内嵌语言），则触发 panic 模式
- 内嵌语言保存在核心代码中，关键语言词条按 key 映射

---

## 💥 Panic 模式

- 最底层紧急错误处理机制
- 不使用图像与复杂 UI，保底能显示“Press any key to continue”
- 展示错误代码及提示上传日志至 EFIshion Config 工具
- Panic 也可被显式调用用于调试或引导崩溃恢复

### 非致命错误处理：
- 以 Pop-up window 的形式展示：
  - 错误信息
  - 提供 ignore / next boot / open config 选项

---

## 🔧 EFIshion Config 工具（系统内使用）

- 用于日志查看、语言包更新、主题导入/制作
- 接入 GitHub 自动检测更新并提醒
- 提供配置向导与系统重启快捷方式

---

## 🧩 插件系统（plugins）

- 可扩展的小工具，如：
  - diskpart clone
  - chkdsk 修复
  - dism 命令界面
  - 分区信息查看器
- 使用独立的 plugin 文件夹，按模块注册
- 可通过 theme.ini 定义入口按钮样式和位置

---

## 🖼 GUI 与扫描逻辑

- 主界面显示所有可用 EFI 启动项（除隐藏项）
- 提供图形选择、键盘导航、鼠标点击
- 避免如 rEFInd 扫描时的黑屏闪烁
- 支持以缓存跳过启动扫描流程，提高性能
- 启动逻辑顺序如下：

```
1. 初始化图形与字体系统
2. 检测 EFI 文件大小及结构合法性
3. 读取 config 文件（若缺失则进入 OOBE 引导）
4. 检查是否存在 lastscan.ini（用于快速启动）
5. 若无缓存，则扫描 EFI 分区构建启动项列表
6. 加载语言包与主题资源（支持 fallback）
7. 加载插件、渲染 GUI、进入主交互循环
8. 等候用户操作 / 自动倒计时选择启动项
```

---

## ✅ 技术栈概览

- **语言：C/C++（支持 OOP 模式）**
- **构建体系：基于 EDK II + GCC 或 VS 编译链**
- **目标格式：.efi PE/COFF 可执行文件**
- **图形渲染：GOP + 自定义 GUI 渲染系统（位图、字体解析）**
- **配置文件：.ini 解析、.lang 映射文本语言包**

---

> 所有功能均支持模块化拓展与配置覆盖，核心为用户友好与系统灵活性。
> 此文档结构已存档为永久开发参考。
