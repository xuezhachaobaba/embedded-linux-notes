# 作业 10：Linux 命令行与 shell 基础

> 本课作业**全是实操**：每题在终端里跑，把"你实际敲的命令"贴进答案。不用预测——目标是手感。
> 只把"卡住的 / 想确认的"发我。配套讲义：`课本/03-Linux/10-命令行与shell基础.md`。

---

## 1. `[考：知识点1]` 地图题（不用跑，默写）

`/etc`、`/home`、`/var`、`/proc`、`/dev`、`/usr` 各放什么？一句话一个。

**答**：
/etc：忘了
/home：普通用户的空间
/var：忘了
/proc:忘了
/dev：设备树
/usr:命令

/etc：配置文件
/home：普通用户的家
/var：经常变的数据
/proc：内核信息假文件系统
/dev：设备文件
/usr：系统软件资源
全错啊

## 2. `[考：知识点1]` 路径实操

从 `~/project/02_teach` 出发，**一条命令**分别做到：

a) 跳到 `code/` 目录
b) 跳回 `02_teach`
c) 在 `code` 和 `02_teach` 之间来回跳（用哪个符号？）
d) 直接回家

**答**（贴命令）：
a cd code/
b cd ..
c cd -
d cd

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
mkdir ~/drill/a/sub ~/drill/b
cd ~/drill/a/sub && touch x1.txt x2.txt x3.txt
cp x1.txt ../../b/
mv x2.txt x2.bak
ls -R ~/drill
ls -l ~/drill
rm -rf ~/drill

## 4. `[考：知识点3]` 看文件

a) `ls -l /usr/bin | head -5` 贴输出
b) 数数 /usr/bin 下有多少条目（ls + 管道）
c) `tail -n 3 /etc/passwd` 贴输出，最后一行那个是你的账号（每行一个用户）

**答**：
a:
total 441764
lrwxrwxrwx   1 root root            4 Dec  6  2025 NF -> col1
lrwxrwxrwx   1 root root            1 Feb 28  2026 X11 -> .
lrwxrwxrwx   1 root root           28 Mar 31 00:50 [ -> ../lib/cargo/bin/coreutils/[
-rwxr-xr-x   1 root root        14720 Apr  9 01:26 aa-enabled
b:
ls -l /usr/bin | wc -l
1047
c:
tail -n 3 /etc/passwd
nixbld8:x:985:984:Nix build user 8:/var/empty:/usr/sbin/nologin
nixbld9:x:984:984:Nix build user 9:/var/empty:/usr/sbin/nologin
nixbld10:x:983:984:Nix build user 10:/var/empty:/usr/sbin/nologin

## 5. `[考：知识点4]` find

a) 全盘找一个叫 `stdio.h` 的文件（提示：/usr/include 下，加 `2>/dev/null` 屏蔽报错）
b) 在 `~/project/02_teach` 下找所有 `.c` 文件，贴命令和数量
c) 找出你 home 下大于 10MB 的文件（find -size）

**答**：
a) find / -name "stdio.h" 2>/dev/null
b) find ~/project/02_teach/ -name "*.c" | wc -l
    37
c) find ~/home/ -size +10M

## 6. `[考：知识点4]` grep

在 `~/project/02_teach` 下：

a) 递归搜 `volatile`，显示行号，贴命令 + 命中几个文件
b) 递归搜"知识点清单"，统计总共出现几处（连招：grep | wc -l）
c) 在 `~/.bashrc` 里搜跟历史命令条数有关的配置（关键词 HISTSIZE）

**答**：
a)
rep -rn "volatile" . 
./README.md:40:- [x] 03 `volatile` / `static` / `const` ✅（12/12 全对）
./笔记/要点.md:46:## volatile / static / const 速记（03）
./笔记/要点.md:48:- volatile = "每次都老实去内存读写"：**禁止缓存/合并/删除访问**。三个场景：①中断共享变量 ②硬件寄存器 ③多线程共享（仅保可见性）
./笔记/要点.md:49:- ⚠️ volatile **三个不保证**：不原子、不同步、不防打断——多线程正确性靠锁，volatile 只保证"读的是内存"
./笔记/要点.md:50:- 访问硬件寄存器标准姿势：`volatile uint32_t *reg = (volatile uint32_t*)0x40021000;`
./笔记/要点.md:51:- `const volatile int *p` = 代码不许改（const）、硬件随时改（volatile）→ 只读状态寄存器
./笔记/要点.md:53:- 面试一句话：volatile 管优化，static 管生命周期+作用域，const 管只读
./作业/10-命令行与shell基础.md:60:a) 递归搜 `volatile`，显示行号，贴命令 + 命中几个文件
./作业/10-命令行与shell基础.md:82:e) cat 课本/01-C内功/03-volatile-static-const.md | wc -l
./作业/03-volatile-static-const.md:1:# 作业 03：volatile / static / const
./作业/03-volatile-static-const.md:3:> 本节 **volatile 的效果要在 `-O2` 下才明显，且很多题是概念题（没法直接跑）**——这正常，理解 WHY 比跑代码重要。static / const 的题可以跑。
./作业/03-volatile-static-const.md:4:> 做完只把"卡住的 / 想确认的"发我。配套讲义：`课本/01-C内功/03-volatile-static-const.md`。
./作业/03-volatile-static-const.md:17:**答**：这里中断把flag设成1之后，主代码也不会读到，while也不会停，成了死循环。怎么修：定义的时候，前面加上volatile int flag = 0;这样中断里flag被设成1的话，会从内存里读取到，停止循环；
./作业/03-volatile-static-const.md:22:"`volatile` 让变量的读写在单条指令内完成，不会被中断打断（即原子操作）。"
./作业/03-volatile-static-const.md:26:**答**：错，因为在c里，volatile只保证变量从内存中读写，并不保证其他，可能会被中断打断，不保证原子操作。
./作业/03-volatile-static-const.md:30:"`volatile` 能保证多线程下的正确同步，用了 volatile 就不用加锁。"
./作业/03-volatile-static-const.md:34:**答**：错，因为在c里，volatile只保证变量从内存中读写，并不保证其他，多线程下的正确同步需要靠互斥锁和同步锁来解决。
./作业/03-volatile-static-const.md:40:volatile uint32_t *reg = (volatile uint32_t*)0x40021000;
./作业/03-volatile-static-const.md:42:**不加 volatile 会怎样？**
./作业/03-volatile-static-const.md:45:重新回答：这是volatile的一个应用场景，读写硬件寄存器有副作用，访问不能被合并/删掉
./作业/03-volatile-static-const.md:49:`const volatile int *status` 表示什么？**什么场景会用**？
./作业/03-volatile-static-const.md:111:各用一句话说清 `volatile` / `static` / `const` 的作用（像面试那样口头表达）。
./作业/03-volatile-static-const.md:113:- volatile：修饰的变量会从内存里读取数据，而不是寄存器之类的
./作业/03-volatile-static-const.md:128:这么修改：volatile uint32_t *p = (volatile uint32_t*)0x40000000;
./课本/01-C内功/02b-指针与数组.md:149:下一节进 **03：`volatile` / `static` / `const` 三个关键字**（嵌入式面试常驻考点，尤其 `volatile`）。
./课本/03-Linux/10-命令行与shell基础.md:197:grep -rn "volatile" 课本/ | wc -l        # volatile 出现几次
./课本/01-C内功/03-volatile-static-const.md:1:# 03 三个关键字：`volatile` / `static` / `const`
./课本/01-C内功/03-volatile-static-const.md:3:> 这三个是 C 面试的常驻考点，嵌入式尤其爱考 `volatile`（它是嵌入式区别于纯软件的标志）。本节务必把"为什么"想透。
./课本/01-C内功/03-volatile-static-const.md:7:- 理解 `volatile` 的作用、三大场景，以及它**不**保证什么
./课本/01-C内功/03-volatile-static-const.md:13:1. `volatile` 是什么：阻止编译器优化，强制每次读写内存
./课本/01-C内功/03-volatile-static-const.md:14:2. `volatile` 的三大使用场景：硬件寄存器 / 中断共享变量 / 多线程
./课本/01-C内功/03-volatile-static-const.md:15:3. `volatile` 的经典坑（`while(flag)` 被优化成死循环）
./课本/01-C内功/03-volatile-static-const.md:16:4. **`volatile` 不保证原子性、不保证线程安全**（面试最爱挖的坑）
./课本/01-C内功/03-volatile-static-const.md:17:5. `const volatile` 组合：只读但会变（硬件状态寄存器）
./课本/01-C内功/03-volatile-static-const.md:24:## 1. volatile 是什么　`[知识点1]`
./课本/01-C内功/03-volatile-static-const.md:26:`volatile` 告诉编译器：**这个变量的值随时可能被"当前代码流之外"的力量改变，别自作主张优化它，每次都老老实实从内存读写，别缓存到寄存器。**
./课本/01-C内功/03-volatile-static-const.md:29:volatile int flag;
./课本/01-C内功/03-volatile-static-const.md:32:## 2. volatile 的三大使用场景　`[知识点2]`
./课本/01-C内功/03-volatile-static-const.md:36:volatile uint32_t *gpio = (volatile uint32_t*)0x40021000;
./课本/01-C内功/03-volatile-static-const.md:41:volatile int data_ready = 0;   // 中断里会置 1
./课本/01-C内功/03-volatile-static-const.md:44:**③ 多线程共享变量**——（注意：见知识点 4，volatile 在这里不够用）
./课本/01-C内功/03-volatile-static-const.md:46:## 3. volatile 的经典坑　`[知识点3]` ⭐面试高频
./课本/01-C内功/03-volatile-static-const.md:54:修法：`volatile int flag = 0;`，编译器每次都重新从内存读 `flag`。
./课本/01-C内功/03-volatile-static-const.md:56:> 想亲眼验证可以 `gcc -O2 -S` 看汇编：没 volatile 的版本 `flag` 只被读一次；volatile 的版本每次循环都重新 load。
./课本/01-C内功/03-volatile-static-const.md:58:## 4. volatile 不保证原子性、不保证线程安全　`[知识点4]` ⭐面试最爱挖的坑
./课本/01-C内功/03-volatile-static-const.md:62:- ❌ "volatile 让读写变成原子操作" → **错**。`volatile` 只防优化，**不保证一次读/写不被打断**。`volatile int64_t` 在 32 位机上读写仍可能被打断。
./课本/01-C内功/03-volatile-static-const.md:63:- ❌ "volatile 能保证多线程安全" → **错**。它不保证**内存顺序**、不保证原子。多线程正确同步要靠**互斥锁 / 原子变量**。
./课本/01-C内功/03-volatile-static-const.md:65:> 记住：**C 的 volatile ≠ Java 的 volatile**。C 的 volatile 只管"别优化、老实访问内存"，仅此而已。
./课本/01-C内功/03-volatile-static-const.md:67:## 5. const volatile 组合　`[知识点5]`
./课本/01-C内功/03-volatile-static-const.md:69:看起来矛盾，实则很常见：**"代码里不能改它（const），但它会被硬件改（volatile）"**——典型的**只读状态寄存器**。
./课本/01-C内功/03-volatile-static-const.md:72:const volatile uint32_t *status = (const volatile uint32_t*)0x40021010;
./课本/01-C内功/03-volatile-static-const.md:116:见 `作业/03-volatile-static-const.md`。**volatile 的效果要在 `-O2` 下才明显，且很多题是概念题（没法直接跑）——理解 WHY 比跑代码重要**；static / const 的题可以跑。
grep: ./.git/index: binary file matches
b)
grep -r "知识点清单" . | wc -l
8
c)
grep HISTSIZE ~/.bashrc
# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000


## 7. `[考：知识点5]` 权限

a) `ls -l` 看 `code/02b/01.c`，把权限段（如 `-rw-rw-r--`）抄下来，解释 9 位分三组各是谁
b) 把它复制一份到 /tmp，改成 `600`，再 `ls -l` 验证
c) `ls -l /` 看 `/etc/passwd` 的权限——为什么普通用户改不了它？
d) 写一个 t.sh 输出 hi，直接跑、chmod +x 后再跑，贴两次结果

**答**：
a)ls -l code/02b/01.c
-rw-rw-r-- 1 zhuchao zhuchao 114 Jul 17 15:51 code/02b/01.c
-表示是普通文件，rw-属于所有者，6 rw-属于所属组，6，r--属于other，4
b)
cp code/02b/01.c /tmp/ && chmod /tmp/01.c 600 && ls -l /tmp/01.c
chmod: cannot access '600': No such file or directory
c)
ls -l /etc/passwd
-rw-r--r-- 1 root root 2079 Jul 16 18:27 /etc/passwd
不知道
d)
echo "echo hi" > t.sh
./t.sh
bash: ./t.sh: Permission denied
chmod +x t.sh
./t.sh
hi

## 8. `[考：知识点6]` 管道与重定向连招（写出每条的输出或文件内容）

```bash
a) echo "hello" > f1.txt; cat f1.txt
b) echo "world" >> f1.txt; cat f1.txt        # 注意和 a 的区别
c) ls /notexist > f2.txt                      # 屏幕上有什么？f2.txt 里有什么？为什么？
d) ls /notexist 2> f3.txt; cat f3.txt
e) cat 课本/01-C内功/03-volatile-static-const.md | wc -l
f) history | grep "chmod" | wc -l
```

**答**（重点解释 c）：
hello
hello
world
ls /notexist > f2.txt
ls: cannot access '/notexist': No such file or directory
ls /notexist 2> f3.txt; cat f3.txt
ls: cannot access '/notexist': No such file or directory
120
7
中间两个命令应该是我输入有问题，我电脑环境哪里不对，这两条命令我没看懂

## 9. `[考：知识点6]` 实战编译记录

用 tee 记录一次编译：

```bash
cd ~/project/02_teach/code/02b
gcc -Wall 01.c -o /tmp/t01 2>&1 | tee /tmp/build.log
cat /tmp/build.log
```

如果编译有警告，log 里应该也有。解释这条命令里 `2>&1` 和 `| tee` 各干了什么：

**答**：
2>&1,我的理解是把gcc那句命令的两个输出，正常输出和不正常输出都输入到一起了，tee读取这个输出，这里我没懂，课本里我也没看懂
cat没有输出

## 10. `[考：知识点7]` 进程

a) `ps aux | head -3` 贴输出，说出表头 USER/PID/STAT/COMMAND 各是什么
b) 找出你所有 bash 进程（ps aux | grep bash | grep -v grep，解释 grep -v grep 干嘛的）
c) 后台跑 `sleep 500 &`，用 jobs 看，再用 kill 杀掉，贴过程
d) `top` 打开按 q 退出；顺手记一下：你们 WSL 里现在 CPU 占用最高的是什么命令？

**答**：
user是所有人， pid是进程的id ，stat不知道，command是命令嘛？不知道
ps aux | grep bash | grep -v grep
zhuchao      817  0.0  0.0  16192 12832 pts/1    Ss+  9月18   0:00 -bash
root         952  0.0  0.0   9340  5508 pts/4    Ss+  9月18   0:00 -bash
zhuchao    47704  0.0  0.0   8280  4156 ?        Ss   20:00   0:00 -bash
zhuchao    48366  0.0  0.0  16520 13488 pts/7    Ss   20:00   0:00 /bin/bash --init-file /home/zhuchao/.vscode-server/cli/servers/Stable-a44adf7f53e00964ab890f9f8758a334f1fc15bc/server/out/vs/workbench/contrib/terminal/common/scripts/shellIntegration-bash.sh
zhuchao    48602  0.0  0.0  16336 13092 pts/0    Ss   20:01   0:00 -bash
zhuchao    49078  0.0  0.0  16336 13148 pts/2    Ss+  20:04   0:00 -bash
不懂
sleep 500 &
[1] 63013
jobs
[1]+  Running                    sleep 500 &
kill %1
[1]+  Terminated                 sleep 500
wsl里目前占用最多的是claude

## 11. `[考：知识点8]` 环境变量

a) `echo $PATH` 贴出来，解释敲 gcc 时 shell 怎么找到它的
b) `export DRILL=done && echo $DRILL`，然后**新开一个终端**再 `echo $DRILL`——结果？为什么？怎么让它永久有效？
c) `Ctrl+R` 搜你历史里的 `git commit`，贴你搜到的那条
d) `sudo !!` 什么场景用？

**答**：
/home/zhuchao/.vscode-server/cli/servers/Stable-a44adf7f53e00964ab890f9f8758a334f1fc15bc/server/bin/remote-cli:/home/zhuchao/.local/bin:/home/zhuchao/.nvm/versions/node/v22.23.2/bin:/home/zhuchao/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
gcc时候，shell先从当前目录下查看是否有gcc命令，没有的话，就从path的地址下面找
b）不懂
git commit': git commit -m "day-2"
上一条命令没有给sudo的时候用


## 12. `[考：综合]` 大连招（一条管道链）

统计 `~/project/02_teach/课本/` 下所有 md 文件里 `知识点` 一共出现多少次：

**答**（贴命令和数字）：
cat ~/project/02_teach/课本/*/*.md | grep "知识点" | wc -l
90
---

> 做完自检：3/5/6/8 顺手 + 能解释 c 题的重定向 = 本课 pass。
> 本课不用写总结（操作类），但命令手感要留下——以后每节课都会用。
> C 内功阶段到此全部结束！下一站：**阶段 0.5 C++**（C01 从 C 到 C++）。总结欠账（02b~05）有空挑两篇补上 😄
