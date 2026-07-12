# find 文件查找命令

> 本章目标：学会在复杂目录中快速定位文件，并把查找结果交给后续命令处理。

## 1. find 解决什么问题

当项目变大后，文件可能分散在很多目录里。`find` 的作用是：从指定目录开始，递归查找满足条件的文件或目录。

基本格式：

```bash
find <起始目录> <查找条件> <处理动作>
```

示例：在当前目录下查找所有 `.c` 文件：

```bash
find . -name "*.c"
```

## 2. 最常用的查找条件

| 条件 | 作用 | 示例 |
|---|---|---|
| `-name` | 按名称匹配 | `find . -name "*.c"` |
| `-iname` | 按名称匹配，忽略大小写 | `find . -iname "readme*"` |
| `-type f` | 只找普通文件 | `find . -type f` |
| `-type d` | 只找目录 | `find . -type d` |
| `-size` | 按大小查找 | `find . -size +10M` |
| `-mtime` | 按修改时间查找 | `find . -mtime -1` |
| `-perm` | 按权限查找 | `find . -perm -111` |

## 3. 按名称查找

查找所有 C 源文件：

```bash
find . -name "*.c"
```

查找所有头文件：

```bash
find . -name "*.h"
```

查找名称中包含 `test` 的文件：

```bash
find . -name "*test*"
```

> 注意：`*.c` 要加引号，避免先被 shell 展开。

## 4. 按类型查找

只查找目录：

```bash
find . -type d
```

只查找普通文件：

```bash
find . -type f
```

查找可执行文件：

```bash
find . -type f -perm -111
```

## 5. 按时间和大小查找

查找最近 1 天修改过的文件：

```bash
find . -type f -mtime -1
```

查找 7 天前修改过的文件：

```bash
find . -type f -mtime +7
```

查找大于 10 MB 的文件：

```bash
find . -type f -size +10M
```

查找小于 4 KB 的文件：

```bash
find . -type f -size -4k
```

## 6. 对查找结果执行操作

`find` 可以配合 `-exec` 对每个结果执行命令。

查看所有 `.log` 文件的详细信息：

```bash
find . -name "*.log" -exec ls -lh {} \;
```

删除临时文件：

```bash
find . -name "*.tmp" -delete
```

统计所有 C 文件行数：

```bash
find . -name "*.c" -exec wc -l {} \;
```

其中 `{}` 表示当前找到的文件，`\;` 表示这条 `-exec` 命令结束。

## 7. 和 grep 配合使用

查找所有 C 文件中包含 `pthread_create` 的位置：

```bash
find . -name "*.c" -exec grep -n "pthread_create" {} \;
```

如果系统支持，也可以用：

```bash
grep -R --include="*.c" -n "pthread_create" .
```

## 8. 常见错误

| 问题 | 原因 | 解决方式 |
|---|---|---|
| 找不到预期文件 | 起始目录不对 | 先用 `pwd` 确认当前位置 |
| `*.c` 结果异常 | 通配符被 shell 先展开 | 给模式加引号 |
| 删除了不该删的文件 | 直接用了 `-delete` | 删除前先不加 `-delete` 预览结果 |
| 权限不足 | 查找了系统目录 | 用普通目录练习，必要时再考虑权限 |

## 9. 自学任务

1. 在一个项目目录中找出所有 `.c` 和 `.h` 文件。
2. 找出最近 24 小时修改过的文件。
3. 找出大于 1 MB 的文件。
4. 找出所有可执行文件。
5. 先预览再删除所有 `.tmp` 文件。

## 10. 本章检查清单

- [ ] 能写出 `find . -name "*.c"`。
- [ ] 能区分 `-type f` 和 `-type d`。
- [ ] 能按时间、大小、权限查找文件。
- [ ] 知道删除前要先预览结果。
- [ ] 能把 `find` 和 `grep`、`wc` 等命令组合使用。
