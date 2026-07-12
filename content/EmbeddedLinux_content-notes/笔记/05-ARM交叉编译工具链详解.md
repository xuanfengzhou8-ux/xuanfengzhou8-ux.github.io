# ARM 交叉编译工具链详解

## 1. 什么是交叉编译

### 1.1 宿主机与目标机

在嵌入式开发中，代码并不是在最终运行的设备上编写的，这就引入了两个关键概念：

- **宿主机（Host）**：用于编写和编译代码的计算机，通常是 x86_64 架构的 PC 或服务器，运行 Linux / macOS / Windows。
- **目标机（Target）**：最终运行编译后程序的设备，在嵌入式场景下通常是 ARM、RISC-V、MIPS 等架构的开发板或微控制器（如 STM32、树莓派、全志芯片等）。

**交叉编译（Cross Compilation）** 是指在宿主机上编译生成目标机架构可执行代码的过程。与之相对的是**本地编译（Native Compilation）**，即编译器和目标机架构相同，生成的程序直接在当前机器上运行。

### 1.2 为什么嵌入式开发需要交叉编译

嵌入式设备通常资源受限（CPU 频率低、内存小、没有大容量存储），无法直接运行 GCC、LLVM 等编译工具链。具体原因包括：

- **算力不足**：MCU（如 STM32F103）主频只有 72 MHz，内存几十 KB，编译 Linux 内核可能需要数小时甚至无法完成。
- **无操作系统**：裸机环境下根本没有文件系统和命令行环境来运行编译器。
- **开发效率**：PC 上编译速度远快于开发板，且可以同时使用 IDE、调试器、静态分析工具等辅助手段。
- **工具链本身占用大**：完整的 GCC 工具链安装后可达数 GB，嵌入式设备根本放不下。

因此，业界通用的做法是：**在 PC 上安装交叉编译工具链，编译出目标机架构的二进制文件，再通过烧录器或网络传输到目标机上运行。**

### 1.3 编译四阶段在交叉编译中的体现

无论是本地编译还是交叉编译，GCC 的工作流程都可分为四个阶段。区别在于：交叉编译的每个阶段使用的工具都是针对**目标机架构**的版本。

| 阶段 | 工具 | 输入 → 输出 | 说明 |
|------|------|-------------|------|
| **预处理** | `cpp` (C Preprocessor) | `main.c` → `main.i` | 处理 `#include`、`#define`、`#ifdef` 等指令，展开宏 |
| **编译** | `cc1` (编译器) | `main.i` → `main.s` | 将 C 代码翻译为目标机架构的汇编代码 |
| **汇编** | `as` (汇编器) | `main.s` → `main.o` | 将汇编代码转为机器指令，生成可重定位目标文件 |
| **链接** | `ld` (链接器) | `main.o` + 库 → `main.elf` | 将多个目标文件 + 库链接为可执行文件 |

在交叉编译中，这四个阶段的工具都以交叉工具链前缀命名，例如 `arm-none-eabi-gcc` 内部依次调用了针对 ARM 架构的预处理器、编译器、汇编器和链接器，而非宿主机自带的本地版本。

> **关键理解**：交叉编译器仍运行在宿主机上，只是它生成的机器码是目标机架构的指令集。它本身是一个运行在 x86_64 上的程序，但输出的是 ARM 指令。

---

## 2. 交叉编译工具链的组成

完整的交叉编译工具链（Toolchain）不只是编译器，而是一套工具的集合，通常包括以下组件：

### 2.1 核心组件

| 组件 | 名称示例 | 功能说明 |
|------|----------|----------|
| **编译器** | `arm-none-eabi-gcc` | C 语言编译器，将源码编译为目标机架构的汇编 |
| **C++ 编译器** | `arm-none-eabi-g++` | C++ 语言编译器 |
| **汇编器** | `arm-none-eabi-as` | 将汇编代码转为机器码（目标文件） |
| **链接器** | `arm-none-eabi-ld` | 将多个目标文件和库链接为可执行文件 |
| **预处理器** | `arm-none-eabi-cpp` | 处理宏定义和头文件包含 |

### 2.2 二进制工具（Binary Utilities / Binutils）

这些工具用于操作、分析和转换编译后的二进制文件，是调试和烧录过程中不可或缺的部分：

| 工具 | 功能说明 |
|------|----------|
| `arm-none-eabi-objcopy` | 目标文件格式转换（ELF → HEX / BIN），常用于生成烧录文件 |
| `arm-none-eabi-objdump` | 反汇编、查看目标文件段信息、符号表 |
| `arm-none-eabi-size` | 查看各段（text/data/bss）大小，分析固件体积 |
| `arm-none-eabi-nm` | 列出目标文件中的符号（函数名、全局变量等） |
| `arm-none-eabi-strings` | 提取二进制文件中可打印字符串 |
| `arm-none-eabi-strip` | 移除符号表和调试信息，减小文件体积 |
| `arm-none-eabi-readelf` | 查看 ELF 文件详细信息（段头、程序头、节区等） |
| `arm-none-eabi-addr2line` | 将地址转换为源码文件名和行号（配合地址回溯） |

### 2.3 C 标准库

交叉编译工具链通常捆绑一个 C 标准库，为程序提供 `printf`、`malloc`、`memcpy` 等基础函数。不同场景下的选择不同：

| C 库 | 特点 | 适用场景 |
|------|------|----------|
| **newlib** | 专为嵌入式系统设计，体积较轻量，功能较完整 | 裸机或 RTOS 环境 |
| **newlib-nano** | newlib 的进一步精简版（`--specs=nano.specs`），使用更小的 `printf`/`scanf` 实现 | 资源极度受限的 MCU |
| **glibc** | GNU C 库，功能最全、性能最优，但体积大 | 运行 Linux 的开发板（树莓派、BeagleBone 等） |
| **uClibc-ng** | 为 uClinux 设计，极轻量级 | 无 MMU 的嵌入式 Linux 设备 |
| **musl** | 轻量、安全、符合 POSIX 标准 | 现代嵌入式 Linux 系统 |

> **注意**：`arm-none-eabi-gcc` 工具链提供的是 newlib/newlib-nano；而 `arm-linux-gnueabihf-gcc` 工具链依赖目标板 Linux 系统中的 glibc。

---

## 3. 安装 ARM 交叉编译工具链

### 3.1 `arm-none-eabi-gcc` — 用于裸机 / STM32 开发

该工具链的目标是没有操作系统的裸机环境（Bare-metal），生成的代码直接在 MCU 上运行。

#### 方法一：apt 安装（推荐，较新版本）

```bash
# Ubuntu / Debian
sudo apt update
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi

# macOS (Homebrew)
brew install arm-none-eabi-gcc
```

#### 方法二：ARM 官网下载（获取特定版本）

```
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm
```

下载 `gcc-arm-none-eabi-<version>-linux.tar.bz2`，解压后配置环境变量：

```bash
# 解压
tar -xjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2

# 移动到合适目录（可选）
sudo mv gcc-arm-none-eabi-10.3-2021.10 /opt/

# 配置 PATH 环境变量（写入 ~/.bashrc 或 ~/.zshrc）
export PATH=$PATH:/opt/gcc-arm-none-eabi-10.3-2021.10/bin
```

### 3.2 `arm-linux-gnueabihf-gcc` — 用于 Linux 开发板

该工具链目标是可以运行 Linux 的开发板，生成的 ELF 文件由 Linux 内核加载执行。

#### 方法一：apt 安装

```bash
# Ubuntu / Debian
sudo apt update
sudo apt install gcc-arm-linux-gnueabihf binutils-arm-linux-gnueabihf
```

#### 方法二：Linaro 工具链

Linaro 提供了专门针对 ARM Linux 的优化工具链：

```
https://releases.linaro.org/components/toolchain/binaries/
```

```bash
# 下载示例（以 7.5-2019.12 为例，替换为最新可用版本）
wget https://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz

tar -xf gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz
sudo mv gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf /opt/
export PATH=$PATH:/opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin
```

### 3.3 环境变量配置

将工具链的 `bin/` 目录加入 `PATH` 后，推荐写入 shell 配置文件使其永久生效：

```bash
# 编辑 ~/.bashrc 或 ~/.zshrc 或 ~/.bash_profile
echo 'export PATH=$PATH:/opt/gcc-arm-none-eabi-10.3-2021.10/bin' >> ~/.bashrc
echo 'export PATH=$PATH:/opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin' >> ~/.bashrc
source ~/.bashrc
```

### 3.4 版本验证

安装完成后，通过以下命令确认工具链可用：

```bash
# 裸机工具链
arm-none-eabi-gcc --version

# Linux 工具链
arm-linux-gnueabihf-gcc --version

# 查看详细配置（目标架构等）
arm-none-eabi-gcc -v
```

正常输出应包含类似信息：

```
arm-none-eabi-gcc (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)
Copyright (C) 2020 Free Software Foundation, Inc.
```

---

## 4. 工具链命名规则解读

交叉编译工具链的命名遵循 `arch-vendor-os-abi` 的格式，理解这一命名规则有助于选择合适的工具链。

### 4.1 `arm-none-eabi-gcc` 各部分含义

| 段 | 含义 | 说明 |
|----|------|------|
| `arm` | **架构（Architecture）** | 目标 CPU 架构为 ARM |
| `none` | **厂商（Vendor）** | 无特定厂商（或可忽略），表示通用 |
| `eabi` | **ABI（Application Binary Interface）** | 嵌入式 ABI（Embedded ABI），目标为裸机系统 |

> **EABI** 定义了函数调用约定（参数如何传递、寄存器如何保存）、数据类型大小和对齐方式等二进制接口规范。裸机场景下使用 EABI。

### 4.2 `arm-linux-gnueabihf-gcc` 各部分含义

| 段 | 含义 | 说明 |
|----|------|------|
| `arm` | **架构** | 目标 CPU 架构为 ARM |
| `linux` | **操作系统（OS）** | 目标运行 Linux 操作系统 |
| `gnu` | **C 库类型** | 使用 GNU C 库（glibc） |
| `eabi` | **基本 ABI** | ARM EABI 规范 |
| `hf` | **硬浮点（Hard-Float）** | 使用硬件浮点单元（FPU）进行浮点运算 |

### 4.3 命名对比总结

| 工具链前缀 | 目标架构 | 操作系统 | C 库 | 浮点 | 典型用途 |
|------------|----------|----------|------|------|----------|
| `arm-none-eabi-` | ARM | 无（裸机） | newlib | soft/hard | STM32 MCU 裸机开发 |
| `arm-none-linux-gnueabihf-` | ARM | Linux | glibc | hard-float | ARM Linux 应用开发 |
| `arm-linux-gnueabihf-` | ARM | Linux | glibc | hard-float | 同上（简写，`none` 省略） |
| `arm-linux-gnueabi-` | ARM | Linux | glibc | soft-float | 无 FPU 的 ARM Linux |
| `aarch64-linux-gnu-` | ARM64 | Linux | glibc | — | 64 位 ARM Linux |

### 4.4 为什么有时找不到 `arm-linux-gnueabihf-gcc`

在某些发行版的包管理中，工具链可执行文件的实际名称可能略有差异，例如 Ubuntu 上安装后是 `arm-linux-gnueabihf-gcc`，而官方 Linaro 包名相同。搜索时可以使用 `apt search arm-none` 或 `apt search arm-linux` 来确认可用包。

> **记忆口诀**：**arch-vendor-os-abi** — 从左到右依次描述"什么架构、谁家的、跑什么系统、遵循什么接口规范"。

---

## 5. Makefile 中使用交叉编译器

### 5.1 基本 Makefile 示例

以下是一个针对 STM32 裸机程序的 Makefile 示例：

```makefile
# 工具链
CROSS_COMPILE = arm-none-eabi-
CC            = $(CROSS_COMPILE)gcc
LD            = $(CROSS_COMPILE)ld
OBJCOPY       = $(CROSS_COMPILE)objcopy
OBJDUMP       = $(CROSS_COMPILE)objdump
SIZE          = $(CROSS_COMPILE)size

# 项目配置
TARGET        = led-blink
SRC           = main.c startup.c
OBJ           = $(SRC:.c=.o)
LD_SCRIPT     = stm32f103.ld

# 编译选项
CFLAGS        = -mcpu=cortex-m3 -mthumb -Wall -O2 -g
CFLAGS       += -I./inc -DSTM32F103
LDFLAGS       = -T $(LD_SCRIPT) -nostartfiles -lc -lnosys

# 默认目标
all: $(TARGET).elf $(TARGET).hex $(TARGET).bin

# 编译
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 链接
$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

# 生成烧录文件
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# 反汇编
disasm: $(TARGET).elf
	$(OBJDUMP) -d $< > $(TARGET).dis

# 烧录（OpenOCD）
flash: $(TARGET).bin
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
		-c "program $(TARGET).bin 0x08000000 verify reset exit"

# 清理
clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex $(TARGET).bin $(TARGET).dis

.PHONY: all clean disasm flash
```

### 5.2 关键变量释义

- **`CROSS_COMPILE`**：交叉工具链前缀，切换工具链时只需改此行（如改为 `arm-linux-gnueabihf-`）。
- **`CFLAGS`**：传递给编译器的标志。
  - `-mcpu=cortex-m3`：指定目标 CPU 内核。
  - `-mthumb`：使用 Thumb-2 指令集（ARM Cortex-M 系列仅支持 Thumb 模式）。
  - `-Wall -O2 -g`：开启警告、优化级别 2、生成调试信息。
- **`LDFLAGS`**：传递给链接器的标志。
  - `-T $(LD_SCRIPT)`：指定链接脚本。
  - `-nostartfiles`：不使用默认启动文件（由我们提供 `startup.c`）。
- **文件格式**：`.elf`（含调试信息）、`.hex`（HEX 文本格式）、`.bin`（纯二进制）三种格式的用途不同，烧录时通常用 `.bin` 或 `.hex`。

### 5.3 Keil MDK-ARM IDE vs. Makefile + GCC 对比

| 对比维度 | Keil MDK-ARM IDE | Makefile + GCC |
|---------|------------------|----------------|
| **操作系统** | 仅 Windows | Windows / Linux / macOS |
| **价格** | 商业收费（社区版有限制） | 完全免费开源 |
| **上手难度** | 较低，图形界面，向导式配置 | 较高，需理解编译链接流程 |
| **调试** | 集成调试器，界面友好 | 可配合 VSCode + Cortex-Debug / pyOCD |
| **CI/CD 集成** | 困难（依赖 GUI） | 天然支持，命令行驱动 |
| **自定义程度** | 受限，按 IDE 规则配置 | 完全可控，链接脚本、编译选项自由定制 |
| **代码量控制** | 自动包含许多库，固件偏大 | 精细控制，固件体积小 |
| **团队协作** | .uvprojx 文件易冲突 | Makefile 纯文本，适合 Git 管理 |

**结论**：Keil 适合快速原型和初学者；Makefile + GCC 适合商业产品、持续集成和对编译过程有深入要求的场景。

---

## 6. 交叉编译 STM32 裸机程序

本节演示不使用 Keil，纯命令行完成一个 STM32F103 LED 闪烁程序的完整流程。

### 6.1 项目结构

```
led-blink/
├── Makefile
├── stm32f103.ld        # 链接脚本
├── startup.c           # 启动文件
├── main.c              # 主程序
└── inc/
    └── stm32f103.h     # 寄存器定义
```

### 6.2 链接脚本（Linker Script）

链接脚本告诉链接器各段（代码段、数据段、BSS 段等）应该放在内存的什么位置。

```ld
/* stm32f103.ld — STM32F103C8T6 (Blue Pill) 链接脚本 */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))    /* 中断向量表 */
        *(.text*)               /* 程序代码 */
        *(.rodata*)             /* 只读数据 */
        . = ALIGN(4);
        _etext = .;             /* 代码段结束地址 */
    } > FLASH

    .data :
    {
        _sdata = .;             /* 数据段起始地址 */
        *(.data*)
        . = ALIGN(4);
        _edata = .;             /* 数据段结束地址 */
    } > SRAM AT > FLASH

    .bss :
    {
        _sbss = .;              /* BSS 段起始地址 */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;              /* BSS 段结束地址 */
    } > SRAM

    _estack = ORIGIN(SRAM) + LENGTH(SRAM);  /* 栈顶地址 */
}
```

> **链接脚本中各段的含义**：`.text`（代码 + 只读数据）存放在 Flash；`.data`（已初始化的全局变量）运行时在 SRAM，初始值存储在 Flash；`.bss`（未初始化的全局变量）运行时在 SRAM，需清零。

### 6.3 启动文件（Startup Code）

启动文件是 MCU 上电后执行的第一段代码，负责初始化系统和 C 运行时环境。

```c
/* startup.c — STM32F103 简易启动文件 */

extern int main(void);
extern void _estack(void);  /* 栈顶地址, 在链接脚本中定义 */

/* 中断向量表 */
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    _estack,                  /* 0x00000000: 栈顶指针 */
    Reset_Handler,            /* 0x00000004: 复位中断 */
    /* 其他中断可在此添加 */
};

/* 复位中断处理函数 */
void Reset_Handler(void)
{
    /* 声明链接脚本中定义的符号 */
    extern unsigned int _sdata, _edata, _sbss, _ebss;
    extern unsigned int _etext;

    unsigned int *src, *dst;

    /* 1. 复制 .data 段从 Flash 到 SRAM */
    src = &_etext;
    dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    /* 2. 清零 .bss 段 */
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;

    /* 3. 跳转到 main */
    main();

    /* main 返回后死循环 */
    while (1);
}
```

### 6.4 主程序

```c
/* main.c — LED 闪烁（STM32F103C8，PA5 接 LED） */

#include "stm32f103.h"

/* 简单软件延时 */
static void delay(volatile unsigned int count)
{
    while (count--)
        __asm__("nop");
}

int main(void)
{
    /* 1. 使能 GPIOA 时钟（RCC APB2 外设时钟使能寄存器） */
    RCC->APB2ENR |= (1 << 2);   /* IOPAEN: GPIOA 时钟使能 */

    /* 2. 配置 PA5 为推挽输出，50 MHz */
    GPIOA->CRL &= ~(0xF << 20); /* 清除 CNF5 和 MODE5 */
    GPIOA->CRL |=  (0x3 << 20); /* MODE5 = 11: 输出 50 MHz */
                               /* CNF5 = 00: 通用推挽输出 */

    while (1)
    {
        /* 3. 点亮 LED（PA5 置高） */
        GPIOA->BSRR = (1 << 5);

        delay(1000000);

        /* 4. 熄灭 LED（PA5 置低） */
        GPIOA->BRR  = (1 << 5);

        delay(1000000);
    }
}
```

```c
/* inc/stm32f103.h — STM32F103 寄存器定义 */

#ifndef __STM32F103_H
#define __STM32F103_H

typedef unsigned int uint32_t;

/* 外设基地址 */
#define PERIPH_BASE     0x40000000UL
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000UL)
#define AHBPERIPH_BASE  (PERIPH_BASE + 0x20000UL)

/* GPIOA */
#define GPIOA_BASE      (APB2PERIPH_BASE + 0x0800UL)

/* RCC */
#define RCC_BASE        (AHBPERIPH_BASE + 0x1000UL)

/* GPIO 寄存器结构体 */
typedef struct {
    uint32_t CRL;       /* 端口配置低寄存器，地址偏移 0x00 */
    uint32_t CRH;       /* 端口配置高寄存器，地址偏移 0x04 */
    uint32_t IDR;       /* 端口输入数据寄存器，地址偏移 0x08 */
    uint32_t ODR;       /* 端口输出数据寄存器，地址偏移 0x0C */
    uint32_t BSRR;      /* 端口置位/复位寄存器，地址偏移 0x10 */
    uint32_t BRR;       /* 端口复位寄存器，地址偏移 0x14 */
    uint32_t LCKR;      /* 端口配置锁定寄存器，地址偏移 0x18 */
} GPIO_TypeDef;

/* RCC 寄存器结构体 */
typedef struct {
    uint32_t CR;        /* 时钟控制寄存器，地址偏移 0x00 */
    uint32_t CFGR;      /* 时钟配置寄存器，地址偏移 0x04 */
    uint32_t CIR;       /* 时钟中断寄存器，地址偏移 0x08 */
    uint32_t APB2RSTR;  /* APB2 外设复位寄存器，地址偏移 0x0C */
    uint32_t APB1RSTR;  /* APB1 外设复位寄存器，地址偏移 0x10 */
    uint32_t AHBENR;    /* AHB 外设时钟使能寄存器，地址偏移 0x14 */
    uint32_t APB2ENR;   /* APB2 外设时钟使能寄存器，地址偏移 0x18 */
    uint32_t APB1ENR;   /* APB1 外设时钟使能寄存器，地址偏移 0x1C */
    /* ... 其他寄存器省略 */
} RCC_TypeDef;

/* 外设指针 */
#define GPIOA           ((GPIO_TypeDef *) GPIOA_BASE)
#define RCC             ((RCC_TypeDef *)  RCC_BASE)

#endif /* __STM32F103_H */
```

### 6.5 编译与烧录

```bash
# 1. 编译
cd led-blink
make clean && make

# 2. 查看生成的固件大小
arm-none-eabi-size led-blink.elf

# 3. 反汇编（可选，验证生成的机器码）
arm-none-eabi-objdump -d led-blink.elf | head -50

# 4. 烧录（使用 ST-Link + OpenOCD）
#    确保 ST-Link 已连接，stlink 驱动已安装
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
    -c "program led-blink.bin 0x08000000 verify reset exit"
```

成功烧录后，STM32F103 开发板上的 LED 将以约 0.5 Hz 的频率闪烁。

---

## 7. 交叉编译 Linux 应用程序

### 7.1 编写 Hello World

```c
/* hello.c */
#include <stdio.h>

int main(void)
{
    printf("Hello from ARM Linux!\n");
    printf("Cross compilation works!\n");
    return 0;
}
```

### 7.2 交叉编译

```bash
# 使用 arm-linux-gnueabihf 工具链编译
arm-linux-gnueabihf-gcc hello.c -o hello -static

# 查看生成文件的架构信息
file hello
```

输出显示：

```
hello: ELF 32-bit LSB executable, ARM, EABI5 version 1 (GNU/Linux), statically linked, not stripped
```

**参数说明**：

- `-static`：静态链接，将 glibc 库函数直接编译进可执行文件。优点是目标板上不需要装库，缺点是体积较大。
- 不加 `-static` 时采用动态链接，目标板上必须存在匹配版本的 glibc 及其动态链接器 `ld-linux-armhf.so.3`。

### 7.3 传输到开发板运行

有多种方式可以将编译好的程序传输到开发板上运行：

#### 方式一：scp（推荐，通过 SSH）

```bash
# 从 PC 传输到开发板（假设开发板 IP 为 192.168.1.100）
scp hello root@192.168.1.100:/root/

# SSH 登录开发板
ssh root@192.168.1.100

# 运行
chmod +x /root/hello
./hello
```

#### 方式二：NFS 共享（适合开发调试）

在 PC 上配置 NFS 服务器，将编译目录共享给开发板，开发板挂载后可直接运行。

```bash
# 开发板上挂载 NFS
mount -t nfs 192.168.1.2:/path/to/project /mnt -o nolock
/mnt/hello
```

#### 方式三：U 盘拷贝

将程序复制到 U 盘（需格式化为 FAT32 或 ext4），插入开发板挂载后运行。适合无网络环境。

### 7.4 静态链接 vs 动态链接（补充说明）

| 对比项 | 静态链接（`-static`） | 动态链接 |
|--------|----------------------|----------|
| 文件大小 | 较大（约 800 KB ~ 1.5 MB） | 较小（约 8 ~ 15 KB） |
| 依赖 | 无外部依赖 | 目标板需匹配的 .so 库 |
| 兼容性 | 好（不依赖目标板库版本） | 差（库版本不匹配 → 运行失败） |
| 启动速度 | 较快 | 稍慢（需加载动态链接器） |
| 部署场景 | 做产品发布 | 开发调试，或能精确控制目标板软件环境 |

> **开发建议**：调试阶段使用动态链接以提升迭代速度（scp 小文件更快）；发布阶段使用静态链接或提供打包好的库文件。

---

## 8. 常见问题排查

### 8.1 `command not found`

**现象**：执行 `arm-none-eabi-gcc` 等命令时提示未找到。

**原因与解决**：

1. **工具链未安装** → 对照第 3 节安装对应工具链。
2. **环境变量未配置** → 检查 `echo $PATH` 中是否包含工具链的 `bin/` 目录；确认 `source ~/.bashrc` 已执行。
3. **Shell 未重新加载** → 重新打开终端或执行 `exec $SHELL -l`。
4. **权限问题** → 检查工具链目录是否有执行权限：`ls -l /opt/gcc-arm-none-eabi-*/bin/`。

### 8.2 库版本不匹配

**现象**：在开发板上运行 Linux 程序时提示：

```
./hello: error while loading shared libraries: libc.so.6: cannot open shared object file: No such file or directory
```

或者：

```
./hello: /lib/arm-linux-gnueabihf/libc.so.6: version `GLIBC_2.31' not found
```

**原因**：宿主机交叉编译时链接的 glibc 版本高于目标板上安装的版本。

**解决方案**：

1. **使用静态链接**：`arm-linux-gnueabihf-gcc hello.c -o hello -static`（最快捷）。
2. **降级工具链版本**：安装与目标板匹配的旧版工具链。
3. **升级目标板系统**：更新开发板上的 Linux 系统。
4. **使用 Docker**：创建与目标板系统版本一致的 Docker 容器进行编译。

### 8.3 浮点 ABI 不兼容

**现象**：

```
FATAL: kernel too old
Illegal instruction
```

编译时出现：

```
error: conflicting CPU architectures 1/16
```

**原因**：ARM 的浮点 ABI 分为 soft、softfp、hard 三种，宿主机和目标板的设置不一致。

| 浮点 ABI | 说明 | 标志 |
|----------|------|------|
| **soft** | 不使用硬件 FPU，浮点运算由软件模拟，函数参数通过整数寄存器传递 | `-mfloat-abi=soft` |
| **softfp** | 允许使用硬件 FPU 指令，但函数参数仍通过整数寄存器传递（与 soft 兼容） | `-mfloat-abi=softfp` |
| **hard** | 完全使用硬件 FPU，函数参数通过 FPU 寄存器传递（与 soft 不兼容） | `-mfloat-abi=hard` |

**检查目标板的 FPU 能力**：

```bash
# 在开发板上执行
cat /proc/cpuinfo | grep Features
# 输出中若包含 "vfp" 或 "neon" 则支持硬件浮点
```

**解决方案**：

1. 确认工具链的浮点配置：`arm-linux-gnueabihf-gcc -v 2>&1 | grep -- --with-float`。
2. 编译时显式指定浮点 ABI：`arm-linux-gnueabihf-gcc -mfloat-abi=hard -mfpu=vfp hello.c -o hello`。
3. 确保选择带 `hf` 后缀的工具链（`arm-linux-gnueabihf`）编译 hard-float 目标板的程序。

> **关键原则**：编译器和目标板的浮点 ABI 必须一致，否则程序会崩溃或产生错误的计算结果。

### 8.4 链接脚本错误导致烧录后不运行

**现象**：烧录成功，但上电后程序不运行。

**常见原因**：

1. **中断向量表位置不对**：`.isr_vector` 段必须放在 Flash 起始地址（`0x08000000`）。
2. **栈顶指针错误**：`_estack` 计算错误，导致启动时 MSP 指向无效地址。
3. **`.data` 段初始化未完成**：启动文件中未正确从 Flash 复制初始值到 SRAM。
4. **链接脚本内存范围超限**：`.text + .rodata` 大小超过 64 KB（对于 STM32F103C8）。

### 8.5 OpenOCD 烧录失败

**常见错误与解决**：

| 错误信息 | 原因 | 解决 |
|----------|------|------|
| `unable to find a matching CMSIS-DAP device` | 调试器驱动问题 | 安装正确驱动，检查 USB 连接 |
| `Error: open failed` | 设备被占用或权限不足 | 检查 `lsusb`，添加 udev 规则或使用 `sudo` |
| `Error: timed out while waiting for target halted` | 目标芯片处于休眠或锁死状态 | 按住复位键再试，或检查连接线 |
| `Error: target not in halt state` | 目标芯片没有停止 | 尝试 `reset halt` 命令 |

---

## 面试练习题

**题目 1**：简述交叉编译的概念，以及为什么嵌入式开发中必须使用交叉编译而非本地编译。

**题目 2**：对比 `arm-none-eabi-gcc` 和 `arm-linux-gnueabihf-gcc` 这两条工具链的前缀命名中，各部分（arch、vendor、os、abi）分别代表什么含义？它们各自适用于什么场景？

**题目 3**：GCC 的编译过程分为预处理、编译、汇编和链接四个阶段。请说明每个阶段的输入输出文件格式，并指出交叉编译中哪个阶段与本地编译有根本性区别、为什么。

**题目 4**：在交叉编译 STM32 裸机程序时，链接脚本（Linker Script）的作用是什么？请说明 STM32 的 Flash 和 SRAM 地址空间中分别存放了哪些段（.text、.data、.bss），以及启动文件中完成的 .data 段初始化和 .bss 段清零过程。

**题目 5**：在开发板上运行交叉编译的 Linux 程序时，出现 `./hello: /lib/arm-linux-gnueabihf/libc.so.6: version 'GLIBC_2.31' not found` 错误。请分析原因并给出至少三种解决方案。
