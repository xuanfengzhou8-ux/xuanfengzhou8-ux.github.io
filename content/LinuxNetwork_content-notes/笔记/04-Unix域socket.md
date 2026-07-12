# Unix 域 socket

> 本章目标：理解同一主机内进程通信为什么可以使用 Unix 域 socket，并能写出基础通信流程。

## 1. Unix 域 socket 是什么

Unix 域 socket 也叫本地 socket。它不通过 IP 网络通信，而是在同一台主机内部完成进程间通信。

特点：

- 适合同一台主机上的进程通信。
- 不需要 IP 和端口。
- 常通过文件系统路径标识服务端地址。
- 接口风格和网络 socket 很像。

## 2. 地址结构 sockaddr_un

```c
#include <sys/un.h>

struct sockaddr_un addr;
addr.sun_family = AF_UNIX;
strncpy(addr.sun_path, "/tmp/demo.sock", sizeof(addr.sun_path) - 1);
```

`sun_path` 是 socket 文件路径。

## 3. 服务端流程

```text
socket -> unlink旧路径 -> bind -> listen -> accept -> read/write -> close
```

为什么要 `unlink`？

如果上一次程序异常退出，路径文件可能残留，导致新的 `bind` 失败。

## 4. 服务端示例

```c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(void) {
    const char *path = "/tmp/demo.sock";
    int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        return 1;
    }

    unlink(path);

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(listen_fd);
        return 1;
    }

    listen(listen_fd, 8);

    int conn_fd = accept(listen_fd, NULL, NULL);
    char buf[128] = {0};
    ssize_t n = read(conn_fd, buf, sizeof(buf) - 1);
    if (n > 0) {
        write(conn_fd, buf, n);
    }

    close(conn_fd);
    close(listen_fd);
    unlink(path);
    return 0;
}
```

## 5. 客户端示例

```c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(void) {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_un server;
    memset(&server, 0, sizeof(server));
    server.sun_family = AF_UNIX;
    strncpy(server.sun_path, "/tmp/demo.sock", sizeof(server.sun_path) - 1);

    if (connect(fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(fd);
        return 1;
    }

    const char msg[] = "hello unix socket";
    write(fd, msg, sizeof(msg) - 1);

    char buf[128] = {0};
    read(fd, buf, sizeof(buf) - 1);
    printf("reply: %s\n", buf);

    close(fd);
    return 0;
}
```

## 6. 与 TCP 本地回环通信对比

| 对比项 | Unix 域 socket | TCP 回环 |
|---|---|---|
| 通信范围 | 同一主机 | 同一主机或网络 |
| 地址 | 文件路径 | IP + 端口 |
| 开销 | 通常更低 | 经过网络协议栈 |
| 权限控制 | 可结合文件权限 | 依赖端口和网络策略 |

## 7. 常见用途

- 本地服务和客户端通信。
- 守护进程控制接口。
- 多进程程序内部通信。
- 需要比 TCP 回环更轻量的本机 IPC。

## 8. 易错点

- `bind` 前没有清理旧 socket 路径。
- `sun_path` 超长被截断。
- 程序退出时忘记删除 socket 文件。
- 把 Unix 域 socket 当成跨主机通信方式。

## 9. 自学任务

1. 写一个 Unix 域 echo 服务端和客户端。
2. 观察 `/tmp/demo.sock` 文件何时出现。
3. 故意不 `unlink`，再次启动服务端观察错误。
4. 对比 TCP 127.0.0.1 echo 与 Unix 域 echo。

## 10. 本章检查清单

- [ ] 能解释 Unix 域 socket 的使用场景。
- [ ] 能写出 `sockaddr_un`。
- [ ] 能说明为什么要清理旧 socket 路径。
- [ ] 能区分 Unix 域 socket 和 TCP 回环。
