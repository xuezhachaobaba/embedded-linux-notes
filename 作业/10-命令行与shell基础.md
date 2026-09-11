# 作业 10：Linux 命令行与 shell 基础

> 本课作业**全是实操**：每题在终端里跑，把"你实际敲的命令"贴进答案。不用预测——目标是手感。
> 只把"卡住的 / 想确认的"发我。配套讲义：`课本/10-命令行与shell基础.md`。

---

## 1. `[考：知识点1]` 地图题（不用跑，默写）

`/etc`、`/home`、`/var`、`/proc`、`/dev`、`/usr` 各放什么？一句话一个。

**答**：

## 2. `[考：知识点1]` 路径实操

从 `~/project/02_teach` 出发，**一条命令**分别做到：

a) 跳到 `code/` 目录
b) 跳回 `02_teach`
c) 在 `code` 和 `02_teach` 之间来回跳（用哪个符号？）
d) 直接回家

**答**（贴命令）：

## 3. `[考：知识点2]` 六件套实操

不离开终端完成（贴全过程命令）：

```text
在 ~ 下建 ~/drill/a/sub 和 ~/drill/b（一条命令）
在 a/sub 里建 3 个文件 x1.txt x2.txt x3.txt（可以一条 touch）
把 x1.txt 复制到 b/
把 x2.txt 改名 x2.bak
只看 ~/drill 的树形结构（提示：ls -R）
把整个 drill 删掉（删之前先干什么？）
```

**答**：

## 4. `[考：知识点3]` 看文件

a) `ls -l /usr/bin | head -5` 贴输出
b) 数数 /usr/bin 下有多少条目（ls + 管道）
c) `tail -n 3 /etc/passwd` 贴输出，最后一行那个是你的账号（每行一个用户）

**答**：

## 5. `[考：知识点4]` find

a) 全盘找一个叫 `stdio.h` 的文件（提示：/usr/include 下，加 `2>/dev/null` 屏蔽报错）
b) 在 `~/project/02_teach` 下找所有 `.c` 文件，贴命令和数量
c) 找出你 home 下大于 10MB 的文件（find -size）

**答**：

## 6. `[考：知识点4]` grep

在 `~/project/02_teach` 下：

a) 递归搜 `volatile`，显示行号，贴命令 + 命中几个文件
b) 递归搜"知识点清单"，统计总共出现几处（连招：grep | wc -l）
c) 在 `~/.bashrc` 里搜跟历史命令条数有关的配置（关键词 HISTSIZE）

**答**：

## 7. `[考：知识点5]` 权限

a) `ls -l` 看 `code/02b/01.c`，把权限段（如 `-rw-rw-r--`）抄下来，解释 9 位分三组各是谁
b) 把它复制一份到 /tmp，改成 `600`，再 `ls -l` 验证
c) `ls -l /` 看 `/etc/passwd` 的权限——为什么普通用户改不了它？
d) 写一个 t.sh 输出 hi，直接跑、chmod +x 后再跑，贴两次结果

**答**：

## 8. `[考：知识点6]` 管道与重定向连招（写出每条的输出或文件内容）

```bash
a) echo "hello" > f1.txt; cat f1.txt
b) echo "world" >> f1.txt; cat f1.txt        # 注意和 a 的区别
c) ls /notexist > f2.txt                      # 屏幕上有什么？f2.txt 里有什么？为什么？
d) ls /notexist 2> f3.txt; cat f3.txt
e) cat 课本/03-volatile-static-const.md | wc -l
f) history | grep "chmod" | wc -l
```

**答**（重点解释 c）：

## 9. `[考：知识点6]` 实战编译记录

用 tee 记录一次编译：

```bash
cd ~/project/02_teach/code/02b
gcc -Wall 01.c -o /tmp/t01 2>&1 | tee /tmp/build.log
cat /tmp/build.log
```

如果编译有警告，log 里应该也有。解释这条命令里 `2>&1` 和 `| tee` 各干了什么：

**答**：

## 10. `[考：知识点7]` 进程

a) `ps aux | head -3` 贴输出，说出表头 USER/PID/STAT/COMMAND 各是什么
b) 找出你所有 bash 进程（ps aux | grep bash | grep -v grep，解释 grep -v grep 干嘛的）
c) 后台跑 `sleep 500 &`，用 jobs 看，再用 kill 杀掉，贴过程
d) `top` 打开按 q 退出；顺手记一下：你们 WSL 里现在 CPU 占用最高的是什么命令？

**答**：

## 11. `[考：知识点8]` 环境变量

a) `echo $PATH` 贴出来，解释敲 gcc 时 shell 怎么找到它的
b) `export DRILL=done && echo $DRILL`，然后**新开一个终端**再 `echo $DRILL`——结果？为什么？怎么让它永久有效？
c) `Ctrl+R` 搜你历史里的 `git commit`，贴你搜到的那条
d) `sudo !!` 什么场景用？

**答**：

## 12. `[考：综合]` 大连招（一条管道链）

统计 `~/project/02_teach/课本/` 下所有 md 文件里 `知识点` 一共出现多少次：

**答**（贴命令和数字）：

---

> 做完自检：3/5/6/8 顺手 + 能解释 c 题的重定向 = 本课 pass。
> 本课不用写总结（操作类），但命令手感要留下——以后每节课都会用。
> C 内功阶段到此全部结束！下一站：**阶段 0.5 C++**（C01 从 C 到 C++）。总结欠账（02b~05）有空挑两篇补上 😄
