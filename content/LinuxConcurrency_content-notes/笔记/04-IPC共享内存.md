# IPC：共享内存

> 本章目标：理解共享内存为什么快，以及为什么它必须配合同步机制使用。

## 1. 共享内存是什么

共享内存允许多个进程把同一段物理内存映射到自己的虚拟地址空间。映射完成后，进程可以像访问普通内存一样读写它。

简化理解：

```text
进程 A 地址空间  --->  同一段物理内存  <---  进程 B 地址空间
```

共享内存的特点：

- 数据不需要在进程和内核之间反复复制，效率高。
- 适合传输大量数据。
- 本身不提供互斥，需要信号量、互斥锁等机制保护。

## 2. System V 共享内存流程

典型步骤：

1. 使用 `ftok` 生成 key。
2. 使用 `shmget` 创建或获取共享内存对象。
3. 使用 `shmat` 映射到当前进程地址空间。
4. 像普通内存一样读写。
5. 使用 `shmdt` 解除映射。
6. 使用 `shmctl` 删除共享内存对象。

## 3. 创建共享内存

```c
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main(void) {
    key_t key = ftok(".", 1);
    if (key < 0) {
        perror("ftok");
        return 1;
    }

    int shmid = shmget(key, 4096, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    printf("shmid = %d\n", shmid);
    return 0;
}
```

## 4. 写入共享内存

```c
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void) {
    key_t key = ftok(".", 1);
    int shmid = shmget(key, 4096, IPC_CREAT | 0666);

    char *addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1) {
        perror("shmat");
        return 1;
    }

    strcpy(addr, "hello shared memory");
    shmdt(addr);
    return 0;
}
```

## 5. 读取共享内存

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void) {
    key_t key = ftok(".", 1);
    int shmid = shmget(key, 4096, 0666);

    char *addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1) {
        perror("shmat");
        return 1;
    }

    printf("data = %s\n", addr);
    shmdt(addr);
    return 0;
}
```

## 6. 删除共享内存

共享内存对象不会因为进程退出就自动删除。可以使用：

```c
shmctl(shmid, IPC_RMID, NULL);
```

也可以在命令行查看和删除：

```bash
ipcs -m
ipcrm -m <shmid>
```

## 7. 为什么需要同步

如果一个进程正在写，另一个进程同时读，可能读到半更新的数据。

错误示意：

```text
写进程：写入前半段 ---- 写入后半段
读进程：        读取到了不完整数据
```

所以共享内存通常搭配：

- System V 信号量
- POSIX 信号量
- 进程共享互斥锁
- futex 等同步机制

## 8. 共享内存与管道对比

| 对比项 | 共享内存 | 管道/FIFO |
|---|---|---|
| 数据形式 | 内存区域 | 字节流 |
| 拷贝开销 | 低 | 相对更高 |
| 是否自带同步 | 否 | 读写阻塞可提供部分同步 |
| 适合场景 | 大块数据、高频交换 | 简单字节流通信 |
| 使用复杂度 | 较高 | 较低 |

## 9. 易错点

- `shmat` 失败返回 `(void *)-1`，不是 `NULL`。
- 创建后不删除，会残留共享内存对象。
- 共享内存只解决“共享数据”，不解决“访问顺序”。
- 结构体写入共享内存时，要注意不同程序的结构体布局一致。

## 10. 自学任务

1. 写两个程序，一个写共享内存，一个读共享内存。
2. 用 `ipcs -m` 查看共享内存对象。
3. 用 `ipcrm -m` 删除共享内存对象。
4. 尝试同时运行多个写进程，观察数据覆盖问题。
5. 思考如何用信号量保护共享内存。

## 11. 本章检查清单

- [ ] 能说出共享内存为什么快。
- [ ] 能写出 `ftok -> shmget -> shmat -> shmdt` 流程。
- [ ] 知道如何删除共享内存对象。
- [ ] 知道共享内存必须配合同步机制。
- [ ] 能区分共享内存和管道的适用场景。
