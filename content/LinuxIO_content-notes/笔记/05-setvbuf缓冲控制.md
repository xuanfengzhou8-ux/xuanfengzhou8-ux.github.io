# setvbuf 缓冲控制

> 本章目标：理解标准 I/O 缓冲区可以被显式配置，并知道什么时候需要调整缓冲方式。

## 1. setvbuf 的作用

`setvbuf` 用于设置一个标准 I/O 流的缓冲方式和缓冲区。

```c
#include <stdio.h>

int setvbuf(FILE *stream, char *buf, int mode, size_t size);
```

参数含义：

| 参数 | 说明 |
|---|---|
| `stream` | 要设置的流，例如 `stdin`、`stdout` 或文件流 |
| `buf` | 用户提供的缓冲区，传 `NULL` 表示由库分配 |
| `mode` | 缓冲模式 |
| `size` | 缓冲区大小 |

## 2. 三种缓冲模式

| 模式 | 含义 |
|---|---|
| `_IOFBF` | 全缓冲 |
| `_IOLBF` | 行缓冲 |
| `_IONBF` | 无缓冲 |

示例：把 `stdout` 设置为无缓冲。

```c
#include <stdio.h>

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("hello");
    return 0;
}
```

## 3. 设置自定义缓冲区

```c
#include <stdio.h>

int main(void) {
    char buffer[4096];
    FILE *fp = fopen("out.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    setvbuf(fp, buffer, _IOFBF, sizeof(buffer));
    fputs("hello\n", fp);
    fclose(fp);
    return 0;
}
```

注意：缓冲区生命周期必须覆盖流的使用过程，不能用已经失效的局部缓冲区继续给流使用。

## 4. 什么时候需要 setvbuf

常见场景：

- 调试输出希望立即显示：设置无缓冲。
- 文件批量写入希望减少系统调用：设置较大的全缓冲。
- 交互式命令行程序希望按行刷新：设置行缓冲。
- 实验标准 I/O 缓冲行为：显式设置模式便于观察。

## 5. 和 fflush 的关系

`setvbuf` 设置缓冲策略，`fflush` 触发刷新。

```c
setvbuf(stdout, NULL, _IOLBF, 0);
printf("progress...");
fflush(stdout);
```

实际开发中，经常只需要 `fflush`，不一定要修改缓冲模式。

## 6. 输入流的缓冲

输入流也有缓冲。例如 `stdin` 可能先把用户输入读入缓冲区，再由 `fgetc`、`scanf` 等函数逐步取出。

示例：设置 `stdin` 无缓冲。

```c
setvbuf(stdin, NULL, _IONBF, 0);
```

不过实际项目中很少随意修改 `stdin` 的缓冲方式。更常见的是设计清晰的输入协议，避免混用 `scanf`、`fgets` 等接口造成残留换行问题。

## 7. 易错点

- `setvbuf` 应尽量在流打开后、读写前调用。
- 自定义缓冲区不能过早失效。
- 无缓冲不等于性能更好，它可能增加系统调用次数。
- 缓冲问题不等于程序没执行，先用 `fflush` 或换行验证。

## 8. 自学任务

1. 写程序比较 `printf("hello")` 在默认缓冲和无缓冲下的表现。
2. 给文件流设置 4KB 全缓冲并写入大量数据。
3. 在循环打印进度时使用 `fflush(stdout)`。
4. 尝试混用 `scanf` 和 `fgets`，观察输入残留问题。

## 9. 本章检查清单

- [ ] 能说出 `setvbuf` 的四个参数含义。
- [ ] 能区分全缓冲、行缓冲、无缓冲。
- [ ] 知道 `setvbuf` 与 `fflush` 的区别。
- [ ] 知道自定义缓冲区生命周期的要求。
