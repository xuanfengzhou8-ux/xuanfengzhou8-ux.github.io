# UDP、广播与组播

> 本章目标：理解 UDP 数据报编程，并掌握广播、组播和常见 socket 选项的基本使用场景。

## 1. UDP 的特点

UDP 是无连接的数据报协议。它不保证可靠送达，也不保证顺序，但开销小、延迟低。

| 特性 | 说明 |
|---|---|
| 无连接 | 发送前不需要建立连接 |
| 数据报 | 一次发送对应一个数据报 |
| 不可靠 | 丢包、乱序、重复需要应用自己处理 |
| 轻量 | 适合实时或简单通信 |

典型场景：

- 局域网设备发现。
- 简单控制命令。
- 实时音视频数据。
- 周期性状态上报。

## 2. UDP 服务端流程

```text
socket -> bind -> recvfrom/sendto -> close
```

服务端通常需要 `bind` 到固定端口，这样客户端才知道发给谁。

```c
int fd = socket(AF_INET, SOCK_DGRAM, 0);
```

## 3. UDP 客户端流程

```text
socket -> sendto/recvfrom -> close
```

客户端可以不调用 `bind`，由内核分配临时端口。

## 4. UDP echo 服务端

```c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(9000);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr *)&local, sizeof(local)) < 0) {
        perror("bind");
        close(fd);
        return 1;
    }

    char buf[1024];
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);

    ssize_t n = recvfrom(fd, buf, sizeof(buf), 0,
                         (struct sockaddr *)&peer, &len);
    if (n > 0) {
        sendto(fd, buf, n, 0, (struct sockaddr *)&peer, len);
    }

    close(fd);
    return 0;
}
```

## 5. UDP 客户端

```c
int fd = socket(AF_INET, SOCK_DGRAM, 0);

struct sockaddr_in server;
memset(&server, 0, sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(9000);
inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

const char msg[] = "hello udp";
sendto(fd, msg, sizeof(msg) - 1, 0,
       (struct sockaddr *)&server, sizeof(server));
```

## 6. socket 选项

`setsockopt` 和 `getsockopt` 可以设置或读取 socket 参数。

```c
int on = 1;
setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
```

常见选项：

| 选项 | 作用 |
|---|---|
| `SO_REUSEADDR` | 允许地址复用 |
| `SO_BROADCAST` | 允许发送广播 |
| `SO_RCVBUF` | 设置接收缓冲区 |
| `SO_SNDBUF` | 设置发送缓冲区 |

## 7. 广播

广播用于向同一局域网内所有主机发送数据。发送广播前需要开启选项：

```c
int on = 1;
setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
```

广播地址示例：

```text
255.255.255.255
192.168.1.255
```

适合场景：

- 局域网设备发现。
- 简单状态广播。

注意：广播范围较大，不适合高频大量数据。

## 8. 组播

组播用于把数据发送给加入某个组播组的主机。

常见组播地址范围：

```text
224.0.0.0 ~ 239.255.255.255
```

加入组播组通常使用 `IP_ADD_MEMBERSHIP`。

```c
struct ip_mreq mreq;
mreq.imr_multiaddr.s_addr = inet_addr("239.0.0.1");
mreq.imr_interface.s_addr = htonl(INADDR_ANY);
setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
```

## 9. UDP 编程注意事项

- UDP 有消息边界，但不保证可靠。
- 接收缓冲区太小会导致数据被截断。
- 需要自己设计序号、确认、重传等可靠机制。
- 广播和组播需要注意网络环境和权限策略。
- UDP 服务端通常需要绑定固定端口。

## 10. 自学任务

1. 写一个 UDP echo 服务端和客户端。
2. 用 `SO_REUSEADDR` 解决端口复用问题。
3. 尝试发送局域网广播包。
4. 设计一个简单设备发现协议。
5. 思考 UDP 丢包时应用层如何补救。

## 11. 本章检查清单

- [ ] 能写出 UDP `sendto/recvfrom` 流程。
- [ ] 能解释 UDP 与 TCP 的差异。
- [ ] 能使用 `setsockopt` 设置常见选项。
- [ ] 能说明广播和组播适合的场景。
- [ ] 知道 UDP 可靠性需要应用层设计。
