# Linux 系统 I/O 基础

> 本章目标：理解 Linux 为什么把设备和文件统一成“文件接口”，并能用 `open/read/write/lseek/close` 完成基础文件操作。

## 1. 从“直接操作硬件”到“通过操作系统访问资源”

在没有操作系统的简单系统中，应用程序可能直接访问硬件寄存器。这种方式直观，但有几个明显问题：

- 应用必须理解硬件细节。
- 很难让多个程序同时运行。
- 资源管理、权限控制和错误恢复都要自己处理。

在 Linux 中，应用通常不直接操作硬件，而是调用内核提供的 API。内核负责屏蔽硬件差异，并把常见资源抽象成文件。

## 2. Linux 的核心思想：一切皆文件

Linux/Unix 系统里，很多资源都可以通过文件接口访问：

| 资源 | 常见形式 |
|---|---|
| 普通文件 | `/home/user/data.txt` |
| 目录 | `/home/user/project` |
| 设备 | `/dev/fb0`、`/dev/input/event0` |
| 管道 | pipe、FIFO |
| socket | 网络通信端点 |

这带来的好处是：应用只要掌握文件 I/O 的基本接口，就能处理许多不同类型的资源。

## 3. 文件描述符

系统 I/O 使用“文件描述符”标识一个已经打开的文件。

```text
文件描述符是一个非负整数。
open 成功后返回文件描述符。
read/write/close 都通过文件描述符操作文件。
```

进程启动后默认已经打开 3 个文件描述符：

| fd | 名称 | 说明 |
|---:|---|---|
| `0` | stdin | 标准输入 |
| `1` | stdout | 标准输出 |
| `2` | stderr | 标准错误 |

## 4. open：打开文件

```c
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int fd = open("data.txt", O_RDONLY);
if (fd < 0) {
    perror("open");
}
```

常见打开标志：

| 标志 | 含义 |
|---|---|
| `O_RDONLY` | 只读 |
| `O_WRONLY` | 只写 |
| `O_RDWR` | 读写 |
| `O_CREAT` | 不存在则创建 |
| `O_TRUNC` | 打开时清空 |
| `O_APPEND` | 追加写 |

创建文件时需要指定权限：

```c
int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
```

## 5. read / write：读写文件

读取文件：

```c
#include <unistd.h>

char buf[128];
ssize_t n = read(fd, buf, sizeof(buf));
if (n < 0) {
    perror("read");
}
```

写入文件：

```c
const char msg[] = "hello\n";
ssize_t n = write(fd, msg, sizeof(msg) - 1);
if (n < 0) {
    perror("write");
}
```

返回值含义：

| 函数 | 返回值 |
|---|---|
| `read` | 实际读到的字节数；`0` 表示文件结束；`-1` 表示错误 |
| `write` | 实际写入的字节数；`-1` 表示错误 |

> 注意：`read` 和 `write` 不保证一次处理完你想要的全部字节，严谨程序要处理短读和短写。

## 6. lseek：移动文件偏移量

每个打开的文件都有一个当前偏移量，类似“光标”。

```c
#include <unistd.h>

lseek(fd, 0, SEEK_SET);   // 回到文件开头
lseek(fd, 0, SEEK_END);   // 移动到文件末尾
lseek(fd, 10, SEEK_CUR);  // 从当前位置向后移动 10 字节
```

常见用途：

- 获取文件大小。
- 跳过文件头。
- 修改指定位置的数据。

获取文件大小示例：

```c
off_t size = lseek(fd, 0, SEEK_END);
lseek(fd, 0, SEEK_SET);
```

## 7. close：关闭文件

```c
close(fd);
```

关闭文件很重要：

- 释放文件描述符。
- 让内核回收相关资源。
- 对某些设备或文件系统，关闭时可能触发最终同步。

## 8. 完整示例：复制文件

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <src> <dst>\n", argv[0]);
        return 1;
    }

    int in = open(argv[1], O_RDONLY);
    if (in < 0) {
        perror("open src");
        return 1;
    }

    int out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) {
        perror("open dst");
        close(in);
        return 1;
    }

    char buf[4096];
    ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        char *p = buf;
        ssize_t left = n;
        while (left > 0) {
            ssize_t written = write(out, p, left);
            if (written < 0) {
                perror("write");
                close(in);
                close(out);
                return 1;
            }
            p += written;
            left -= written;
        }
    }

    if (n < 0) {
        perror("read");
    }

    close(in);
    close(out);
    return n < 0 ? 1 : 0;
}
```

## 9. 易错点

- 忘记检查 `open/read/write` 返回值。
- 创建文件时忘记传第三个权限参数。
- 把文件描述符和 `FILE *` 混用。
- 认为 `write` 一次一定写完所有数据。
- 忘记关闭不再使用的文件描述符。

## 10. 自学任务

1. 写程序打开一个文本文件并打印内容。
2. 写程序复制任意文件。
3. 用 `lseek` 获取文件大小。
4. 尝试用 `O_APPEND` 追加写日志。
5. 故意打开不存在的文件，观察 `perror` 输出。

## 11. 本章检查清单

- [ ] 能解释文件描述符是什么。
- [ ] 能写出 `open/read/write/close` 基本流程。
- [ ] 能区分系统 I/O 和标准 I/O 的接口类型。
- [ ] 能使用 `lseek` 操作文件偏移量。
- [ ] 能处理系统调用返回值和错误信息。
