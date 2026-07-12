# Keil5 安装与 STM32 开发环境搭建

## 1. Keil5 简介

### 1.1 什么是 MDK-ARM

Keil MDK-ARM（Microcontroller Development Kit for ARM）是 某芯片架构厂商旗下 嵌入式工具部门推出的一款针对 ARM Cortex-M、Cortex-R 系列微控制器的集成开发环境（IDE）。Keil5 是 MDK-ARM 的第五代版本，其核心组件包括：

- **µVision IDE**：图形化的代码编辑、编译、调试界面
- **ARM Compiler 5/6**：专为 ARM 架构优化的 C/C++ 编译器
- **CMSIS 包**：ARM Cortex 微控制器软件接口标准
- **Device Packs**：各芯片厂商提供的设备支持包，包含启动文件、SVD 描述、Flash 算法等

> Keil5 采用"包管理"机制，IDE 核心与芯片支持包分离，用户按需安装对应型号的 Device Pack，这是与 Keil4 最大的区别之一。

### 1.2 与 ARM Compiler 的关系

ARM Compiler 是 Keil MDK 的底层编译器。Keil5 默认捆绑了 ARM Compiler 5（AC5，基于 ARMCC），同时也支持 ARM Compiler 6（AC6，基于 LLVM/Clang）：

| 特性 | ARM Compiler 5 (AC5) | ARM Compiler 6 (AC6) |
|------|----------------------|----------------------|
| 内核 | ARMCC | LLVM/Clang |
| C++14 支持 | 部分 | 完整 |
| 代码密度 | 优秀 | 更优 |
| 编译速度 | 较慢 | 快 2-4 倍 |
| 推荐场景 | 遗留项目迁移 | 新项目首选 |

> AC6 已成为 Keil 官方推荐的默认编译器。如果在旧项目中遇到 AC6 编译报错，可以在 Project -> Options -> Target -> ARM Compiler 中切换回 AC5。

### 1.3 在中国嵌入式行业的地位

尽管 GCC/LLVM 工具链在开源社区占据主导，Keil5 在中国嵌入式行业依然广泛使用，原因包括：

1. **高校教学惯性**：国内绝大多数电子信息/自动化专业教材使用 Keil 教学，学生毕业后自然沿用
2. **国产 MCU 生态依赖**：兆易创新（GD32）、极海（APM32）、雅特力（AT32）等国产 ARM Cortex-M 厂商的首选工具链就是 Keil
3. **商业支持完善**：Keil 提供商业许可和技术支持，企业开发流程成熟
4. **调试器兼容性**：J-Link、ST-Link、ULINK、DAP-Link 等主流调试器在 Keil 下开箱即用
5. **中间件丰富**：RTX RTOS、CMSIS-DSP、CMSIS-NN、emWin 图形库等中间件与 Keil 深度集成

> 但并不推荐学生只局限于 Keil。在 Linux 下使用 GCC + Makefile/CMake + OpenOCD 的"嵌入式开发正统"路线，才是长远发展的方向。

---

## 2. Keil5 在 Windows 上的安装

### 2.1 安装前准备

**系统要求**：
- Windows 7/8/10/11（64 位）
- 至少 2 GB 内存，推荐 8 GB
- 至少 10 GB 空闲磁盘空间
- 管理员权限

**安装包下载**：
- Keil MDK 安装包：[https://www.keil.com/demo/eval/arm.htm](https://www.keil.com/demo/eval/arm.htm)
  - 评估版有 32KB 代码大小限制，但足够学习使用
  - 注册后可免费获取 STM32 系列芯片的 License
- 各芯片厂商 Device Pack：
  - STM32F1 系列：Keil.STM32F1xx_DFP.x.x.x.pack
  - STM32F4 系列：Keil.STM32F4xx_DFP.x.x.x.pack

### 2.2 安装步骤

**第一步：安装 MDK-ARM 核心**

```
1. 以管理员身份运行 MDK535.exe（此处版本号以实际下载为准）
2. 点击 "Next" -> 勾选 "I agree to all terms"
3. 选择安装路径（建议默认 C:\Keil_v5，避免路径含中文或空格）
4. 填写用户信息（随意填写即可）
5. 等待安装完成 -> "Finish"
```

**第二步：安装 Device Pack**

方式一（推荐）：在 µVision IDE 中在线安装

```
1. 打开 Keil µVision
2. 菜单栏 -> Pack Installer
3. 在左侧 Device 列表中找到 STMicroelectronics -> STM32F1 Series
4. 点击右侧 Install/Update 按钮
5. 同样安装 STM32F4 Series 对应的 Pack
```

方式二：离线安装 `.pack` 文件

```
1. 从 Keil 官网下载对应的 .pack 文件
2. 双击 .pack 文件，Pack Installer 自动运行
3. 等待安装完成
```

**第三步：注册 License（可选）**

```
1. Keil µVision -> File -> License Management
2. 复制 Computer ID（CID）
3. 在 Keil 官网申请或购买 License
4. 将收到的 License ID Code（LIC）粘贴并点击 "Add LIC"
```

### 2.3 安装后验证

建立并运行一个简单的验证项目，确保开发环境正常工作：

```c
#include "stm32f10x.h"

int main(void)
{
    // 开启 GPIOB 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置 PB0 为推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    while (1)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
    }
}
```

点击 **Project -> Build Target (F7)**，如果编译无报错，则安装成功。

---

## 3. Keil5 在 Ubuntu 上的替代方案

嵌入式开发的主力系统是 Linux，但 Keil 本身只有 Windows 版本。以下介绍三种在 Ubuntu 上使用 Keil 的方案。

### 3.1 方案一：Wine 运行 Keil5（不推荐长期使用）

Wine 可以在 Linux 上运行 Windows 应用程序。Keil5 通过 Wine 基本可用，但存在稳定性问题。

**安装与配置**：

```bash
# 安装 Wine
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install wine wine32 wine64

# 下载 Keil MDK 的 Windows 安装包后执行
wine MDK535.exe

# 安装 Device Pack
wine PackInstaller.exe Keil.STM32F1xx_DFP.pack
```

**已知问题**：
- 调试功能（ULINK/J-Link）在 Wine 下不可用
- USB 设备识别不稳定
- 编译大项目时可能崩溃
- 界面渲染偶发异常

> 结论：Wine 方案仅适合应急时的代码编辑和编译，不适合正式开发。

### 3.2 方案二：虚拟机方案

在 Ubuntu 上安装 Windows 虚拟机，在虚拟机中运行 Keil5。这是最稳定的方案。

**推荐配置（VirtualBox / VMware Workstation）**：

| 配置项 | 推荐值 |
|--------|--------|
| 内存 | 4 GB |
| CPU 核心 | 2-4 核 |
| 磁盘 | 40 GB 动态分配 |
| USB 控制器 | USB 3.0（用于调试器直通） |
| 网络 | 桥接模式 |

**USB 调试器直通（VirtualBox 示例）**：

```bash
# 安装 VirtualBox Extension Pack（支持 USB 2.0/3.0）
# 在 VirtualBox 中挂载 Windows 虚拟机
# 虚拟机设置 -> USB -> 添加 ST-Link/J-Link 设备过滤器
```

> 优点：Keil 功能完整、调试器可用。缺点：占用资源多、文件共享需要配置。

### 3.3 方案三：Ubuntu 开发 + Windows 烧录（推荐）

这是**最推荐的混合方案**，兼顾 Linux 的开发效率和 Windows 对 Keil/SWD 调试器的硬件兼容性。

**工作流程**：

```
┌─────────────────────────────────────────────────────────┐
│                   开发工作流                             │
│                                                         │
│  编辑代码 ←─── 编译/链接 ────→ 生成 .hex/.bin ────→ 烧录  │
│     │              │               │              │      │
│     ▼              ▼               ▼              ▼      │
│   VS Code       GCC +            Makefile      Windows    │
│  (Ubuntu)    Makefile/CMake     产物输出     ST-Link Utility│
│  Clion         (Ubuntu)        (Ubuntu)      J-Flash      │
│                                                   J-Link   │
│                                                   Keil MDK │
└─────────────────────────────────────────────────────────┘
```

**具体操作步骤**：

```bash
# 1. Ubuntu 上安装 ARM GCC 工具链
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi
sudo apt install openocd st-link-tool     # 可选：烧录工具

# 2. 使用 Makefile 或 CMake 管理工程
# 3. 生成 .hex 文件后，通过以下方式烧录：
#   a) 共享给 Windows 虚拟机
#   b) 使用 Samba/NFS 共享目录
#   c) Git 在不同系统间同步

# 4. Windows 上可使用：
#   - STM32 ST-LINK Utility：烧录 .hex/.bin
#   - J-Flash：配合 J-Link 烧录
#   - Keil MDK 的 Flash 功能（虚拟机上）
```

> 此方案的核心思想：用 Linux 做"脑力活"（编码、编译、版本管理），用 Windows 做"体力活"（烧录、调试硬件）。

---

## 4. STM32CubeMX 安装与使用

### 4.1 STM32CubeMX 简介

STM32CubeMX 是 ST 官方提供的图形化 MCU 配置工具，主要功能包括：

- **MCU 选型**：芯片型号筛选、引脚兼容性对比
- **时钟树配置**：图形化配置 HSE、HLS、PLL 等时钟源
- **引脚功能分配**：拖拽式引脚功能映射，自动检查冲突
- **外设参数配置**：USART、I2C、SPI、ADC、DMA 等参数图形化配置
- **中间件配置**：FreeRTOS、FATFS、USB 等中间件集成
- **代码生成**：生成初始化 C 代码，支持多种 IDE（Keil、IAR、STM32CubeIDE）

### 4.2 安装步骤

```bash
# Step 1: 下载 STM32CubeMX
# 访问 https://www.st.com/en/development-tools/stm32cubemx.html
# 注册 ST 账号后下载安装包（需要 Java 运行环境）

# Step 2: 安装 Java 运行环境（如果尚未安装）
# https://www.java.com/download/

# Step 3: 安装 STM32CubeMX
# Windows: 运行 SetupSTM32CubeMX-x.x.x.exe
# Ubuntu:  运行 SetupSTM32CubeMX-x.x.x.linux

# Step 4: 安装固件包
# 打开 STM32CubeMX
# Help -> Manage embedded software packages
# 选择 STM32F1、STM32F4 系列并下载
```

**Ubuntu 安装注意事项**：

```bash
# 需要 64 位 JRE 或 JDK
sudo apt install default-jre

# 如果下载固件包速度慢，可以手动下载后导入：
# Help -> Manage embedded software packages -> From Local
```

### 4.3 使用 CubeMX 生成 Keil5 工程

以下以 STM32F103C8T6（蓝色小板/最小系统板）为例。

**Step 1：新建工程**

```
1. 打开 CubeMX -> New Project
2. 搜索 STM32F103C8 -> 双击选中
3. 确认芯片型号
```

**Step 2：配置时钟树**

STM32F103C8 最高主频 72MHz，典型配置如下：

```
Clock Source Configuration:
  HSE (外部晶振)  →  8 MHz
  PLL 倍频         →  x9 (= 72 MHz)
  SYSCLK           →  72 MHz
  APB1 Prescaler   →  /2 (= 36 MHz)
  APB2 Prescaler   →  /1 (= 72 MHz)
```

在 CubeMX 的 **Clock Configuration** 页面，按照以下路径拖动配置：

```
HSE (Crystal/Ceramic Resonator) → PLLSRC → PLLMUL x9 → SYSCLK
                                                      → AHB Prescaler /1
                                                         → APB1 /2 (36MHz)
                                                         → APB2 /1 (72MHz)
```

> 如果配置错误，CubeMX 会红色高亮提示，且无法生成代码。

**Step 3：配置引脚功能**

以点亮 PC13 上板载 LED 为例：

```
Pinout & Configuration 页面：
  1. 在芯片引脚图上点击 PC13
  2. 选择 GPIO_Output
  3. 在右侧 Configuration -> GPIO 中：
     - Output level: High
     - Pull-up/Pull-down: No pull-up/pull-down
     - Maximum output speed: Low
```

**Step 4：生成代码**

```
1. Project Manager 页面：
   - Project Name: MyProject
   - Project Location: 选择存放路径
   - Toolchain / IDE: MDK-ARM（Keil 5）
   - Minimum Firmware Version: V1.8.0（建议选最新）

2. Code Generator 页面：
   - 勾选 "Copy only the necessary library files"
   - 勾选 "Generate peripheral initialization as a pair of .c/.h files per peripheral"

3. 点击右上角 GENERATE CODE
```

### 4.4 CubeMX 的常用配置项

| 配置类别 | 关键配置项 | 说明 |
|----------|------------|------|
| 时钟 | RCC -> HSE | 选择 Crystal/Ceramic Resonator |
| 调试 | SYS -> Debug | 选 Serial Wire（SWD），否则 ST-Link 第二次无法连接 |
| USART | USART1 -> Mode | Asynchronous，波特率 115200 |
| GPIO | 引脚右键 | Pinout view 中可快速设定上下拉、输出速度 |
| NVIC | System Core -> NVIC | 中断优先级分组、使能/禁用中断 |

> **重要提醒**：如果生成代码后 ST-Link 无法连接（Error: Target no device found），很可能是 SYS -> Debug 没有配置为 Serial Wire，导致 GPIO 复用了 SWDIO/SWCLK 引脚。

---

## 5. Keil5 创建 STM32F103 项目（LED 闪烁）

本章节从零开始，手动创建一个 STM32F103C8T6 的 Keil5 工程，包含完整的 LED 闪烁示例。

### 5.1 新建工程

```
1. 打开 Keil µVision
2. Project -> New µVision Project...
3. 选择工程保存路径（同样避免中文路径）
4. 输入工程名：LED_Blink
5. 芯片选择：STMicroelectronics -> STM32F1 Series -> STM32F103C8
6. 弹出 "Manage Run-Time Environment" 窗口 -> 点击 Cancel
   （我们手动管理文件，便于理解工程结构）
7. 弹出 "Copy STM32 Startup Code to Project" -> 点击 Yes
   （这将自动添加启动文件 startup_stm32f103xb.s）
```

### 5.2 工程目录结构

建议的工程目录组织方式：

```
LED_Blink/
├── Core/
│   ├── inc/          # 头文件
│   │   ├── main.h
│   │   └── gpio.h
│   └── src/          # 源文件
│       ├── main.c
│       └── gpio.c
├── Drivers/
│   ├── CMSIS/         # CMSIS 核心文件
│   │   ├── core_cm3.h
│   │   └── system_stm32f10x.h
│   └── STM32F10x_StdPeriph_Driver/
│       ├── inc/       # 标准外设库头文件
│       └── src/       # 标准外设库源文件
├── startup/
│   └── startup_stm32f103xb.s
├── MDK-ARM/
│   ├── LED_Blink.uvprojx  # Keil 工程文件
│   └── ...
├── README.md
└── LED_Blink.ioc  # CubeMX 配置文件（如果使用 CubeMX）
```

### 5.3 添加源文件到工程

```
1. 在 Keil 的 Project 窗口中右键 Target 1 -> Manage Project Items
2. 创建以下 Groups：
   - Core          # main.c 等用户代码
   - Startup       # 启动文件
   - StdPeriph_Driver  # 标准外设库
3. 将下载的 STM32F10x_StdPeriph_Lib_V3.6.0 中的对应文件添加到 StdPeriph_Driver 组
4. 添加 main.c 到 Core 组
```

### 5.4 配置工程选项

点击 **Project -> Options for Target 'Target 1' (Alt+F7)**，进行以下配置：

**Target 页面：**
```
Xtal (MHz): 8.0          # 外部晶振频率
Operating system: None   # 不使用 RTOS
Use Cross-Module Optimization: 不勾选
Use MicroLIB: 勾选       # 使用 MicroLIB 减小代码体积
```

**Output 页面：**
```
Select Folder for Objects: Objects
Name of Executable: LED_Blink
Create HEX File: 勾选     # 生成 .hex 烧录文件
```

**C/C++ 页面：**
```
Preprocessor Symbols - Define:
  USE_STDPERIPH_DRIVER   # 使用标准外设库
  STM32F10X_MD           # 中等容量（F103C8 = 64KB Flash）

Include Paths:
  .\Core\inc
  .\Drivers\CMSIS
  .\Drivers\STM32F10x_StdPeriph_Driver\inc
```

**Debug 页面：**
```
Use: ST-Link Debugger
  -> Settings -> Flash Download:
     - Reset and Run: 勾选（下载后自动运行）
     - Programming Algorithm: STM32F10x Med-density Flash
```

### 5.5 编写 LED 闪烁代码

**main.c：**

```c
#include "stm32f10x.h"

void Delay(uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        for (uint32_t j = 0; j < 1000; j++)
            __NOP();
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启 GPIOC 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // 配置 PC13 为推挽输出（STM32F103C8T6 蓝色小板的板载 LED）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int main(void)
{
    GPIO_Configuration();

    while (1)
    {
        // PC13 低电平点亮 LED（开发板原理图决定）
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        Delay(1000);

        // PC13 高电平熄灭 LED
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        Delay(1000);
    }
}
```

### 5.6 编译与下载

```
编译：
  Project -> Build Target (F7)
  或 Rebuild All Target Files (Ctrl+F7 后再 F7)

下载：
  Flash -> Download (F8)

如果下载后 LED 没有闪烁，请检查：
  1. 是否勾选了 "Reset and Run"（Options -> Debug -> Flash Download）
  2. ST-Link 连接是否正确（GND, SWDIO, SWCLK, VCC）
  3. 芯片供电是否正常（3.3V）
  4. Debug 页面是否选择了正确的 Flash Algorithm
```

### 5.7 LED 延时问题改进

上例中的软件延时（Delay 函数）不精确且阻塞 CPU。在实际项目中改用 **SysTick 定时器**：

```c
#include "stm32f10x.h"

volatile uint32_t ms_counter = 0;

void SysTick_Handler(void)
{
    ms_counter++;
}

void Delay_ms(uint32_t ms)
{
    uint32_t start = ms_counter;
    while ((ms_counter - start) < ms);
}

void SysTick_Init(void)
{
    // SystemCoreClock 是 F103 的 72MHz
    // SysTick 每 1ms 中断一次
    SysTick_Config(SystemCoreClock / 1000);
}

int main(void)
{
    SysTick_Init();
    GPIO_Configuration();

    while (1)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        Delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        Delay_ms(500);
    }
}
```

---

## 6. Keil5 创建 STM32F407 项目

### 6.1 与 F103 项目的主要区别

| 对比项 | STM32F103C8T6 | STM32F407VGT6 |
|--------|---------------|---------------|
| 内核 | Cortex-M3 | Cortex-M4F（带 FPU） |
| 启动文件 | startup_stm32f103xb.s | startup_stm32f40xx.s |
| 标准外设库 | STM32F10x_StdPeriph_Lib | STM32F4xx_StdPeriph_Lib |
| 芯片选型 | STM32F103C8 | STM32F407VG |
| 主频 | 72 MHz | 168 MHz |
| FPU 配置 | 无 | 需要额外配置 |
| Flash 算法 | STM32F1x Med-density | STM32F4xx 1MB |

### 6.2 创建 F407 工程的步骤

**Step 1：新建工程**

```
1. Project -> New µVision Project...
2. 芯片选择：STMicroelectronics -> STM32F4 Series -> STM32F407VG
3. 复制启动文件（Yes）
4. 管理模式运行环境（Cancel）
```

**Step 2：配置工程选项**

Target 页面差异：

```
Xtal (MHz): 8.0
Floating Point Hardware: 选择 "Single Precision"
  或勾选 "Use FPU"（在 C/C++ 页面自动添加 __FPU_PRESENT=1 和 ARM_MATH_CM4）
Operating system: None
Use MicroLIB: 勾选
```

C/C++ 页面差异：

```
Preprocessor Symbols - Define:
  USE_STDPERIPH_DRIVER
  STM32F40XX   # F4 系列宏定义
  __FPU_PRESENT=1
  ARM_MATH_CM4

Include Paths（增加 DSP 库路径）：
  .\Core\inc
  .\Drivers\CMSIS
  .\Drivers\CMSIS\DSP\Include
  .\Drivers\STM32F4xx_StdPeriph_Driver\inc
```

**Step 3：FPU 初始化**

F407 带硬件浮点运算单元（FPU），需要在 main 函数之前启用：

```c
// 在 system_stm32f4xx.c 或 main.c 中
void FPU_Enable(void)
{
    // 设置 CPACR 寄存器，启用 CP10 和 CP11 协处理器（FPU）
    SCB->CPACR |= (0xF << 20);
}
```

通常这个功能已经在 ST 官方提供的 `system_stm32f4xx.c` 中通过宏 `__FPU_USED` 自动处理。如果使用 CubeMX 生成代码，FPU 初始化会自动包含。

**Step 4：主代码（LED 闪烁 + FPU 运算）**

```c
#include "stm32f4xx.h"

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // F407 探索者开发板 LED 在 PF9/PF10
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    // 测试 FPU 浮点运算
    float a = 1.234f;
    float b = 5.678f;
    float c;

    while (1)
    {
        c = a * b;          // 硬件 FPU 完成
        GPIO_SetBits(GPIOF, GPIO_Pin_9);
        GPIO_ResetBits(GPIOF, GPIO_Pin_10);

        for (volatile uint32_t i = 0; i < 500000; i++);

        GPIO_ResetBits(GPIOF, GPIO_Pin_9);
        GPIO_SetBits(GPIOF, GPIO_Pin_10);

        for (volatile uint32_t i = 0; i < 500000; i++);
    }
}
```

> **与 F103 的关键差异**：
> 1. F4 的 GPIO 时钟挂载在 AHB1 总线（而非 APB2）
> 2. F4 的 GPIO 初始化多出 `GPIO_OType` 和 `GPIO_PuPd` 两个参数
> 3. F4 支持硬件浮点运算，需要额外配置 FPU
> 4. F4 的启动文件和链接脚本与 F103 不同

---

## 7. Keil5 调试功能介绍

### 7.1 调试模式进入

```
1. Debug -> Start/Stop Debug Session (Ctrl+F5)
2. 连接调试器（ST-Link / J-Link）后进入调试界面
```

调试界面布局：

```
┌──────────────────────────────────────────────────────────┐
│  Toolbar: Run, Step, Step Over, Step Out, Stop           │
├──────────┬───────────────────────────────────────────────┤
│ Register │              Source Code Window                │
│  Window  │     (黄色箭头指向当前执行行)                    │
│          │                                               │
│  R0-R15  │   断点：红色圆点                                │
│  xPSR    │   当前行：黄色箭头                               │
│  MSP/PSP │                                               │
├──────────┼───────────────────────────────────────────────┤
│  Call   │              Disassembly Window                 │
│  Stack  │     (反汇编窗口，可查看编译器生成的汇编代码)       │
├──────────┼───────────────────────────────────────────────┤
│ Memory   │              Watch / Variables                  │
│ Window   │                                               │
│          │   Locals: 当前函数局部变量                        │
│          │   Watch1/2: 用户监视变量                         │
└──────────┴───────────────────────────────────────────────┘
```

### 7.2 断点（Breakpoint）

**基本断点**：在代码行号左侧双击（或右键 -> Insert Breakpoint）

**条件断点**：
```
Debug -> Breakpoints (Ctrl+B)
Examples:
  i == 100          // 当变量 i 等于 100 时触发
  (count > 10) && (flag == 0)  // 复合条件
  printf("hit\n")   // 触发时执行表达式（不停止执行）
```

**硬件断点 vs 软件断点**：
- F103/片上 Flash：最多支持 **6 个硬件断点**（FBP）
- RAM 中调试：软件断点数量不受限
- 超过硬件断点数时，Keil 会使用软件断点（仅限 RAM）

### 7.3 变量监视（Watch & Variables）

```
查看变量：在源码中选中变量 -> 右键 -> Add to Watch

Watch 窗口支持：
  1. 十进制/十六进制显示切换（右键 -> Display as Hex/Decimal）
  2. 数组展开（a[10] 展开后显示所有元素）
  3. 结构体成员查看
  4. 快速修改变量值（双击 Value 列）
```

**Watch 窗口常用表达式**：

```
*(uint32_t*)0x40010800      // 直接查看某个寄存器的值
GPIOB->ODR                  // 查看 GPIOB 输出数据寄存器
arr[0:5]                    // 查看数组前 6 个元素
myStruct.member             // 查看结构体成员
```

### 7.4 串口打印（SEGGER RTT / ITM / 半主机）

**方式一：使用半主机（Semihosting）**

半主机通过 SWD 调试接口将 printf 输出重定向到 Keil 的 Debug (printf) Viewer。

```c
// 重定向 fputc 到半主机（需要勾选 Use MicroLIB）
#include <stdio.h>

int fputc(int ch, FILE *f)
{
    // 使用 ITM 通道 0 输出
    ITM_SendChar(ch);
    return ch;
}

// 在代码中使用 printf
printf("SystemCoreClock = %d Hz\n", SystemCoreClock);
```

查看输出：**View -> Serial Windows -> Debug (printf) Viewer**

**方式二：通过 UART 硬件串口**

```c
// USART1 初始化后，重定向 fputc
int fputc(int ch, FILE *f)
{
    // 等待发送完成
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, (uint8_t)ch);
    return ch;
}
```

然后用 USB-TTL 模块连接 PC，用串口助手查看输出。

### 7.5 逻辑分析仪（Logic Analyzer）

Keil 的 Logic Analyzer 可以图形化显示变量的实时变化，无需示波器。

```
1. Debug 状态下 -> View -> Analysis Windows -> Logic Analyzer
2. 点击 Setup -> 新建信号
3. 输入信号名称（如 GPIOB->ODR 或 GPIOA->IDR）
4. 设置显示格式（Bit / Analog）
5. 点击 "Start" 或运行程序，观察波形
```

**典型应用场景**：
- 观察 PWM 占空比
- 查看 GPIO 翻转频率
- 分析 I2C/SPI 时序（简易版）

> **注意**：Logic Analyzer 的采样通过调试接口进行，会影响程序实时性。对于高频信号（如 PWM 几十 kHz），实际波形会有偏差。

### 7.6 其他实用调试技巧

| 功能 | 操作 | 用途 |
|------|------|------|
| Call Stack + Locals | 调试自动打开 | 查看函数调用栈和局部变量 |
| System Viewer | Peripherals -> System Viewer | 查看寄存器状态 |
| System Analyzer | View -> Analysis Windows | 实时查看 RTOS 任务状态 |
| Execution Profiler | Debug模式下 View -> Trace | 代码执行时间统计 |
| Parallel Watch | View -> Watch | 同时监视多组变量 |

---

## 8. 常见编译错误与解决

### 错误 1：`Error: L6218E: Undefined symbol _main`

```
错误信息：
  .\Objects\LED_Blink.axf: Error: L6218E: Undefined symbol main (referred from __rtentry2.o).

原因分析：
  链接器找不到 main 函数入口。

解决方法：
  1. 检查项目中是否有 main.c 文件（是否已添加到工程中）
  2. 检查 main 函数拼写（注意不是 mian、mian）
  3. 检查 main 函数原型：int main(void) 或 void main(void)
```

> **特别提示**：在 MicroLIB 下，main() 不需要返回值，可以写为 `int main(void)` 并在末尾添加 `return 0;`。

### 错误 2：`Error: C9555E: #error directive: "Please select first the target ...

```
错误信息：
  core_cm3.h(50): error: #error directive: "Please select first the target STM32F10x device used in your application (in stm32f10x.h file)"

原因分析：
  没有在 C/C++ 编译器选项的 Define 中定义芯片型号宏。

解决方法：
  在 Project -> Options -> C/C++ -> Preprocessor Symbols -> Define 中添加：
    USE_STDPERIPH_DRIVER, STM32F10X_MD
  注意：F103C8 是中容量（Medium Density），宏定义为 STM32F10X_MD
  F103ZE 等多型号对应不同宏：
    STM32F10X_LD  —— 低容量（16-32KB）
    STM32F10X_MD  —— 中容量（64-128KB）
    STM32F10X_HD  —— 高容量（256-512KB）
    STM32F10X_XL  —— 超大容量（768KB+）
```

### 错误 3：`Error: L6406E: Imported symbol ... in ... is not externally visible`

```
错误信息：
  Error: L6406E: Imported symbol GPIO_Init in gpio.o is not externally visible.

原因分析：
  函数声明了 static 但在其他文件中被调用，或者标准外设库的函数定义未被正确包含。

解决方法：
  1. 检查是否有 .c 文件漏添加到工程（如 stm32f10x_gpio.c 未添加）
  2. 检查函数是否使用了 static 修饰但不该有
  3. 检查函数原型和实现是否匹配
  4. 清理并重新编译：Project -> Rebuild All Target Files
```

### 错误 4：`Error: L6915E: Library reports error: __use_no_semihosting was requested`

```
错误信息：
  Error: L6915E: Library reports error: __use_no_semihosting was requested but a semihosting fgetc/fputc was referenced

原因分析：
  使用了 printf/sprintf 等标准 I/O 函数，但 MicroLIB 默认需要半主机（Semihosting）支持，而调试器未提供半主机服务时会报错。

解决方法：

方案一：重定义 fputc（推荐）：
  在项目中添加以下代码，将 printf 重定向到串口或 ITM：

  #pragma import(__use_no_semihosting)
  #include <stdio.h>

  struct __FILE { int handle; };
  FILE __stdout;

  int fputc(int ch, FILE *f)
  {
      // 这里重定向到 USART1 或 ITM
      ITM_SendChar(ch);
      return ch;
  }

  void _sys_exit(int x)
  {
      x = x;
      while (1);
  }

方案二：完全避免使用 printf：
  改用 sprintf 将格式化的字符串存储到缓冲区，然后手动通过串口发送。
```

### 错误 5：`Error: Flash Download failed - "Target No Device Found"`

```
错误信息：
  Flash Download failed - "Target No Device Found"
  (或 "Cortex-M3/M4/M7" not found)

原因分析：
  SWD 调试器无法连接到目标芯片。

排查步骤：

  1. 硬件连接检查：
     - SWDIO, SWCLK, GND 三根线是否接对
     - VCC 是否连接（部分调试器需要 VCC 参考电平）
     - 芯片供电是否正常（3.3V）

  2. 软件配置检查：
     - Debug 页面选择正确的调试器（ST-Link Debugger，不是 J-LINK/J-TRACE）
     - 检查 ST-Link 固件版本（STM32 ST-LINK Utility -> Firmware Update）
     - 在 ST-Link Settings -> Flash Download 中选择正确的 Flash Algorithm

  3. 复位与重试：
     - 按住复位键 -> 点击 Download -> 松开复位键（可能会成功）
     - 如果之前配置了错误的 GPIO 复用了 SWD 引脚，按住复位重新下载
     - 在 Settings -> Debug -> Port 中选择 SW（不是 JTAG）

  4. 终极方案：
     - 使用 STM32 ST-LINK Utility 执行 "Full Chip Erase"
     - 如果 ST-LINK Utility 也无法连接，检查硬件（尤其是焊接质量）
```

### 常见编译告警（Warning）说明

| 警告 | 说明 | 处理建议 |
|------|------|----------|
| `#68-D: integer conversion resulted in a change of sign` | 有符号/无符号整数隐式转换 | 添加显式强制类型转换 |
| `#177-D: variable "xxx" was declared but never referenced` | 变量定义了但未使用 | 删除或用 `(void)var;` 消除警告 |
| `#223-D: function "xxx" declared implicitly` | 函数未声明即调用 | 添加函数原型或包含对应头文件 |
| `#1-D: last line of file ends without a newline` | 文件末尾缺少换行 | 在文件末尾添加一个空行 |

---

## 面试练习题

1. 在 Keil MDK 中，要使用 STM32F103C8 的标准外设库，以下哪个 Preprocessor Symbols 定义是正确的？
   A. `STM32F10X_LD, USE_STDPERIPH_DRIVER`
   B. `STM32F10X_MD, USE_STDPERIPH_DRIVER`
   C. `STM32F10X_HD, USE_STDPERIPH_DRIVER`
   D. `STM32F10X_XL, USE_STDPERIPH_DRIVER`

2. STM32F407 与 STM32F103 在 GPIO 配置上的主要区别是什么？
   A. F407 不需要配置 GPIO 速度
   B. F407 的 GPIO 挂在 APB2 总线上，而 F103 挂在 AHB1 总线上
   C. F407 的 GPIO 初始化需要配置 GPIO_OType 和 GPIO_PuPd 参数
   D. F407 不需要使能 GPIO 时钟

3. 在 Keil 调试界面中，如果程序在 Flash 中运行且设置了 6 个以上的断点，会怎样？
   A. 所有断点都能正常工作，数量不受限制
   B. 第 7 个及以后的断点不会触发（因 Cortex-M3/M4 仅支持 6 个硬件断点）
   C. Keil 会自动将所有断点转换为软件断点
   D. 调试器会报错并停止调试

4. 使用 CubeMX 生成工程时，如果不配置 SYS -> Debug 为 Serial Wire，最可能出现的后果是？
   A. 程序无法编译
   B. LED 灯不亮
   C. 第二次下载时 ST-Link 无法连接芯片
   D. 串口无法输出

5. 在 Ubuntu 上进行 STM32 开发，最推荐的方案是？
   A. 只用 Windows 虚拟机，所有工作都在虚拟机内完成
   B. 只用 Wine 运行 Keil，不安装 Windows
   C. 使用 Ubuntu 进行代码编辑和编译，用 Windows 或虚拟机进行烧录调试
   D. 完全放弃 Keil，只用 GCC 和 OpenOCD

---

**参考答案**：1.B  2.C  3.B  4.C  5.C
