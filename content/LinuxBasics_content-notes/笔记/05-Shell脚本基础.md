# Shell 脚本基础

> 本章目标：把多条命令组织成可重复执行的脚本，用脚本完成自动化任务。

## 1. Shell 是什么

Shell 是命令解释器。你在终端里输入的命令，会先交给 Shell 解析，再由系统执行。

常见 Shell：

```bash
/bin/sh
/bin/bash
/bin/dash
```

Shell 脚本就是把多条命令写进一个文件，让 Shell 按顺序执行。

## 2. 第一个脚本

创建 `hello.sh`：

```bash
#!/bin/bash

echo "hello shell"
```

给脚本添加执行权限：

```bash
chmod +x hello.sh
```

运行脚本：

```bash
./hello.sh
```

第一行 `#!/bin/bash` 称为 shebang，用来指定脚本解释器。

## 3. 变量

Shell 变量默认都是字符串。赋值时等号两边不能有空格。

```bash
name="linux"
echo "$name"
echo "${name}"
```

命令替换：

```bash
today=$(date +%F)
echo "today is $today"
```

> 推荐使用 `$(...)`，比反引号更清晰，也更容易嵌套。

## 4. 位置参数

脚本可以接收命令行参数。

```bash
#!/bin/bash

echo "script: $0"
echo "first: $1"
echo "second: $2"
echo "count: $#"
echo "all: $@"
```

运行：

```bash
./args.sh hello linux
```

常见参数变量：

| 变量 | 含义 |
|---|---|
| `$0` | 脚本名 |
| `$1`、`$2` | 第 1、2 个参数 |
| `$#` | 参数个数 |
| `$@` | 所有参数，推荐遍历时使用 |
| `$?` | 上一条命令的退出状态码 |

## 5. 条件判断

基本格式：

```bash
if [ 条件 ]; then
    命令
else
    命令
fi
```

判断文件是否存在：

```bash
if [ -f "config.txt" ]; then
    echo "config exists"
else
    echo "missing config"
fi
```

常见文件判断：

| 条件 | 含义 |
|---|---|
| `-f file` | 是否为普通文件 |
| `-d dir` | 是否为目录 |
| `-e path` | 路径是否存在 |
| `-x file` | 是否可执行 |

字符串判断：

```bash
if [ "$1" = "start" ]; then
    echo "start service"
fi
```

数字判断：

```bash
if [ "$count" -gt 10 ]; then
    echo "too many"
fi
```

## 6. 循环

遍历参数：

```bash
for arg in "$@"; do
    echo "arg = $arg"
done
```

遍历文件：

```bash
for file in *.c; do
    echo "compile $file"
done
```

while 循环：

```bash
count=0
while [ "$count" -lt 5 ]; do
    echo "$count"
    count=$((count + 1))
done
```

## 7. 函数

函数用于复用一段脚本逻辑。

```bash
log() {
    echo "[$(date +%H:%M:%S)] $*"
}

log "build start"
```

函数返回值通常通过退出状态码或标准输出传递。

```bash
is_file() {
    [ -f "$1" ]
}

if is_file "main.c"; then
    echo "found main.c"
fi
```

## 8. 一个实用脚本：批量统计源码行数

```bash
#!/bin/bash

set -e

root=${1:-.}

echo "scan root: $root"
find "$root" -name "*.c" -o -name "*.h" | while read -r file; do
    lines=$(wc -l < "$file")
    echo "$lines $file"
done
```

运行：

```bash
./count-lines.sh src
```

## 9. 写脚本时的好习惯

- 变量引用尽量加双引号：`"$name"`。
- 删除文件前先打印将要删除的目标。
- 用 `set -e` 让脚本在错误时尽早停止。
- 对外部输入做检查，不要默认参数一定正确。
- 复杂脚本先拆成函数，再逐步调试。

## 10. 自学任务

1. 写一个脚本，打印所有命令行参数。
2. 写一个脚本，判断某个文件是否存在。
3. 写一个脚本，统计当前目录下 `.c` 文件数量。
4. 写一个脚本，批量给 `.sh` 文件添加执行权限。
5. 写一个脚本，查找大于 1 MB 的日志文件。

## 11. 本章检查清单

- [ ] 能写出包含 shebang 的脚本。
- [ ] 能使用变量、参数和命令替换。
- [ ] 能写 if 判断和 for/while 循环。
- [ ] 能定义简单函数。
- [ ] 能把 find、grep、wc 等命令组合进脚本。
