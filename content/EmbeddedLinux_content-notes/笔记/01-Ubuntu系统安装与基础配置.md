# Ubuntu 系统安装与基础配置

---

## 1. 为什么选择 Ubuntu

### 1.1 Linux 发行版概览

Linux 操作系统有数百种发行版（Distribution），它们共享相同的 Linux 内核，但在包管理、默认软件、桌面环境、更新策略上各有不同。对于嵌入式系统开发者而言，选择合适的发行版直接影响到开发效率、工具链兼容性和团队协作。

### 1.2 Ubuntu vs 其他主流发行版

| 特性 | Ubuntu | CentOS / Rocky Linux | Debian | Fedora | Arch Linux |
|------|--------|----------------------|--------|--------|------------|
| 包管理 | APT (`.deb`) | YUM/DNF (`.rpm`) | APT (`.deb`) | DNF (`.rpm`) | Pacman |
| 软件新度 | 适中 | 保守 | 较保守 | 前沿 | 滚动更新 |
| 社区规模 | 最大 | 中等 | 大 | 中等 | 中等 |
| 商业支持 | Canonical | Red Hat / 社区 | 社区 | Red Hat | 社区 |
| 嵌入式资料 | 最丰富 | 较少 | 较多 | 较少 | 较少 |
| 初学者友好 | 非常友好 | 一般 | 一般 | 友好 | 不友好 |

### 1.3 选择 Ubuntu 的关键理由

**（1）最丰富的嵌入式开发资料**

Ubuntu 拥有全球最大的 Linux 用户社区。当你在嵌入式开发中遇到问题（如交叉编译失败、驱动加载失败、U-Boot 配置错误），在搜索引擎中输入问题加上 "Ubuntu"，几乎总能找到现成解答。对于学生而言，这意味着更低的试错成本。

**（2）APT 包管理简洁高效**

```bash
# 一行命令安装全部嵌入式开发工具
sudo apt update
sudo apt install build-essential gcc-arm-linux-gnueabihf u-boot-tools
```

APT 自动处理依赖关系，无需像 Arch 那样频繁手动介入，也不会像 Fedora 那样某些包需要额外添加 Copr 仓库。

**（3）LTS 版本提供长期稳定支持**

Ubuntu LTS（Long Term Support）版本每两年发布一次，提供 **5 年标准支持 + 5 年 ESM（扩展安全维护）**，共 10 年的生命周期。对于嵌入式开发项目，这意味着：

- 开发环境可以稳定使用多年，无需频繁升级系统
- 团队所有成员可以保持一致的开发环境
- CI/CD 流水线的镜像版本可以长期锁定

**（4）硬件和工具链兼容性最佳**

各大半导体厂商（常见半导体平台）的 SDK 和 BSP（Board Support Package）官方支持的 Linux 发行版首选 Ubuntu。ARM 的交叉编译工具链、Yocto Project、Buildroot 等嵌入式构建系统在 Ubuntu 上的测试最为充分。

**（5）对初学者最友好**

Ubuntu 的安装过程有图形化向导、硬件驱动自动识别、中文支持开箱即用。学生无需在系统安装环节消耗过多精力，可以将更多时间投入到嵌入式开发本身。

### 1.4 Ubuntu LTS 版本选择建议

| LTS 版本 | 发布年份 | 标准支持截止 | 推荐场景 |
|----------|----------|--------------|----------|
| 20.04 (Focal) | 2020 | 2025 | 兼容老旧项目，即将结束支持 |
| 22.04 (Jammy) | 2022 | 2027 | 当前最稳定选择，推荐 |
| 24.04 (Noble) | 2024 | 2029 | 最新 LTS，适合新项目 |

> **建议**：2026 年的当下，新安装推荐使用 **Ubuntu 24.04 LTS**，组件较新且支持周期最长。若团队项目仍基于 22.04，建议保持一致。

---

## 2. 安装方式选择

### 2.1 三种主流方案概述

嵌入式 Linux 开发环境可以搭建在虚拟机（VM）、WSL2 或物理机上。每种方案适合不同的场景和学习阶段。

### 2.2 方案对比表

| 特性 | VMware / VirtualBox 虚拟机 | WSL2 | 物理机双系统 |
|------|---------------------------|------|--------------|
| **安装难度** | 低 | 低 | 中 |
| **性能损失** | 中等（约 10-20%） | 低（约 5%） | 无 |
| **与 Windows 共享文件** | 简单（拖拽/共享文件夹） | 原生集成 | 需要双系统切换 |
| **GUI 桌面** | 完整桌面 | 需额外配置（WSLg） | 完整桌面 |
| **USB/串口设备直通** | 支持（需配置） | 支持（USBIP） | 原生支持 |
| **磁盘空间占用** | 动态分配 20-60 GB | 较小 | 需要独立分区 |
| **系统切换** | 无需重启 | 无需重启 | 需要重启切换 |
| **同时运行多个 Linux** | 轻松 | 轻松 | 困难 |
| **适合阶段** | 学习、开发初期 | 开发、代码编译 | 高性能嵌入式开发 |

### 2.3 VMware 虚拟机方案（推荐初学者）

**优势详解：**

- **快照功能**：在安装系统、配置环境前拍摄快照，出错时可一键恢复
- **不破坏宿主机**：无需分区、无需重启，不影响 Windows 正常使用
- **网络模式灵活**：支持 NAT、桥接、Host-Only 多种模式，方便模拟嵌入式网络环境
- **串口模拟**：可在虚拟机中配置串口，配合 Minicom 练习调试嵌入式设备

**适用场景：** 绝大多数嵌入式 Linux 初学者、实验室统一环境部署。

### 2.4 WSL2 方案

**优势详解：**

- **性能接近原生**：WSL2 使用真正的 Linux 内核（在 Hyper-V 虚拟机中运行），文件系统 I/O 性能远超 WSL1
- **VS Code 深度集成**：通过 Remote-WSL 插件可以直接在 WSL2 中编辑代码、调试
- **零资源浪费**：不启动时不占用内存，启动后内存动态管理

**局限性：**

- **缺乏完整桌面环境**：WSLg 可运行 GUI 应用，但非完整桌面体验
- **USB/串口需要额外配置**：需安装 `usbipd-win` 工具
- **systemd 支持较晚**：从 Windows 11 才开始原生支持 systemd

```powershell
# WSL 安装命令（PowerShell 管理员模式）
wsl --install -d Ubuntu-24.04

# 安装后检查 WSL 版本
wsl -l -v
```

### 2.5 物理机双系统方案

**适用场景：** 需要进行大量编译（如完整 Yocto 构建）、需要直接操作硬件设备（调试器、烧录器）。

**注意：** 双系统安装需要手动分区、管理引导（GRUB），存在误删分区或覆盖 Windows 引导的风险。建议在具备一定 Linux 基础后再尝试。

---

## 3. VMware 安装 Ubuntu 详细步骤

### 3.1 准备工作

**（1）下载 VMware Workstation**

- 官网地址：https://www.vmware.com/products/workstation-pro.html
- 推荐版本：VMware Workstation 17 Pro 或 VMware Workstation Player（免费版）
- 也可以使用 VirtualBox 7.x（开源免费）

**（2）下载 Ubuntu 22.04/24.04 LTS ISO 镜像**

```
https://releases.ubuntu.com/
```

选择对应的 LTS 版本，下载 Desktop Image（`.iso` 文件，约 5 GB）。

### 3.2 创建虚拟机

打开 VMware，选择 **"创建新的虚拟机"**（Create a New Virtual Machine），建议选择 **"自定义（高级）"** 以获得最大灵活性。

```
步骤 1：选择虚拟机兼容性
  -> Workstation 17.x（默认即可）

步骤 2：安装来源
  -> 选择 "安装程序光盘映像文件（iso）"
  -> 浏览并选择下载的 Ubuntu ISO 文件

步骤 3：客户机操作系统
  -> 客户机操作系统：Linux
  -> 版本：Ubuntu 64 位

步骤 4：虚拟机名称和位置
  -> 名称：Ubuntu 24.04 LTS
  -> 位置：建议放在空间充足的盘（如 D:\VMs\Ubuntu24.04）

步骤 5：处理器配置
  -> 处理器数量：1
  -> 每个处理器内核数量：2（或根据宿主机 CPU 调整）

步骤 6：虚拟机内存
  -> 建议：4096 MB（4 GB）
  -> 最低：2048 MB（2 GB）

步骤 7：网络类型
  -> 选择 "使用网络地址转换（NAT）"
  -> NAT 模式使虚拟机通过宿主机 IP 上网，方便且不占用局域网 IP

步骤 8：I/O 控制器类型
  -> 默认：LSI Logic（或 NVMe，根据 VMware 版本）

步骤 9：虚拟磁盘类型
  -> 默认：SCSI（或 NVMe）

步骤 10：磁盘
  -> 选择 "创建新虚拟磁盘"
  -> 最大磁盘大小：40-60 GB（建议 60 GB，确保编译空间充足）
  -> 选择 "将虚拟磁盘拆分为多个文件"（方便迁移）
```

### 3.3 安装 Ubuntu 操作系统

1. 启动虚拟机，等待 Ubuntu 安装引导界面出现
2. 选择语言：**简体中文** 或 **English**（建议选择英文，终端操作更兼容）
3. 选择 **"Install Ubuntu"**
4. 键盘布局：默认 `English (US)`
5. 安装类型：选择 **"Erase disk and install Ubuntu"**（这是在虚拟机内，不会影响宿主机）
6. 设置用户名和密码：
   - Your name：`你的名字`
   - Computer's name：`ubuntu-dev`（主机名，后续终端可见）
   - Pick a username：`你的用户名`（如 `student`）
   - Password：设置一个你记得住的密码
7. 等待安装完成（约 10-20 分钟，取决于机器性能）
8. 安装完成后重启，并移除安装介质（VMware 会自动断开 ISO）

### 3.4 首次启动配置

**（1）安装 VMware Tools / open-vm-tools**

VMware Tools 提供更好的鼠标集成、剪贴板共享、拖拽文件等功能。

```bash
# 打开终端（Ctrl+Alt+T），执行
sudo apt update
sudo apt install -y open-vm-tools open-vm-tools-desktop
```

安装完成后重启虚拟机以生效（或注销重新登录）。

**（2）设置屏幕分辨率自适应**

安装 `open-vm-tools-desktop` 后，调整 VMware 窗口大小，Ubuntu 桌面会自动适应。

### 3.5 虚拟机常用的 VMware 功能

| 功能 | 操作方法 | 说明 |
|------|----------|------|
| **快照** | VM -> Snapshot -> Take Snapshot | 在安装环境前拍摄快照 |
| **共享文件夹** | VM -> Settings -> Options -> Shared Folders | 在 Windows 和 Ubuntu 间共享文件 |
| **拖拽复制** | 安装 open-vm-tools 后直接拖拽 | 简单快捷 |
| **全屏模式** | View -> Full Screen 或 Ctrl+Alt+Enter | 沉浸式工作 |
| **挂起/恢复** | VM -> Power -> Suspend Guest | 下次启动恢复工作状态 |

---

## 4. Ubuntu 基础系统配置

### 4.1 软件源配置（换国内源）

Ubuntu 默认的软件源位于国外（archive.ubuntu.com），下载速度较慢。更换为国内镜像源可以显著提升软件下载速度。

**常用国内软件源（2026 年推荐）：**

| 镜像站 | 地址 | 适用地区 |
|--------|------|----------|
| 清华 TUNA | `https://mirrors.tuna.tsinghua.edu.cn/ubuntu/` | 全国 |
| 虚拟电商公司乙云 | `https://mirror-a.example.com/ubuntu/` | 全国 |
| 中科大 USTC | `https://mirrors.ustc.edu.cn/ubuntu/` | 全国 |
| 虚拟通信公司己云 | `https://mirror-b.example.com/ubuntu/` | 全国 |

**图形化方式（推荐初学者）：**

```bash
# 打开 "软件和更新"（Software & Updates）
# 在 "Ubuntu 软件" 选项卡中，将 "下载自" 改为 "其他站点"
# 选择中国服务器，如 mirrors.tuna.tsinghua.edu.cn
```

**命令行方式：**

```bash
# 备份原 sources.list
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak

# 以清华源为例，替换为 Ubuntu 22.04 源
sudo sed -i 's@//archive.ubuntu.com@//mirrors.tuna.tsinghua.edu.cn@g' /etc/apt/sources.list
sudo sed -i 's@//security.ubuntu.com@//mirrors.tuna.tsinghua.edu.cn@g' /etc/apt/sources.list

# 如果是 Ubuntu 24.04，sources 文件格式已变化，建议直接编辑
# 或者使用以下方式查看版本代号：
lsb_release -a
# 输出中 Codename 为 jammy（22.04）或 noble（24.04）
```

对于 Ubuntu 24.04，系统使用 `sources.list` 和 `/etc/apt/sources.list.d/ubuntu.sources` 配置文件，建议直接编辑新的格式：

```bash
# Ubuntu 24.04 的清华源配置
sudo tee /etc/apt/sources.list.d/ubuntu.sources > /dev/null <<EOF
Types: deb
URIs: https://mirrors.tuna.tsinghua.edu.cn/ubuntu/
Suites: noble noble-updates noble-backports
Components: main restricted universe multiverse
Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg

Types: deb
URIs: https://mirrors.tuna.tsinghua.edu.cn/ubuntu/
Suites: noble-security
Components: main restricted universe multiverse
Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg
EOF
```

### 4.2 系统更新

```bash
# 更新软件包列表（从源拉取最新包索引）
sudo apt update

# 升级所有已安装软件包
sudo apt upgrade -y

# 升级 Linux 内核等核心组件
sudo apt dist-upgrade -y

# 清理不需要的软件包缓存
sudo apt autoremove -y
sudo apt autoclean

# 检查是否需要重启（如果有内核更新）
[ -f /var/run/reboot-required ] && echo "需要重启系统"
```

### 4.3 中文输入法配置

**方法一：IBus（系统自带，推荐）**

```bash
# 安装中文语言包
sudo apt install -y language-pack-zh-hans language-pack-zh-hans-base

# 安装 IBus 中文输入引擎
sudo apt install -y ibus-libpinyin ibus-clutter

# 重启 IBus 服务
ibus restart

# 进入设置 -> Region & Language -> Input Sources
# 点击 + 号，选择 Chinese (Intelligent Pinyin)
# 切换快捷键：Super（Win 键）+ Space
```

**方法二：Fcitx5（功能更丰富）**

```bash
sudo apt install -y fcitx5 fcitx5-chinese-addons fcitx5-pinyin

# 设置为默认输入法框架
im-config -n fcitx5

# 注销重新登录后生效
```

### 4.4 终端美化（可选）

**安装 Zsh + Oh My Zsh：**

```bash
# 安装 Zsh
sudo apt install -y zsh

# 查看当前 shell
echo $SHELL

# 切换默认 shell 为 Zsh
chsh -s /bin/zsh
# 输入密码，退出重新登录后生效

# 安装 Oh My Zsh
sh -c "$(curl -fsSL https://example.com/shell-theme/install.sh)"
```

**安装 Starship 提示符（更美观的命令行提示）：**

```bash
# 安装 Starship
curl -sS https://starship.rs/install.sh | sh

# 在 .zshrc 末尾添加
echo 'eval "$(starship init zsh)"' >> ~/.zshrc

# 安装 Nerd Font 以获得图标支持
# 推荐：Meslo Nerd Font，可在终端 Setting 中修改字体
```

---

## 5. 嵌入式开发必备软件包

### 5.1 一键安装命令

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    gcc \
    g++ \
    make \
    cmake \
    git \
    vim \
    net-tools \
    openssh-server \
    minicom
```

### 5.2 各软件包作用详解

| 软件包 | 作用 | 验证命令 |
|--------|------|----------|
| `build-essential` | GCC/G++ 编译器集合 + libc 开发头文件 | `gcc --version` |
| `gcc` | GNU C 编译器 | `gcc --version` |
| `g++` | GNU C++ 编译器 | `g++ --version` |
| `make` | 项目构建工具，通过 Makefile 编译 | `make --version` |
| `cmake` | 跨平台构建系统生成器（比 Makefile 更现代化） | `cmake --version` |
| `git` | 分布式版本控制系统 | `git --version` |
| `vim` | 终端文本编辑器 | `vim --version` |
| `net-tools` | 网络诊断工具（ifconfig、netstat 等） | `ifconfig` |
| `openssh-server` | SSH 服务端，远程登录支持 | `ssh localhost` |
| `minicom` | 串口通信工具，调试开发板 | `minicom --version` |

### 5.3 额外推荐的嵌入式开发包

```bash
# 交叉编译工具链（ARM 架构）
sudo apt install -y \
    gcc-arm-linux-gnueabihf \
    g++-arm-linux-gnueabihf \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu

# 调试和反汇编工具
sudo apt install -y \
    gdb-multiarch \
    strace \
    ltrace \
    objdump \
    binutils

# 嵌入式构建系统
sudo apt install -y \
    u-boot-tools \
    device-tree-compiler \
    qemu-system-arm \
    qemu-user-static

# 文件系统工具
sudo apt install -y \
    mtd-utils \
    dosfstools \
    e2fsprogs

# 网络测试工具
sudo apt install -y \
    curl \
    wget \
    netcat-openbsd \
    tcpdump \
    nmap
```

### 5.4 验证安装

安装完成后，通过以下命令验证所有工具可用：

```bash
# 编译器和构建工具
echo "=== GCC ===" && gcc --version | head -1
echo "=== G++ ===" && g++ --version | head -1
echo "=== Make ===" && make --version | head -1
echo "=== CMake ===" && cmake --version | head -1

# 版本控制
echo "=== Git ===" && git --version

# 交叉编译器
echo "=== ARM GCC ===" && arm-linux-gnueabihf-gcc --version | head -1
echo "=== AArch64 GCC ===" && aarch64-linux-gnu-gcc --version | head -1

# 网络工具
echo "=== ifconfig ===" && ifconfig

# SSH
echo "=== SSH ===" && ssh -V 2>&1

# 串口
echo "=== Minicom ===" && minicom --version
```

---

## 6. SSH 配置

### 6.1 安装与基本配置

SSH（Secure Shell）是一种加密的网络协议，用于在不安全的网络上安全地运行网络服务。在嵌入式开发中，SSH 用于：

- 远程登录开发板（通常开发板运行 Linux 系统）
- 通过 SCP/RSYNC 传输文件
- 启动远程调试会话（gdbserver）

**安装 openssh-server：**

```bash
sudo apt install -y openssh-server
```

**检查 SSH 服务状态：**

```bash
# 查看服务是否运行
sudo systemctl status ssh

# 如果未运行，手动启动
sudo systemctl start ssh

# 查看 SSH 监听端口（默认 22）
sudo netstat -tlnp | grep :22
```

### 6.2 开机自启配置

```bash
# 设置 SSH 服务开机自启
sudo systemctl enable ssh

# 验证自启配置
sudo systemctl is-enabled ssh
# 输出应为：enabled

# 重启 SSH 服务（修改配置文件后使用）
sudo systemctl restart ssh
```

### 6.3 SSH 配置文件详解

```bash
# 编辑 SSH 配置文件
sudo vim /etc/ssh/sshd_config
```

常用配置项：

```ini
# 监听端口（建议教学环境保持默认）
Port 22

# 禁止 root 直接登录（安全考虑）
PermitRootLogin no

# 允许密码认证（内网教学环境可开启）
PasswordAuthentication yes

# 允许公钥认证
PubkeyAuthentication yes

# RSA 公钥存储位置
AuthorizedKeysFile .ssh/authorized_keys
```

**安全注意事项：**

- 在公网环境中，建议将 `PasswordAuthentication` 设为 `no`，仅使用密钥登录
- 修改默认端口（如 2222）以减少被扫描攻击的风险
- 定期审查 `/var/log/auth.log` 中的登录记录

### 6.4 SSH 免密登录配置

**场景：** 在 Ubuntu 主机和开发板之间建立信任关系，实现无需输入密码的 SSH 登录。这在自动化部署、远程调试时极为重要。

**步骤一：生成密钥对（在主机上执行）**

```bash
# 生成 RSA 密钥对（默认 3072 位）
ssh-keygen -t rsa -b 4096 -C "embedded-dev@ubuntu"

# 输出路径默认为 ~/.ssh/id_rsa（私钥）和 ~/.ssh/id_rsa.pub（公钥）
# 提示输入 passphrase 时直接回车（免密则留空）

# 查看生成的公钥
cat ~/.ssh/id_rsa.pub
```

**步骤二：将公钥复制到开发板（或目标机器）**

方法一（使用 `ssh-copy-id`，最简单）：

```bash
# 将公钥复制到开发板
ssh-copy-id student@192.168.1.100
# 输入开发板密码后，公钥自动追加到开发板的 ~/.ssh/authorized_keys
```

方法二（手动复制）：

```bash
# 在主机上查看公钥
cat ~/.ssh/id_rsa.pub

# 在开发板上创建 .ssh 目录（如果不存在）
mkdir -p ~/.ssh
chmod 700 ~/.ssh

# 将公钥内容追加到 authorized_keys
echo "ssh-rsa AAAA... embedded-dev@ubuntu" >> ~/.ssh/authorized_keys
chmod 600 ~/.ssh/authorized_keys
```

**步骤三：验证免密登录**

```bash
# 简化：配置 SSH 别名（可选）
echo "Host board
    HostName 192.168.1.100
    User student
    Port 22
    IdentityFile ~/.ssh/id_rsa" >> ~/.ssh/config

# 免密登录测试
ssh student@192.168.1.100
# 或使用别名
ssh board

# 执行远程命令
ssh board "uname -a && cat /proc/cpuinfo"
```

**调试 SSH 连接：**

```bash
# 使用 -vvv 输出详细调试信息
ssh -vvv student@192.168.1.100

# 常见问题：
# - Permission denied (publickey)：公钥未正确配置或权限不正确
# - Connection refused：SSH 服务未启动或防火墙阻止
# - Connection timed out：网络不通或 IP 地址错误
```

---

## 7. NFS 和 TFTP 服务配置

### 7.1 概述

在嵌入式开发中，NFS（Network File System）和 TFTP（Trivial File Transfer Protocol）是两种最常用的文件传输协议：

| 协议 | 端口 | 用途 | 传输层 |
|------|------|------|--------|
| NFS | 2049 (TCP/UDP) | 通过网络共享文件系统（如挂载开发板的根文件系统） | 基于 RPC |
| TFTP | 69 (UDP) | 传输内核映像、设备树、引导加载程序等二进制文件 | UDP |
| SCP | 22 (TCP) | 文件拷贝（基于 SSH） | TCP |

**典型开发流程：**

```
PC（Ubuntu 主机）                 开发板（目标板）
  |                                    |
  |--- TFTP：发送 zImage/DTB --------->|  （U-Boot 阶段）
  |--- NFS：挂载 /srv/nfs/rootfs ----->|  （内核启动阶段）
  |--- SSH：调试和交互监控 ------------>|  （系统运行阶段）
```

### 7.2 NFS 服务配置

**（1）安装 NFS 服务器：**

```bash
sudo apt update
sudo apt install -y nfs-kernel-server
```

**（2）创建共享目录：**

```bash
# 创建 NFS 根文件系统目录
sudo mkdir -p /srv/nfs/rootfs

# 设置权限（允许所有用户访问，嵌入式开发常用）
sudo chmod 777 /srv/nfs/rootfs

# 也可以使用 nobody:nogroup
sudo chown nobody:nogroup /srv/nfs/rootfs
```

**（3）配置导出目录：**

```bash
# 编辑导出配置文件
sudo vim /etc/exports
```

添加以下内容：

```
# 格式：共享目录    客户机(选项)
/srv/nfs/rootfs    *(rw,sync,no_subtree_check,no_root_squash)
```

**配置选项说明：**

| 选项 | 含义 |
|------|------|
| `*` | 允许所有客户端连接（可限制为特定 IP，如 `192.168.1.0/24`） |
| `rw` | 读写权限 |
| `sync` | 同步写入（数据写入磁盘后才返回确认，更安全） |
| `no_subtree_check` | 禁用子目录检查，提高稳定性 |
| `no_root_squash` | 允许客户端的 root 用户拥有管理员权限（嵌入式调试需要） |

**（4）启动 NFS 服务：**

```bash
# 重新加载 exports 配置
sudo exportfs -rav

# 查看已导出的目录
sudo exportfs -v

# 重启 NFS 服务
sudo systemctl restart nfs-kernel-server

# 设置开机自启
sudo systemctl enable nfs-kernel-server
```

**（5）测试 NFS 挂载：**

```bash
# 在本地测试（将共享目录挂载到 /mnt）
sudo mount -t nfs 127.0.0.1:/srv/nfs/rootfs /mnt

# 验证挂载成功
ls /mnt

# 卸载测试挂载
sudo umount /mnt
```

**（6）在开发板上挂载 NFS（即客户端侧）：**

在 U-Boot 启动或 Linux 内核启动参数中设置：

```
# 内核启动参数示例
root=/dev/nfs nfsroot=192.168.1.10:/srv/nfs/rootfs,nfsvers=3 ip=192.168.1.100
```

或者在开发板的 Linux 中手动挂载：

```bash
# 在开发板上执行
mount -t nfs -o nolock 192.168.1.10:/srv/nfs/rootfs /mnt
```

### 7.3 TFTP 服务配置

**（1）安装 TFTP 服务器：**

```bash
sudo apt update
sudo apt install -y tftpd-hpa tftp-hpa
```

**（2）配置 TFTP 服务：**

```bash
# 编辑配置
sudo vim /etc/default/tftpd-hpa
```

配置文件内容：

```bash
# TFTP 配置
TFTP_USERNAME="tftp"
TFTP_DIRECTORY="/srv/tftp"          # TFTP 根目录
TFTP_ADDRESS="0.0.0.0:69"          # 监听所有网卡的 69 端口
TFTP_OPTIONS="--secure --create"    # --secure 限制在根目录内，--create 允许上传
```

**（3）创建 TFTP 目录并设置权限：**

```bash
# 创建 TFTP 共享目录
sudo mkdir -p /srv/tftp

# 设置权限
sudo chmod 777 /srv/tftp

# 将内核映像 zImage 和设备树文件复制到 TFTP 目录
cp zImage /srv/tftp/
cp imx6ull-14x14-evk.dtb /srv/tftp/
```

**（4）启动 TFTP 服务：**

```bash
# 重启 TFTP 服务
sudo systemctl restart tftpd-hpa

# 设置开机自启
sudo systemctl enable tftpd-hpa

# 检查服务状态
sudo systemctl status tftpd-hpa

# 检查端口监听（UDP 69）
sudo netstat -tuln | grep :69
```

**（5）测试 TFTP 服务：**

```bash
# 在主机本地测试
tftp 127.0.0.1
tftp> get zImage
tftp> quit

# 或者使用 -c 模式直接下载
tftp 127.0.0.1 -c get zImage

# 查看 TFTP 日志（排查错误时使用）
sudo tail -f /var/log/syslog | grep tftp
```

**（6）在 U-Boot 中使用 TFTP 加载内核（开发板侧）：**

在开发板的 U-Boot 命令行中：

```
# 设置网络参数
setenv ipaddr 192.168.1.100          # 开发板 IP
setenv serverip 192.168.1.10         # Ubuntu 主机 IP（TFTP 服务器）
setenv netmask 255.255.255.0

# 通过 TFTP 下载内核和设备树
tftp 0x80800000 zImage              # 将 zImage 加载到内存地址 0x80800000
tftp 0x83000000 imx6ull-14x14-evk.dtb  # 加载设备树

# 启动内核
bootz 0x80800000 - 0x83000000
```

### 7.4 防火墙配置

如果启用了 `ufw` 防火墙，需要放行相关端口：

```bash
# NFS 相关端口
sudo ufw allow 2049/tcp
sudo ufw allow 2049/udp

# TFTP 端口
sudo ufw allow 69/udp

# 重新加载防火墙
sudo ufw reload
```

---

## 8. Minicom 串口工具配置

### 8.1 串口通信简介

串口（Serial Port）是嵌入式开发中最基础、最重要的调试接口。开发板通常通过 UART（Universal Asynchronous Receiver/Transmitter）将调试信息输出到串口，用户可以通过串口终端与开发板的 Linux 系统或 U-Boot 交互。

**为什么使用串口：**

- 开发板在没有网络和显示接口时，串口是唯一的交互方式
- U-Boot 引导加载程序通常只通过串口输出调试信息
- Linux 内核的早期启动日志（`earlycon`）通过串口输出
- 串口协议简单、工具成熟、调试可靠

### 8.2 安装 Minicom

```bash
sudo apt update
sudo apt install -y minicom
```

### 8.3 串口设备识别

```bash
# 查看系统中所有串口设备
ls -l /dev/ttyS*
ls -l /dev/ttyUSB*
ls -l /dev/ttyAMA*

# 实际硬件串口：ttyS0、ttyS1...
# USB 转串口适配器：ttyUSB0、ttyUSB1...
# 树莓派等平台：ttyAMA0
```

**常见串口设备类型：**

| 设备节点 | 说明 | 常见场景 |
|----------|------|----------|
| `/dev/ttyUSB0` | USB 转串口适配器 | 最常用，通过 CH340/PL2303/FT232 转换 |
| `/dev/ttyS0` | 主板原生串口 | 台式机或工控机 |
| `/dev/ttyAMA0` | ARM 平台串口 | 树莓派、开发板原生串口 |

### 8.4 Minicom 基本配置

```bash
# 启动 Minicom 配置界面
sudo minicom -s
```

进入配置界面后，操作如下：

```
选择 "Serial port setup" 进入串口设置
  +-----------------------------------------------------------------------+
  | A - Serial Device      : /dev/ttyUSB0                                 |
  | B - Lockfile Location  : /var/lock                                    |
  | C - Callin Program     :                                              |
  | D - Callout Program    :                                              |
  | E - Bps/Par/Bits       : 115200 8N1                                   |
  | F - Hardware Flow Control : No                                        |
  | G - Software Flow Control : No                                        |
  |                                                                       |
  | Change which setting?                                                 |
  +-----------------------------------------------------------------------+
```

**关键配置项说明：**

- **串口设备（A）**：改成实际连接的设备节点，如 `/dev/ttyUSB0`
- **波特率（E）**：按 `E` 键进入设置，选择 `115200 8N1`
  - `115200`：波特率（常见值 9600、19200、38400、115200、921600）
  - `8`：数据位（8 位）
  - `N`：无奇偶校验（None）
  - `1`：停止位（1 位）
- **硬件流控（F）**：设为 `No`（大部分开发板不需要）
- **软件流控（G）**：设为 `No`

设置完成后：

1. 选择 `Exit` 返回主菜单
2. 选择 `Save setup as dfl` 保存为默认配置
3. 选择 `Exit` 退出配置，进入 Minicom 终端

### 8.5 Minicom 常用操作命令

**退出 Minicom：**

按下 `Ctrl+A`，松开，再按 `Z` 打开帮助菜单，然后按 `X` 退出。

**常用快捷键：**

| 快捷键 | 功能 |
|--------|------|
| `Ctrl+A` `Z` | 打开帮助菜单 |
| `Ctrl+A` `X` | 退出 Minicom |
| `Ctrl+A` `C` | 清屏 |
| `Ctrl+A` `B` | 查看串口缓冲区内容 |
| `Ctrl+A` `L` | 将串口输出记录到文件 |
| `Ctrl+A` `O` | 配置选项（临时修改） |
| `Ctrl+A` `W` | 自动换行开关 |
| `Ctrl+A` `P` | 添加换页符 |

### 8.6 连接开发板实操

```bash
# 1. 确认串口设备
ls /dev/ttyUSB*

# 2. 启动 Minicom（使用默认配置）
sudo minicom

# 3. 或使用命令行指定配置直接启动
sudo minicom -D /dev/ttyUSB0 -b 115200
```

**参数说明：**
- `-D`：指定串口设备
- `-b`：设置波特率

**连接开发板的典型输出：**

```
U-Boot 2020.04 (Apr 10 2024 - 16:30:00 +0800)

CPU:   i.MX6ULL
Model: Embedded-KB EVK Board
Board: EVK
DRAM:  256 MiB
MMC:   FSL_SDHC: 0, FSL_SDHC: 1
Net:   FEC0 [PRIME]

Hit any key to stop autoboot:  0
=>
```

### 8.7 Minicom 替代工具

除了 Minicom，还有其他常用的串口工具：

**（1）screen：**

```bash
# 安装 screen
sudo apt install -y screen

# 连接串口
sudo screen /dev/ttyUSB0 115200

# 退出：Ctrl+A 然后输入 :quit
```

**（2）picocom（轻量简洁）：**

```bash
# 安装 picocom
sudo apt install -y picocom

# 连接串口
sudo picocom -b 115200 /dev/ttyUSB0

# 退出：Ctrl+A 然后 Ctrl+X
```

**（3）putty（图形化）：**

```bash
sudo apt install -y putty
```

### 8.8 串口调试常见问题排查

| 问题 | 可能原因 | 解决方法 |
|------|----------|----------|
| `No such file or directory` | 未连接串口线或驱动未安装 | `ls /dev/tty*` 检查设备 |
| `Permission denied` | 用户无权限访问串口设备 | 使用 `sudo` 或加入 `dialout` 组 |
| 屏幕显示乱码 | 波特率不匹配 | 确认开发板实际波特率（常见 115200） |
| 无任何输出 | 串口线接错或流控设置错误 | 交换 TX/RX 线，关闭流控 |
| minicom 启动报错 | 设备被占用 | 检查是否有其他程序在使用串口 |

**将用户加入 dialout 组（避免每次使用 sudo）：**

```bash
sudo usermod -a -G dialout $USER
# 注销重新登录后生效
```

---

## 9. 面试练习题

以下面试题覆盖本章核心知识点，帮助检验学习效果。

### 题目 1

```json
{
  "type": "SINGLE",
  "stem": "在嵌入式 Linux 开发中，以下哪个 LTS 版本的 Ubuntu 在 2026 年仍处于标准支持期内且推荐新项目使用？",
  "options": [
    "A) Ubuntu 18.04 LTS",
    "B) Ubuntu 20.04 LTS",
    "C) Ubuntu 24.04 LTS",
    "D) Ubuntu 16.04 LTS"
  ],
  "answer": "C",
  "analysis": "Ubuntu 24.04 LTS 发布于 2024 年，标准支持至 2029 年，在 2026 年仍然处于支持期内，并且组件较新。18.04 和 20.04 的标准支持已结束或即将结束（20.04 至 2025 年），而 16.04 早已结束支持。选 C。"
}
```

### 题目 2

```json
{
  "type": "SINGLE",
  "stem": "在配置 VMware 虚拟机中的 Ubuntu 时，为了实现鼠标无缝切换和剪贴板共享，需要安装哪个软件包？",
  "options": [
    "A) linux-tools-generic",
    "B) open-vm-tools-desktop",
    "C) virtualbox-guest-additions",
    "D) vmware-esx-tools"
  ],
  "answer": "B",
  "analysis": "open-vm-tools 和 open-vm-tools-desktop 是 VMware 官方为 Linux 客户机提供集成服务的开源工具包。open-vm-tools-desktop 包含图形化增强功能（鼠标无缝切换、剪贴板共享、拖拽文件等）。选项 C 是 VirtualBox 的增强工具，不适用于 VMware。"
}
```

### 题目 3

```json
{
  "type": "SINGLE",
  "stem": "在 TFTP 服务配置中，默认监听端口是哪个？使用什么传输层协议？",
  "options": [
    "A) 端口 21，TCP 协议",
    "B) 端口 69，UDP 协议",
    "C) 端口 2049，TCP 协议",
    "D) 端口 22，TCP 协议"
  ],
  "answer": "B",
  "analysis": "TFTP（Trivial File Transfer Protocol）基于 UDP 协议，默认监听端口号为 69。TFTP 设计简洁，无认证机制，适合在局域网中传输文件（如 U-Boot 启动时下载内核映像）。端口 21 是 FTP，端口 2049 是 NFS，端口 22 是 SSH。"
}
```

### 题目 4

```json
{
  "type": "SINGLE",
  "stem": "配置 Minicom 串口工具时，最常用的波特率、数据位、奇偶校验、停止位组合（Bps/Par/Bits）是下列哪一项？",
  "options": [
    "A) 9600 7E1",
    "B) 115200 8N1",
    "C) 57600 8N2",
    "D) 38400 7N1"
  ],
  "answer": "B",
  "analysis": "嵌入式开发中，串口通信最常用的参数是 115200 8N1，即波特率 115200 bps、8 个数据位、无奇偶校验（None）、1 个停止位。大多数开发板的 U-Boot 和 Linux 内核默认使用此配置。选项 A 的 7E1 在老式系统中出现，但现代嵌入式系统几乎统一使用 8N1。"
}
```

### 题目 5

```json
{
  "type": "SINGLE",
  "stem": "以下哪种场景最适合使用 NFS 服务？",
  "options": [
    "A) 在 U-Boot 引导阶段加载内核映像",
    "B) 在两台 Linux 主机之间同步文件",
    "C) 将开发板的根文件系统放在 Ubuntu 主机上，通过网络远程挂载",
    "D) 通过浏览器下载 Ubuntu ISO 镜像"
  ],
  "answer": "C",
  "analysis": "NFS（Network File System）允许客户端通过网络挂载远程文件系统。在嵌入式开发中，NFS 常用于将开发板的根文件系统（rootfs）存放在 Ubuntu 主机上，开发板通过内核启动参数 nfsroot 远程挂载。这样在主机上修改代码后，开发板重启即可生效，无需反复烧写 Flash。选项 A 使用 TFTP，选项 D 使用 HTTP/HTTPS，选项 B 是 NFS 的应用之一但非嵌入式特有最佳场景。"
}
```

---

> **下一章预告：** 02-Linux 基础命令与嵌入式开发入门
>
> 掌握 Ubuntu 开发环境后，下一章将学习 Linux 文件系统结构、常用 Shell 命令、文件权限管理、进程管理等嵌入式开发必备的 Linux 基础知识。
