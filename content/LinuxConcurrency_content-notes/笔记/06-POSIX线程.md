# POSIX 线程

> 本章目标：理解线程是进程内的并发执行路径，并掌握创建、等待、互斥和条件变量的基本方法。

## 1. 为什么需要线程

进程可以实现并发，但进程之间地址空间隔离，创建和通信成本都比较高。

线程是在同一个进程内部运行的执行路径。多个线程共享进程地址空间，因此通信更方便，但也更容易产生数据竞争。

| 对比项 | 进程 | 线程 |
|---|---|---|
| 地址空间 | 相互独立 | 同一进程内共享 |
| 创建开销 | 较大 | 较小 |
| 通信方式 | 需要 IPC | 可直接共享变量 |
| 崩溃影响 | 通常影响单个进程 | 可能影响整个进程 |
| 调度单位 | 现代系统中线程是调度单位 | 线程是调度单位 |

## 2. 创建线程

线程函数原型：

```c
void *thread_func(void *arg);
```

示例：

```c
#include <pthread.h>
#include <stdio.h>

void *worker(void *arg) {
    const char *name = arg;
    printf("hello %s\n", name);
    return NULL;
}

int main(void) {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, "thread");
    pthread_join(tid, NULL);
    return 0;
}
```

编译时需要链接 pthread：

```bash
gcc main.c -o main -pthread
```

## 3. 等待线程结束

`pthread_join` 用于等待线程结束并回收资源。

```c
void *worker(void *arg) {
    return (void *)123;
}

int main(void) {
    pthread_t tid;
    void *ret = NULL;

    pthread_create(&tid, NULL, worker, NULL);
    pthread_join(tid, &ret);

    printf("ret = %ld\n", (long)ret);
    return 0;
}
```

如果线程不需要被 join，可以设置为 detached，但初学阶段建议先掌握 join。

## 4. 数据竞争

多个线程共享全局变量时，下面的代码是不安全的：

```c
int counter = 0;

void *worker(void *arg) {
    for (int i = 0; i < 100000; ++i) {
        counter++;
    }
    return NULL;
}
```

`counter++` 并不是一个不可分割操作，它至少包含读、加、写三个步骤。多个线程同时执行会导致结果丢失。

## 5. 互斥锁 mutex

使用互斥锁保护临界区：

```c
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
```

原则：

- 加锁范围尽量小。
- 每一次 lock 都必须对应 unlock。
- 不要在持锁时执行耗时 I/O。

## 6. 条件变量

条件变量用于“等待某个条件成立”。它通常和互斥锁一起使用。

典型场景：队列为空时，消费者等待；生产者放入数据后通知消费者。

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;

void *consumer(void *arg) {
    pthread_mutex_lock(&mutex);
    while (!ready) {
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *producer(void *arg) {
    pthread_mutex_lock(&mutex);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
```

注意：等待条件时要用 `while`，不要用 `if`。因为线程被唤醒后仍需要重新检查条件。

## 7. 可重入与线程安全

- **可重入函数**：在执行过程中再次被调用也不会破坏状态。
- **线程安全函数**：多个线程同时调用不会产生数据竞争。

常见风险：

- 使用静态局部变量保存状态。
- 返回内部静态缓冲区地址。
- 多线程同时访问全局变量。
- 在信号处理和线程中混用不安全函数。

## 8. 线程设计建议

- 共享数据越少，程序越容易正确。
- 能传参就不要滥用全局变量。
- 先写单线程版本，再引入线程。
- 给每个线程明确职责：采集、处理、写入、通信等。
- 使用队列连接线程，比到处共享变量更清晰。

## 9. 易错点

- 忘记 `-pthread` 导致链接失败。
- 主线程提前退出，其他线程来不及执行。
- 多线程同时写全局变量，结果不稳定。
- 条件变量等待条件时使用 `if` 而不是 `while`。
- 死锁：线程 A 等 B 的锁，线程 B 又等 A 的锁。

## 10. 自学任务

1. 创建一个线程并打印参数。
2. 创建两个线程共同累加计数器，观察不加锁的错误结果。
3. 给计数器加互斥锁，再观察结果。
4. 用条件变量实现一个简单“通知后继续”的程序。
5. 思考一个嵌入式应用中哪些任务适合拆成线程。

## 11. 本章检查清单

- [ ] 能写出 `pthread_create` 和 `pthread_join`。
- [ ] 能解释线程和进程的区别。
- [ ] 能说明为什么共享变量需要互斥锁。
- [ ] 能使用条件变量等待条件成立。
- [ ] 能识别常见死锁和数据竞争风险。
