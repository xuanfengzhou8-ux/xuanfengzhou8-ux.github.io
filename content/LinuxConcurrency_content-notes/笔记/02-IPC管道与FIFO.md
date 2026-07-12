# IPC：管道与 FIFO

> 本章目标：理解进程之间如何通过管道传递字节流，并区分无名管道和有名管道。

## 1. 什么是 IPC

IPC 是进程间通信。由于进程地址空间相互隔离，一个进程不能直接访问另一个进程的变量，因此需要由内核提供通信机制。

常见 IPC：

- 管道 pipe
- FIFO 有名管道
- 信号 signal
- 共享内存 shared memory
- 信号量 semaphore
- 消息队列 message queue
- socket

## 2. 无名管道 pipe

无名管道是内核中的一段缓冲区，表现为两个文件描述符：

```text
fd[0]：读端
fd[1]：写端
```

创建管道：

```c
#include <unistd.h>

int fd[2];
if (pipe(fd) < 0) {
    perror("pipe");
}
```

典型特点：

- 适合有亲缘关系的进程，例如父子进程。
- 默认是半双工通信：一个方向写，一个方向读。
- 数据是字节流，没有消息边界。
- 读写都通过文件描述符完成。

## 3. 父子进程管道通信

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        close(fd[1]);
        char buf[64] = {0};
        read(fd[0], buf, sizeof(buf) - 1);
        printf("child read: %s\n", buf);
        close(fd[0]);
        return 0;
    }

    close(fd[0]);
    const char *msg = "hello pipe";
    write(fd[1], msg, strlen(msg));
    close(fd[1]);

    wait(NULL);
    return 0;
}
```

关键点：

- 子进程只读，所以关闭写端。
- 父进程只写，所以关闭读端。
- 不使用的端口要及时关闭，否则读端可能一直等不到 EOF。

## 4. 管道阻塞规则

| 情况 | 结果 |
|---|---|
| 管道为空，读端读 | 默认阻塞等待数据 |
| 管道满，写端写 | 默认阻塞等待空间 |
| 所有写端关闭，读端读 | 返回 0，表示 EOF |
| 所有读端关闭，写端写 | 可能收到 `SIGPIPE` |

## 5. FIFO 有名管道

FIFO 是文件系统中可见的管道文件。它适合没有亲缘关系的进程通信。

创建 FIFO：

```bash
mkfifo /tmp/demo_fifo
```

也可以在 C 程序中创建：

```c
#include <sys/stat.h>

mkfifo("/tmp/demo_fifo", 0666);
```

写端：

```bash
echo "hello fifo" > /tmp/demo_fifo
```

读端：

```bash
cat /tmp/demo_fifo
```

## 6. C 程序中使用 FIFO

读进程：

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int fd = open("/tmp/demo_fifo", O_RDONLY);
    char buf[64] = {0};
    read(fd, buf, sizeof(buf) - 1);
    printf("read: %s\n", buf);
    close(fd);
    return 0;
}
```

写进程：

```c
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int fd = open("/tmp/demo_fifo", O_WRONLY);
    const char *msg = "hello";
    write(fd, msg, strlen(msg));
    close(fd);
    return 0;
}
```

## 7. pipe 与 FIFO 对比

| 对比项 | pipe | FIFO |
|---|---|---|
| 是否有路径名 | 没有 | 有 |
| 适用进程 | 常用于父子进程 | 可用于无亲缘关系进程 |
| 创建方式 | `pipe()` | `mkfifo()` / `mkfifo` 命令 |
| 通信形式 | 字节流 | 字节流 |
| 生命周期 | 随文件描述符关闭释放 | 文件存在，管道对象按打开状态存在 |

## 8. 易错点

- 管道不是消息队列，读写边界不一定对应。
- 双向通信不要试图只用一个 pipe 简单解决，通常需要两个 pipe。
- 不关闭无用端会导致阻塞问题。
- FIFO 的 `open` 可能阻塞，取决于读写端是否都已打开。

## 9. 自学任务

1. 写一个父进程向子进程发送字符串的 pipe 程序。
2. 修改程序，让子进程返回处理结果给父进程，思考为什么需要两个 pipe。
3. 用 `mkfifo` 创建 FIFO，并用两个终端分别读写。
4. 写两个 C 程序通过 FIFO 通信。
5. 故意不关闭写端，观察读端是否能正常结束。

## 10. 本章检查清单

- [ ] 能解释 IPC 的必要性。
- [ ] 能区分 `fd[0]` 和 `fd[1]`。
- [ ] 能写出父子进程 pipe 通信。
- [ ] 能创建并使用 FIFO。
- [ ] 能解释管道阻塞和 EOF 的常见情况。
