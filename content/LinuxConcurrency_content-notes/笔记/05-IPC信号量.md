# IPC：信号量

> 本章目标：理解信号量如何保护共享资源，并掌握 System V 与 POSIX 两类接口的基本用法。

## 1. 为什么需要信号量

多个进程或线程访问同一个资源时，如果没有同步控制，就可能出现竞争问题。

共享资源示例：

- 共享内存中的数据。
- 同一个日志文件。
- 同一个硬件设备。
- 同一个计数器。

信号量可以用来限制资源访问数量，也可以用来实现互斥。

## 2. P/V 操作

信号量可以看作一个计数器。

| 操作 | 含义 | 结果 |
|---|---|---|
| P / wait | 申请资源 | 计数减 1；如果不可用则阻塞 |
| V / post | 释放资源 | 计数加 1；唤醒等待者 |

二值信号量常用于互斥：

```text
初始值 = 1
进入临界区前 P
离开临界区后 V
```

## 3. 临界区

临界区是访问共享资源的代码片段。

```c
P(sem);

// 临界区：访问共享资源
shared_counter++;

V(sem);
```

原则：

- 临界区尽量短。
- 所有访问共享资源的路径都要遵守同一把锁。
- 出错退出时也要释放资源。

## 4. System V 信号量流程

典型步骤：

1. `ftok` 生成 key。
2. `semget` 创建或获取信号量集合。
3. `semctl` 初始化信号量值。
4. `semop` 执行 P/V 操作。
5. `semctl(..., IPC_RMID)` 删除信号量集合。

## 5. System V P/V 封装示例

```c
#include <sys/sem.h>

void sem_p(int semid) {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

void sem_v(int semid) {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}
```

初始化信号量：

```c
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

union semun arg;
arg.val = 1;
semctl(semid, 0, SETVAL, arg);
```

## 6. POSIX 信号量

POSIX 信号量接口更直观，常见于线程或进程间同步。

### 6.1 无名信号量

适合线程之间使用：

```c
#include <semaphore.h>

sem_t sem;
sem_init(&sem, 0, 1);

sem_wait(&sem);
// 临界区
sem_post(&sem);

sem_destroy(&sem);
```

### 6.2 有名信号量

适合无亲缘关系进程使用：

```c
#include <fcntl.h>
#include <semaphore.h>

sem_t *sem = sem_open("/demo_sem", O_CREAT, 0666, 1);

sem_wait(sem);
// 临界区
sem_post(sem);

sem_close(sem);
sem_unlink("/demo_sem");
```

## 7. 信号量与互斥锁的区别

| 对比项 | 信号量 | 互斥锁 |
|---|---|---|
| 值 | 可以是 0、1 或更大 | 通常只有锁定/未锁定 |
| 用途 | 资源计数、同步、互斥 | 主要用于互斥 |
| 所有权 | 不强调同一执行流释放 | 通常要求加锁者解锁 |
| 典型场景 | 生产者消费者、资源池 | 保护临界区 |

## 8. 生产者消费者模型

信号量非常适合描述“空位数量”和“产品数量”。

```text
empty：缓冲区空位数量
full：缓冲区已有数据数量
mutex：保护缓冲区互斥访问
```

生产者：

```text
P(empty)
P(mutex)
写入数据
V(mutex)
V(full)
```

消费者：

```text
P(full)
P(mutex)
读取数据
V(mutex)
V(empty)
```

## 9. 易错点

- 忘记释放信号量会导致其他执行流永久阻塞。
- P/V 顺序写错可能造成死锁。
- 初始化值必须符合资源数量。
- 多个资源同时加锁时，要保持固定顺序。
- System V 信号量对象可能残留，需要用命令检查和清理。

查看 System V IPC 对象：

```bash
ipcs -s
```

删除信号量集合：

```bash
ipcrm -s <semid>
```

## 10. 自学任务

1. 用 POSIX 无名信号量保护一个全局计数器。
2. 用 System V 信号量保护共享内存读写。
3. 故意去掉 `sem_post`，观察程序如何阻塞。
4. 画出生产者消费者模型的 P/V 顺序。
5. 用 `ipcs -s` 查看并清理残留信号量。

## 11. 本章检查清单

- [ ] 能解释 P/V 操作。
- [ ] 能说明临界区和共享资源的关系。
- [ ] 能写出 POSIX 信号量基本用法。
- [ ] 能理解 System V 信号量的创建和删除流程。
- [ ] 能用信号量描述生产者消费者模型。
