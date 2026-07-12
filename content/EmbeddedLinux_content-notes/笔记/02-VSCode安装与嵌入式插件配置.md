# VS Code 安装与嵌入式开发插件配置

Visual Studio Code（简称 VS Code）是当前嵌入式开发中最流行的代码编辑器之一。它轻量、跨平台、插件生态丰富，配合合适的配置可以媲美甚至超越传统的 Keil 和 IAR 等 IDE。本章将手把手教你如何在 Ubuntu 上安装 VS Code，配置嵌入式开发所需的插件、主题与字体，并掌握项目管理与常用快捷键。

---

## 1. VS Code 在 Ubuntu 上的安装

在 Ubuntu 上安装 VS Code 有三种主流方式，推荐使用第二种（编辑器官方 apt 源），因为它能自动接收更新。

### 方式一：通过 Snap 安装（最简单）

Snap 是 Ubuntu 自带的包管理格式，一条命令即可完成安装：

```bash
sudo snap install --classic code
```

**优点**：命令最短，自动更新。
**缺点**：Snap 包的启动速度稍慢，且在某些嵌入式场景下对串口和 USB 设备的访问权限可能受限。

### 方式二：通过编辑器官方 apt 源安装（推荐）

这种方式安装的是原汁原味的编辑器官方版本，更新及时且性能最佳。

```bash
# 1. 安装依赖
sudo apt update
sudo apt install -y wget gpg

# 2. 导入某软件厂商 GPG 密钥
wget -qO- https://example.com/editor/keys/editor.asc | gpg --dearmor | sudo tee /usr/share/keyrings/editor-vendor.gpg > /dev/null

# 3. 添加某软件厂商仓库
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/editor-vendor.gpg] https://example.com/editor/repos/code stable main" | sudo tee /etc/apt/sources.list.d/vscode.list

# 4. 安装 VS Code
sudo apt update
sudo apt install -y code
```

**验证安装**：
```bash
code --version
```
终端执行 `code` 即可启动编辑器，在当前目录执行 `code .` 可以用 VS Code 打开当前目录。

### 方式三：从官网下载 .deb 包手动安装

适合网络受限或需要特定历史版本的环境。

1. 访问 [https://code.visualstudio.com/Download](https://code.visualstudio.com/Download)，选择 `.deb` 包下载。
2. 在下载目录执行：

```bash
sudo dpkg -i code_*.deb
# 如果提示依赖缺失，执行修复
sudo apt --fix-broken install
```

---

## 2. 推荐字体与主题

嵌入式开发经常需要长时间阅读代码，选择合适的字体和主题能显著减轻视觉疲劳。

### 字体推荐

| 字体名称 | 特点 | 是否包含等宽连字 |
|---------|------|----------------|
| **JetBrains Mono** | 专为开发者设计，字母区分度高，支持连字（ligatures） | 是 |
| **Cascadia Code** | 某软件厂商出品，内置 Powerline 符号，Sea 终端友好 | 是 |
| **Fira Code** | Mozilla 设计，广泛的连字支持 | 是 |
| **Source Code Pro** | Adobe 出品，字形清晰无连字，适合传统开发者 | 否 |

**安装示例 —— JetBrains Mono**：

```bash
# 方法一：通过 apt
sudo apt install -y fonts-jetbrains-mono

# 方法二：手动下载（获取最新版）
wget https://example.com/fonts/JetBrainsMono.tar.xz
mkdir -p ~/.local/share/fonts
tar -xvf JetBrainsMono.tar.xz -C ~/.local/share/fonts
fc-cache -fv
```

在 VS Code 设置中搜索 `Font Family`，填入 `'JetBrains Mono', 'Droid Sans Mono', 'monospace'`。

### 主题推荐

| 主题名称 | 适用场景 |
|---------|---------|
| **One Dark Pro** | 长期霸榜的护眼深色主题，辨识度高 |
| **Dark Default** | 通用深色风格，阅读舒适 |
| **Material Theme** | 高对比度，适合投影教学场景 |
| **Nord** | 低饱和度配色，长时间工作不易疲劳 |

在 VS Code 中按 `Ctrl+K Ctrl+T` 可以快速切换主题。

---

## 3. 必装插件清单

VS Code 的强大在于插件生态。以下是嵌入式开发的"黄金插件清单"。

### (1) C/C++（官方扩展）
- **插件 ID**：`ms-vscode.cpptools`
- **用途**：C/C++ 语言的核心支持。提供语法高亮、智能提示（IntelliSense）、代码导航（跳转定义/声明）、断点调试等功能。所有嵌入式 C 开发的基础依赖。
- **安装方式**：在扩展面板搜索 "C/C++" → 选择 某软件厂商 发布的版本安装。

### (2) C/C++ Extension Pack
- **插件 ID**：`ms-vscode.cpptools-extension-pack`
- **用途**：C/C++ 全家桶，安装后一次性获得 C/C++ IntelliSense、CMake Tools、以及调试器支持。省去逐个安装的麻烦，适合新手。

### (3) Cortex-Debug
- **插件 ID**：`marus25.cortex-debug`
- **用途**：ARM Cortex-M 系列微控制器的调试利器。支持 ST-Link、J-Link、OpenOCD、pyOCD 等多种调试器。可配置寄存器查看、外设视图、RTOS 线程查看等高级功能，是嵌入式调试不可替代的工具。

**基本配置示例（.vscode/launch.json）**：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Cortex Debug",
            "type": "cortex-debug",
            "request": "launch",
            "servertype": "openocd",
            "device": "STM32F407VG",
            "configFiles": ["board/stm32f4discovery.cfg"],
            "executable": "${workspaceFolder}/build/program.elf"
        }
    ]
}
```

### (4) ARM Assembly
- **插件 ID**：`dan-c-underwood.arm`
- **用途**：ARM 汇编语法高亮与代码补全。编写启动文件（startup_xxx.s）、汇编优化代码时必备，让汇编代码不再晦涩难读。

### (5) Chinese (Simplified) Language Pack
- **插件 ID**：`MS-CEINTL.vscode-language-pack-zh-hans`
- **用途**：VS Code 中文界面语言包。安装后界面菜单、提示信息全部显示为简体中文，降低初学者的上手门槛。

### (6) GitLens
- **插件 ID**：`eamodio.gitlens`
- **用途**：Git 历史增强工具。可以在代码行末直接看到该行是谁写的、什么时候写的、提交信息是什么。在多人协作的嵌入式项目中，快速定位代码变更原因非常实用。

### (7) Remote - SSH
- **插件 ID**：`ms-vscode-remote.remote-ssh`
- **用途**：远程开发核心插件。嵌入式开发中，代码通常在本地编辑但需要在远程 Linux 服务器或开发板上编译运行。安装此插件后，VS Code 直接通过 SSH 连接远程机器，本地界面操作远程文件，实现"本地编辑 + 远程编译"的最佳体验。

**使用要点**：
- 按下 `F1` → 输入 `Remote-SSH: Connect to Host` → 输入 `user@host-ip`。
- 连接成功后，VS Code 会在远程端自动安装插件，本地只需保留界面。

### (8) CMake / CMake Tools
- **插件 ID**：`twxs.cmake` / `ms-vscode.cmake-tools`
- **用途**：
  - `twxs.cmake`：CMake 语法高亮与代码片段。
  - `ms-vscode.cmake-tools`：CMake 项目的一键配置、编译、调试。自动检测工具链，支持 `Ctrl+F5` 一键编译，配合 Cortex-Debug 实现从编译到烧录调试的全流程。

### (9) Makefile Tools
- **插件 ID**：`ms-vscode.makefile-tools`
- **用途**：对于使用传统 Makefile 的嵌入式项目，这个插件提供语法高亮、目标列表查看、一键构建等功能。它会在侧边栏列出所有 Make 目标，点击即可执行 `make clean`、`make flash` 等常用操作。

### (10) Serial Monitor
- **插件 ID**：`ms-vscode.vscode-serial-monitor`
- **用途**：VS Code 内置的串口监视器。嵌入式开发中经常需要通过串口查看调试输出。安装后点击底部状态栏的串口图标即可选择端口和波特率（如 115200），无需再打开 minicom 或 SecureCRT 等外部工具。

**常用波特率**：9600、38400、115200、921600

### (11) Doxygen Documentation Generator
- **插件 ID**：`cschlosser.doxdocgen`
- **用途**：自动生成 Doxygen 格式的代码注释。在函数上方输入 `/**` 后回车，插件自动解析函数参数/返回值生成注释模板。良好的注释习惯对于嵌入式代码的长期维护至关重要。

---

## 4. settings.json 推荐配置

VS Code 的设置分为用户级（全局）和工作区级（项目）。以下推荐配置适用于大部分嵌入式 C/C++ 项目。

按下 `Ctrl+Shift+P` → 输入 `settings.json` → 选择"首选项：打开设置（JSON）"。

```jsonc
{
    // ─── 编辑器基础 ───
    "editor.fontFamily": "'JetBrains Mono', 'Droid Sans Mono', 'monospace'",
    "editor.fontSize": 14,
    "editor.lineHeight": 24,
    "editor.fontLigatures": true,
    "editor.tabSize": 4,
    "editor.insertSpaces": true,
    "editor.renderWhitespace": "boundary",
    "editor.minimap.enabled": true,
    "editor.rulers": [80, 120],

    // ─── 文件编码 ───
    "files.encoding": "utf8",
    "files.eol": "\n",
    "files.trimTrailingWhitespace": true,
    "files.insertFinalNewline": true,

    // ─── C/C++ 配置 ───
    "C_Cpp.clang_format_fallbackStyle": "{ BasedOnStyle: LLVM, IndentWidth: 4 }",
    "C_Cpp.default.intelliSenseMode": "gcc-x64",
    "C_Cpp.default.includePath": [
        "${workspaceFolder}/**",
        "${workspaceFolder}/Drivers/**",
        "${workspaceFolder}/Inc/**"
    ],
    "C_Cpp.autocompleteAddParentheses": true,
    "C_Cpp.errorSquiggles": "enabled",

    // ─── 终端配置 ───
    "terminal.integrated.fontFamily": "'JetBrains Mono', 'monospace'",
    "terminal.integrated.fontSize": 13,
    "terminal.integrated.defaultProfile.linux": "bash",

    // ─── CMake ───
    "cmake.configureOnOpen": true,
    "cmake.generator": "Unix Makefiles",

    // ─── Git ───
    "git.enableSmartCommit": true,
    "git.confirmSync": false,

    // ─── 文件排除（加速搜索） ───
    "files.exclude": {
        "**/.git": true,
        "**/build": true,
        "**/.vs": true
    },
    "search.exclude": {
        "**/build": true,
        "**/*.o": true,
        "**/*.elf": true,
        "**/*.hex": true
    },

    // ─── 自动保存 ───
    "files.autoSave": "onFocusChange",

    // ─── 资源管理器 ───
    "explorer.confirmDelete": false,
    "explorer.confirmDragAndDrop": false
}
```

**关键配置解释**：

| 配置项 | 作用 |
|-------|------|
| `editor.rulers` | 在 80 列和 120 列处显示竖线，提醒代码不要超出可读长度 |
| `C_Cpp.clang_format_fallbackStyle` | 基于 通用风格的代码格式化，缩进改为 4 空格（嵌入式项目惯例） |
| `files.encoding` | 强制 UTF-8 编码，避免跨平台中文乱码 |
| `files.eol` | 强制 Unix 换行符（`\n`），避免 Windows 的 `\r\n` 导致问题 |
| `files.exclude` / `search.exclude` | 排除编译产物（build、.o、.elf），让文件搜索更快速 |

---

## 5. VS Code 项目管理

嵌入式项目往往包含多个目录（源码、驱动、链接脚本、编译脚本），VS Code 的工作区机制可以很好地组织这些资源。

### 5.1 工作区（Workspace）

工作区是一个 `.code-workspace` 文件，它保存了项目级别的设置、插件配置、打开的文件列表等。

**创建方式**：
1. 打开项目文件夹 → `文件` → `将工作区另存为...` → 选择目录保存为 `项目名.code-workspace`

**工作区文件示例**（`stm32_project.code-workspace`）：

```json
{
    "folders": [
        {
            "name": "应用程序",
            "path": "."
        },
        {
            "name": "STM32 HAL 库",
            "path": "../STM32Cube_FW_F4"
        }
    ],
    "settings": {
        "editor.fontSize": 14,
        "C_Cpp.default.includePath": [
            "${workspaceFolder}/Inc",
            "${workspaceFolder}/../STM32Cube_FW_F4/Drivers/**"
        ],
        "cmake.sourceDirectory": "${workspaceFolder}"
    },
    "tasks": {
        // 任务配置见下节
    },
    "launch": {
        "configurations": [
            // 调试配置见 Cortex-Debug 章节
        ]
    }
}
```

**使用工作区的好处**：
- 同时管理多个文件夹（HAL 库放外面，应用程序放里面）
- 项目级设置互不干扰
- 打开工作区即可恢复上次编辑的所有文件

### 5.2 任务（tasks.json）配置

任务系统让编译、烧录等操作一键完成。按下 `Ctrl+Shift+B` 执行构建，`Ctrl+Shift+T` 执行测试任务。

**`.vscode/tasks.json` 示例**：

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build (Make)",
            "type": "shell",
            "command": "make",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "Clean",
            "type": "shell",
            "command": "make clean",
            "group": "build"
        },
        {
            "label": "Flash (OpenOCD)",
            "type": "shell",
            "command": "openocd -f board/stm32f4discovery.cfg -c 'program ${workspaceFolder}/build/program.elf verify reset exit'",
            "group": "none",
            "dependsOn": ["Build (Make)"]
        },
        {
            "label": "Build & Flash",
            "dependsOn": ["Flash (OpenOCD)"],
            "group": {
                "kind": "test",
                "isDefault": true
            }
        }
    ]
}
```

**任务配置要点**：
- `group.kind` 为 `"build"` 的任务可以通过 `Ctrl+Shift+B` 触发
- `dependsOn` 可以指定任务依赖关系（如先编译后烧录）
- `problemMatcher` 设为 `$gcc` 后，编译错误会显示在"问题"面板，点击即可跳转到错误行
- `presentation` 控制终端面板的行为，`reveal: "always"` 表示任务执行时始终显示终端

### 5.3 多文件夹项目实战

假设你的嵌入式项目结构如下：

```
embedded-project/
├── app/                  # 应用程序源码
├── drivers/              # 外设驱动
├── bsp/                  # 板级支持包
├── linker/               # 链接脚本
├── build/                # 编译输出
├── .vscode/              # VS Code 配置
├── Makefile
└── README.md
```

推荐的工作区打开方式：
```bash
# 直接在项目根目录启动 VS Code
code embedded-project/
```

VS Code 自动识别 `.vscode/` 目录下的 `settings.json`、`tasks.json`、`launch.json`，无需额外配置即可开箱使用。

---

## 6. 快捷键速查表

以下 15 个快捷键是嵌入式开发中最常用、最高频的操作，建议初学者优先背诵。

| 快捷键 | 作用 | 使用频率 |
|--------|------|---------|
| `Ctrl+P` | 快速打开文件（输入文件名模糊搜索） | ★★★★★ |
| `Ctrl+Shift+P` / `F1` | 打开命令面板（所有操作都能在这里找到） | ★★★★★ |
| `Ctrl+Shift+E` | 显示/聚焦资源管理器（文件树） | ★★★★ |
| `Ctrl+\`` | 打开/关闭集成终端 | ★★★★★ |
| `Ctrl+B` | 切换侧边栏显示/隐藏（扩大代码编辑区） | ★★★★ |
| `Ctrl+Shift+B` | 运行构建任务（编译项目） | ★★★★★ |
| `F5` | 启动调试 | ★★★★ |
| `F9` | 切换断点 | ★★★★ |
| `F10` | 单步跳过（逐过程） | ★★★★ |
| `F11` | 单步进入（逐语句） | ★★★★ |
| `Alt+↑/↓` | 向上/下移动当前行 | ★★★ |
| `Ctrl+D` | 选中下一个相同的词（多光标编辑） | ★★★ |
| `Ctrl+Shift+L` | 选中所有相同的词 | ★★★ |
| `Ctrl+Shift+K` | 删除当前行 | ★★★ |
| `Ctrl+Shift+F` | 在整个项目中搜索文本 | ★★★★ |

**嵌入式高频组合拳**：
1. 修改代码 → `Ctrl+S` 保存
2. `Ctrl+Shift+B` 编译
3. 看终端错误 → `Ctrl+\`` 打开终端
4. 双击错误行跳转 → `F2` 重命名符号修复

---

## 面试练习题

### 第 1 题

VS Code 在 Ubuntu 上安装后，在终端输入 `code .` 无法打开当前目录，最可能的原因是？

A. 系统缺少 Python 运行环境
B. 没有将 VS Code 的可执行文件添加到 PATH 环境变量
C. 当前目录名称包含中文字符
D. Ubuntu 不支持从终端启动 GUI 程序

**正确答案：B**

**分析**：`code` 命令需要被系统找到才能执行。如果安装时没有自动配置 PATH，shell 无法定位 `code` 可执行文件。通过 Snap 或 apt 安装通常会处理好 PATH，但手动解压安装时需要自行添加。选项 A 错误，VS Code 不依赖 Python；选项 C 错误，VS Code 支持中文目录名；选项 D 错误，Ubuntu 完全支持从终端启动 GUI。

---

### 第 2 题

以下哪个插件是调试 ARM Cortex-M 微控制器的核心依赖？

A. GitLens
B. Makefile Tools
C. Cortex-Debug
D. Serial Monitor

**正确答案：C**

**分析**：Cortex-Debug 插件专门为 ARM Cortex-M 系列 MCU 设计，支持 ST-Link、J-Link 等调试器，提供寄存器查看、外设视图等功能。GitLens 是 Git 增强工具，Makefile Tools 是构建辅助工具，Serial Monitor 是串口通信工具——它们都与 MCU 调试无直接关系。

---

### 第 3 题

在 VS Code 的 tasks.json 中，以下哪个配置项能让编译错误显示在"问题"面板中？

A. `"group": "build"`
B. `"presentation.reveal": "always"`
C. `"problemMatcher": ["$gcc"]`
D. `"dependsOn": ["Build"]`

**正确答案：C**

**分析**：`problemMatcher` 告诉 VS Code 如何解析终端输出的错误信息。`$gcc` 是内置的 GCC 编译器错误匹配器，它提取出文件路径、行号、错误等级和描述，显示在"问题"面板并支持点击跳转。`group` 决定任务归类，`presentation` 控制终端面板行为，`dependsOn` 设置任务依赖——三者都不涉及错误解析。

---

### 第 4 题

嵌入式项目中，以下哪项 VS Code 工作区配置可以**同时管理多个目录**（如应用程序源码和 HAL 库）？

A. 在 settings.json 中设置 `"files.encoding": "utf8"`
B. 在 launch.json 中添加多个调试配置
C. 在 .code-workspace 文件的 `folders` 数组中列出多个路径
D. 在 C_Cpp 插件中设置多个 IntelliSense 模式

**正确答案：C**

**分析**：`.code-workspace` 工作区文件的 `folders` 数组支持列出多个不同路径的目录，每个目录可以指定显示名称，从而在同一个 VS Code 窗口中管理分散的代码资源。其他选项：A 仅设置编码格式；B 仅配置调试器；D 仅配置智能提示引擎——都与多目录管理无关。

---

### 第 5 题

VS Code 中，以下哪个快捷键组合用于**在工作区内所有文件中搜索文本**？

A. `Ctrl+P`
B. `Ctrl+Shift+F`
C. `Ctrl+Shift+B`
D. `Ctrl+\``

**正确答案：B**

**分析**：`Ctrl+Shift+F` 打开搜索视图，支持正则表达式和文件排除规则，在整个工作区中搜索匹配的文本内容。`Ctrl+P` 是快速打开文件（按文件名搜索）；`Ctrl+Shift+B` 是运行构建任务；`Ctrl+\`` 是切换终端面板。搜索代码中的函数调用、宏定义、全局变量时，`Ctrl+Shift+F` 是最常用的快捷键之一。
