# IPC：信号

> 本章目标：理解信号是一种异步通知机制，并能安全地处理常见信号。

## 1. 信号是什么

信号是 Linux 提供的轻量级异步通知机制。它可以通知进程：某个事件发生了。

常见事件：

- 用户按下 `Ctrl+C`。
- 定时器到期。
- 子进程退出。
- 程序访问非法内存。
- 其他进程发送通知。

信号不是用来传输大量数据的，它更像“提醒”。

## 2. 常见信号

| 信号 | 默认行为 | 典型来源 |
|---|---|---|
| `SIGINT` | 终止进程 | `Ctrl+C` |
| `SIGTERM` | 终止进程 | 请求进程正常退出 |
| `SIGKILL` | 强制终止 | 无法捕获或忽略 |
| `SIGALRM` | 终止进程 | `alarm` 定时器 |
| `SIGCHLD` | 忽略 | 子进程状态变化 |
| `SIGSEGV` | 终止并可能生成调试信息 | 非法内存访问 |
| `SIGPIPE` | 终止进程 | 管道读端关闭后继续写 |

## 3. 发送信号

命令行发送：

```bash
kill -TERM <pid>
kill -9 <pid>
```

C 程序中发送：

```c
#include <signal.h>
#include <sys/types.h>

kill(pid, SIGTERM);
```

给自己发送信号：

```c
#include <signal.h>

raise(SIGINT);
```

## 4. 安装信号处理函数

简单写法：

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void on_sigint(int signo) {
    write(STDOUT_FILENO, "caught SIGINT\n", 14);
}

int main(void) {
    signal(SIGINT, on_sigint);

    while (1) {
        pause();
    }
}
```

> 注意：信号处理函数运行在异步上下文里，不建议在里面做复杂逻辑。

## 5. 使用 sigaction

`sigaction` 比 `signal` 更明确、更适合实际开发。

```c
#include <signal.h>
#include <string.h>
#include <unistd.h>

void handler(int signo) {
    const char msg[] = "signal arrived\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(void) {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);

    sigaction(SIGTERM, &act, NULL);

    while (1) {
        pause();
    }
}
```

## 6. alarm 定时器

`alarm` 可以让系统在指定秒数后给当前进程发送 `SIGALRM`。

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void on_alarm(int signo) {
    write(STDOUT_FILENO, "timeout\n", 8);
}

int main(void) {
    signal(SIGALRM, on_alarm);
    alarm(3);
    pause();
    return 0;
}
```

## 7. 信号处理的安全原则

信号是异步到达的，所以处理函数越短越好。

建议：

- 在处理函数中只设置标志位或写入管道。
- 避免调用复杂库函数。
- 避免在处理函数中使用不可重入函数。
- 主循环中检查标志位，再执行真正逻辑。

示例：

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t stop = 0;

void on_sigterm(int signo) {
    stop = 1;
}

int main(void) {
    signal(SIGTERM, on_sigterm);

    while (!stop) {
        sleep(1);
    }

    printf("clean exit\n");
    return 0;
}
```

## 8. 易错点

- `SIGKILL` 和 `SIGSTOP` 不能被捕获、阻塞或忽略。
- 信号不是普通函数调用，它可能在任意时刻打断当前执行流。
- 不要把大量业务逻辑放到信号处理函数里。
- `pause` 会一直等待，直到收到信号。
- 处理子进程退出时，常结合 `SIGCHLD` 和 `waitpid`。

## 9. 自学任务

1. 写程序捕获 `Ctrl+C`，打印提示但不退出。
2. 使用 `alarm` 实现 5 秒超时提示。
3. 用 `kill` 给另一个进程发送 `SIGTERM`。
4. 尝试捕获 `SIGKILL`，观察是否可行。
5. 使用 `volatile sig_atomic_t` 控制主循环退出。

## 10. 本章检查清单

- [ ] 能解释信号的异步通知特点。
- [ ] 能使用 `kill` 和 `raise` 发送信号。
- [ ] 能用 `signal` 或 `sigaction` 安装处理函数。
- [ ] 知道哪些信号不能被捕获。
- [ ] 知道信号处理函数中不应做复杂逻辑。
