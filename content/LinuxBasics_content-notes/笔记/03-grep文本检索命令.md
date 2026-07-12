# grep 文本检索命令

> 本章目标：学会在日志、源码和配置文件中快速定位文本。

## 1. grep 的核心思想

`grep` 用来从文本中筛选匹配指定模式的行。它常用于：

- 在源码中查找函数或宏定义。
- 在日志中查找错误信息。
- 在配置文件中确认某个参数是否存在。
- 与管道组合，过滤其他命令的输出。

基本格式：

```bash
grep [选项] "模式" 文件
```

## 2. 基础用法

在文件中查找 `error`：

```bash
grep "error" app.log
```

显示行号：

```bash
grep -n "error" app.log
```

忽略大小写：

```bash
grep -i "error" app.log
```

递归查找目录：

```bash
grep -R "pthread_create" .
```

只显示匹配到的文件名：

```bash
grep -Rl "main" .
```

## 3. 常用选项速查

| 选项 | 作用 | 示例 |
|---|---|---|
| `-n` | 显示行号 | `grep -n "TODO" *.c` |
| `-i` | 忽略大小写 | `grep -i "error" app.log` |
| `-R` | 递归搜索目录 | `grep -R "init" src/` |
| `-v` | 反向匹配 | `grep -v "debug" app.log` |
| `-l` | 只显示文件名 | `grep -Rl "main" .` |
| `-c` | 统计匹配行数 | `grep -c "ERROR" app.log` |
| `-w` | 匹配完整单词 | `grep -w "int" main.c` |

## 4. 和管道配合

查找当前进程中包含 `ssh` 的行：

```bash
ps aux | grep "ssh"
```

查看网络配置中包含 `inet` 的行：

```bash
ip addr | grep "inet"
```

筛选日志中的错误行并统计数量：

```bash
grep "ERROR" app.log | wc -l
```

## 5. grep 与正则表达式

`grep` 默认支持基础正则。使用 `-E` 可以启用扩展正则，写法更舒服。

匹配 `error` 或 `failed`：

```bash
grep -E "error|failed" app.log
```

匹配以 `#include` 开头的行：

```bash
grep -n "^#include" *.c
```

匹配空行：

```bash
grep -n "^$" file.txt
```

## 6. 在源码中的典型用法

查找函数调用：

```bash
grep -R -n "pthread_mutex_lock" src/
```

查找宏定义：

```bash
grep -R -n "#define BUFFER_SIZE" .
```

排除构建目录：

```bash
grep -R -n "open(" src/ --exclude-dir=build
```

## 7. 常见错误

| 问题 | 原因 | 建议 |
|---|---|---|
| 匹配太多 | 模式过宽 | 加 `-w` 或更精确的关键字 |
| 找不到中文 | 文件编码不统一 | 先确认文件编码 |
| 把 grep 自己也搜出来 | `ps | grep` 常见现象 | 可再加过滤条件 |
| 递归搜索太慢 | 目录太大 | 限定目录或排除构建目录 |

## 8. 自学任务

1. 在一个源码目录中查找 `main` 函数。
2. 在日志中找出包含 `error` 的行，并显示行号。
3. 统计一个文件中空行数量。
4. 查找所有包含 `pthread` 的源文件名。
5. 使用 `grep -E` 同时匹配两个关键字。

## 9. 本章检查清单

- [ ] 能使用 `grep -n` 定位行号。
- [ ] 能使用 `grep -R` 递归查找源码。
- [ ] 能用 `grep -v` 排除不需要的行。
- [ ] 能把 grep 与管道组合使用。
- [ ] 能写出简单正则匹配行首、行尾和多个关键字。
