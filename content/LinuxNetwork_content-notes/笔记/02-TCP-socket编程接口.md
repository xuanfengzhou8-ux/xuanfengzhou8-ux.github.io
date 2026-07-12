# TCP socket 编程接口

> 本章目标：掌握 TCP 服务端和客户端的基本编程流程，并理解监听套接字与连接套接字的区别。

## 1. socket 是什么

socket 是网络编程接口。在 Linux 中，它也表现为一种文件描述符，因此可以使用类似文件的读写方式。

常见 socket 类型：

| 类型 | 对应协议 | 特点 |
|---|---|---|
| `SOCK_STREAM` | TCP | 面向连接、字节流 |
| `SOCK_DGRAM` | UDP | 无连接、数据报 |
| `SOCK_RAW` | 原始套接字 | 更底层，通常需要特殊权限 |

TCP 编程通常使用：

```c
socket(AF_INET, SOCK_STREAM, 0);
```

## 2. TCP 服务端流程

```text
socket -> bind -> listen -> accept -> read/write -> close
```

每一步职责：

| 步骤 | 作用 |
|---|---|
| `socket` | 创建套接字 |
| `bind` | 绑定本地 IP 和端口 |
| `listen` | 进入监听状态 |
| `accept` | 接收客户端连接 |
| `read/write` | 收发数据 |
| `close` | 关闭连接 |

## 3. TCP 客户端流程

```text
socket -> connect -> read/write -> close
```

客户端通常不需要手动 `bind`，内核会自动分配本地临时端口。

## 4. 地址结构 sockaddr_in

```c
#include <netinet/in.h>
#include <arpa/inet.h>

struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(8080);
inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
```

字段说明：

| 字段 | 含义 |
|---|---|
| `sin_family` | 地址族，IPv4 使用 `AF_INET` |
| `sin_port` | 端口，必须使用网络字节序 |
| `sin_addr` | IP 地址 |

## 5. TCP 服务端示例

```c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(listen_fd);
        return 1;
    }

    if (listen(listen_fd, 8) < 0) {
        perror("listen");
        close(listen_fd);
        return 1;
    }

    int conn_fd = accept(listen_fd, NULL, NULL);
    if (conn_fd < 0) {
        perror("accept");
        close(listen_fd);
        return 1;
    }

    char buf[128] = {0};
    ssize_t n = read(conn_fd, buf, sizeof(buf) - 1);
    if (n > 0) {
        write(conn_fd, buf, n);
    }

    close(conn_fd);
    close(listen_fd);
    return 0;
}
```

## 6. TCP 客户端示例

```c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(fd);
        return 1;
    }

    const char msg[] = "hello tcp";
    write(fd, msg, sizeof(msg) - 1);

    char buf[128] = {0};
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n > 0) {
        printf("reply: %s\n", buf);
    }

    close(fd);
    return 0;
}
```

## 7. 监听套接字与连接套接字

服务端里有两类 fd：

| fd | 来源 | 作用 |
|---|---|---|
| 监听套接字 | `socket` 后 `bind/listen` | 等待新连接 |
| 连接套接字 | `accept` 返回 | 与某个客户端收发数据 |

不要在监听套接字上直接收发客户端业务数据。

## 8. 常用辅助函数

| 函数 | 作用 |
|---|---|
| `inet_pton` | 文本 IP 转二进制 |
| `inet_ntop` | 二进制 IP 转文本 |
| `htons` | 主机字节序端口转网络字节序 |
| `ntohs` | 网络字节序端口转主机字节序 |

## 9. 易错点

- 忘记 `htons`，导致端口错误。
- `bind` 失败后不看错误信息。
- 混淆监听套接字和连接套接字。
- 认为 TCP 一次 `read` 就能读到完整业务包。
- 服务端只能处理一个客户端，需要循环或并发模型扩展。

## 10. 自学任务

1. 写一个 TCP echo 服务端。
2. 写一个 TCP 客户端连接它。
3. 打印客户端 IP 和端口。
4. 把服务端改成循环 `accept`。
5. 思考如何结合多进程、多线程或 I/O 多路复用处理多个客户端。

## 11. 本章检查清单

- [ ] 能写出 TCP 服务端基本流程。
- [ ] 能写出 TCP 客户端基本流程。
- [ ] 能解释 `bind/listen/accept/connect` 的作用。
- [ ] 能区分监听套接字和连接套接字。
- [ ] 知道 TCP 是字节流，不保留应用消息边界。
