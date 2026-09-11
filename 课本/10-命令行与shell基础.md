# 10：Linux 命令行与 shell 基础

> 定位说明：这是**阶段 0 的收官课**，也是转型课——从"写代码"转到"在 Linux 里干活"。嵌入式 Linux 工程师一天到晚泡在终端里：编译、传文件、看日志、调板子，全靠命令行。这节课不求背命令，求**建立"一切皆文件"的世界观 + 手速**。
>
> 前置：无（00 课用过一点终端）。本课全部在 WSL2 里实操，**边读边敲**，别只看。

---

## 知识点清单（共 8 个）

| # | 知识点 | 考频/重要性 |
|---|--------|------|
| 1 | 目录结构与绝对/相对路径、`~` `.` `..` `-` | ⭐⭐⭐ 地基 |
| 2 | 文件操作六件套：ls / cd / cp / mv / mkdir / rm | ⭐⭐⭐ 肌肉记忆 |
| 3 | 查看文件五件套：cat / less / head / tail / wc | ⭐⭐⭐ 日志天天用 |
| 4 | 查找双雄：find（找文件）/ grep（找内容） | ⭐⭐⭐ 驱动调试主力 |
| 5 | 权限三件套：rwx、chmod、sudo | ⭐⭐⭐ 必考 |
| 6 | 管道与重定向：`|` `>` `>>` `<` | ⭐⭐⭐ 哲学核心 |
| 7 | 进程与作业：ps / kill / & / jobs / top | ⭐⭐ 常用 |
| 8 | 环境变量与快捷键：PATH、export、history、Tab | ⭐⭐ 效率 |

---

## 知识点 1：目录结构与路径——Linux 的"地图"

Linux 只有一棵目录树（没有 C盘D盘），根是 `/`。背下这张地图（只背加粗的）：

```
/           根
├── bin, sbin      命令（现在是 /usr 的链接）
├── **etc**        配置文件（口诀：Editable Text Config）
├── **home**       普通用户的家（你在 /home/zhuchao）
├── **root**       root 的家
├── **usr**        系统软件资源（/usr/bin 大量命令、/usr/include 头文件）
├── **var**        经常变的数据（**/var/log** 日志）
├── **tmp**        临时文件
├── **proc**       内核信息假文件系统（ps 的数据源！）
├── **dev**        设备文件——"一切皆文件"的现场（后面驱动课的主角）
└── lib            库
```

### 路径三种写法

```bash
/home/zhuchao/project    # 绝对路径：从 / 出发，任何时候都有效
./code/01.c              # 相对路径：. = 当前目录
../课本/01-位运算.md      # .. = 上一级
cd -                     # 回到上一个目录（两个目录间跳来跳去神器）
cd                       # 直接回家 = cd ~
```

**坑**：文件名带空格要加引号 `cd "my dir"`；**Linux 文件名区分大小写**；`/` 是分隔符所以文件名不能含 `/`。

---

## 知识点 2：文件操作六件套（练成肌肉记忆）

```bash
ls          # 列目录      -l 详细（权限大小时间）  -a 含隐藏(.开头)  -h 人类可读大小  -t 按时间
cd          # 切目录      cd .. 上一级   cd ~ 回家   cd - 回上次
cp a b      # 复制        cp -r dir1 dir2 复制目录（recursive）
mv a b      # 移动/改名   mv old new；mv file dir/
mkdir       # 建目录      mkdir -p a/b/c 一次建整条路径
rm          # 删除        rm -r dir 删目录   rm -f 强制
```

**⚠️ 没有回收站**：`rm` 删了就是没了。最危险的命令没有之一：

```bash
rm -rf /某路径     # 递归+强制删除，写错路径 = 系统没了
```

保命习惯：**删之前先 `ls` 一遍同样的路径**（确认删的是啥），再原样换成 `rm -r`。新手期给自己立个规矩：`rm` 前必须先 `ls`。

**上手练**（现在就敲）：

```bash
mkdir -p ~/tmp_test/{a,b}/sub    # 一口气建 a/sub 和 b/sub
cd ~/tmp_test
touch a/1.txt a/2.txt            # touch 建空文件
cp a/1.txt b/                    # 复制
mv a/2.txt a/renamed.txt         # 改名
ls -R                            # 递归看结构
rm -r ~/tmp_test                 # 收尾
```

---

## 知识点 3：查看文件五件套——日志是嵌入式日常

```bash
cat file       # 全部倒出来（小文件）
less file      # 分页看：↑↓ 滚动、/关键词 搜索（n 下一个）、q 退出——大文件首选
head -n 20 f   # 前 20 行
tail -n 20 f   # 后 20 行
tail -f log    # ★ 持续跟踪新内容——看实时日志的标准姿势（串口日志/系统日志）
wc -l f        # 数行数（word count - lines）
```

**`tail -f` 是嵌入式工程师的看家本领**：板子跑着，日志刷着，`tail -f /var/log/syslog` 挂在旁边，插拔设备瞬间就能看到内核打印。先体验：

```bash
tail -f /var/log/syslog     # 权限不够就 sudo，或用 dmesg --follow
# Ctrl+C 退出
```

---

## 知识点 4：查找双雄——find 与 grep（驱动调试主力）

**find 找文件**（按名字/类型/大小在目录树里爬）：

```bash
find ~/project -name "*.c"            # 名字匹配（注意引号，防 shell 展开）
find / -name "gcc" -type f 2>/dev/null   # 全盘找，错误丢掉
find . -size +1M                       # 大于 1MB
find src/ -name "*.c" -exec grep -l "main" {} \;   # 找到后接着 grep（连招预警）
```

**grep 找内容**（在文件里搜字符串）：

```bash
grep "flag" main.c              # 单文件搜
grep -r "TODO" ~/project/       # 递归搜整个目录 ★ 最常用
grep -rn "知识点" 课本/         # -n 显示行号，递归
grep -i "error" log             # 忽略大小写
grep -v "^#" config             # 反向：排除 # 开头的行
grep -c "error" log             # 只数个数
```

**连招**（下一个知识点讲为什么能连）：

```bash
history | grep "gcc"                 # 在历史里找 gcc 命令
grep -rn "知识点3" 作业/ | wc -l      # 搜到几处
ps aux | grep qemu                   # qemu 跑起来没
```

> 内核/驱动调试日常就是：`grep -rn "某函数名" 内核源码/` 定位实现 → `find` 找头文件。这两个命令的手感决定你后面翻内核源码的速度。

---

## 知识点 5：权限三件套——rwx / chmod / sudo

```bash
ls -l a.c
# -rw-rw-r--  1 zhuchao zhuchao 1024 Sep  9 10:00 a.c
#  │└┬┘└┬┘└┬┘     │       │        │        │       │
#  │ 自己 同组 其他  硬链接数  属主    属组     大小    时间
#  └ 第一个字符：- 普通文件 / d 目录 / l 链接 / c,b 字符/块设备（驱动课见！）
```

三组人（自己 u / 同组 g / 其他 o）各三位（**r**读=4 / **w**写=2 / **x**执行=1）：

```bash
chmod 755 script.sh     # rwxr-xr-x：自己全权，其他人读+执行（数字法：4+2+1 / 4+1 / 4+1）
chmod 644 a.c           # rw-r--r--：普通文件标配
chmod +x build.sh       # 加执行权限（符号法）——拿到脚本第一步常干这个
chmod u+x,g-w file      # 符号法精细操作
```

- 目录的 x = 能不能 cd 进去；r = 能不能 ls
- **sudo**：以 root 身份执行一条命令。Ubuntu 默认锁定 root，全靠 sudo
- **执行程序需要 x 权限**——"为什么我下载的脚本跑不起来"十有八九是没 `chmod +x`

**体验**：

```bash
touch t.sh && echo 'echo hi' > t.sh
./t.sh           # Permission denied！
chmod +x t.sh
./t.sh           # hi
rm t.sh
```

---

## 知识点 6：管道与重定向——Unix 哲学的核心

**三个默认数据口**：每个命令都有 stdin(0) 键盘 / stdout(1) 屏幕 / stderr(2) 屏幕。

```bash
cmd > file       # stdout 重定向到文件（覆盖）
cmd >> file      # 追加
cmd 2> err.log   # stderr 重定向（编译警告收集神器）
cmd > all 2>&1   # stdout + stderr 都进文件（背下来，编译内核记录日志用）
cmd < file       # stdin 从文件来
cmd1 | cmd2      # ★ 管道：cmd1 的 stdout 接到 cmd2 的 stdin
```

**管道是 Unix 哲学的化身**：每个命令只干一件小事，用 `|` 串起来干大事：

```bash
cat 课本/*.md | wc -l                    # 所有课本多少行
ls -l /usr/bin | wc -l                   # 数命令
history | tail -20                       # 最近 20 条命令
grep -rn "volatile" 课本/ | wc -l        # volatile 出现几次
ls | grep "0" | sort | head -5           # 三连招
```

> 嵌入式实战场景：编译内核时 `make 2>&1 | tee build.log`——屏幕上看着，同时全存进文件，报错可回溯。`tee` = 三通管，双向输出。

---

## 知识点 7：进程与作业

```bash
ps aux                 # 全部进程快照（aux 是 BSD 风格三参数，别拆问）
ps aux | grep a.out    # 找特定进程
top                    # 实时刷新的进程监视器（q 退出；按 P 按 CPU 排序、M 按内存）
kill 12345             # 给 PID 发终止信号（默认 SIGTERM，可被捕获）
kill -9 12345          # SIGKILL，必杀（同时意味着来不及保存/清理）
killall a.out          # 按名字杀
```

**后台运行**（编译大项目/跑服务器时用）：

```bash
./a.out &              # & 放后台跑，立刻还给终端
jobs                   # 看后台作业
fg                     # 拉回前台（fg %1 指定编号）
Ctrl+Z                 # 暂停当前前台 → bg 放后台继续
nohup ./a.out &        # 挂断终端也继续跑（跑长任务）
```

**体验**：

```bash
sleep 300 &
jobs
kill %1                # 杀掉作业号 1（或 ps 找 PID 用 kill）
```

> `/proc` 就是这里 ps 数据的来源：`ls /proc/<PID>/` 看看，每个进程一个目录——"内核信息伪装成文件"。阶段 3 驱动课回来再看它就不陌生了。

---

## 知识点 8：环境变量与效率神器

**环境变量 = 进程的全局配置表**，最重要的 `PATH`：

```bash
echo $PATH
# /usr/local/bin:/usr/bin:...   冒号分隔的目录列表
# 你敲 gcc，shell 就按这个顺序找名叫 gcc 的可执行文件
```

```bash
export MY_VAR=hello      # 设置（只对当前会话+子进程有效）
echo $MY_VAR
unset MY_VAR
echo $PS1                # 你前面改过的提示符就是它！
```

**永久生效** = 写进 `~/.bashrc`（改完 `source ~/.bashrc`）——你之前改 `LS_COLORS` 就是这套流程。

**效率神器**（现在开始用）：

| 键/命令 | 作用 |
|---------|------|
| `Tab` | 补全命令/路径（连按两下显示候选）——**用得越多省越多** |
| `↑` / `↓` | 翻历史命令 |
| `Ctrl+R` | 搜历史命令（再按继续找上一个匹配）★ |
| `Ctrl+C` | 终止前台程序 |
| `Ctrl+L` | 清屏（= clear） |
| `Ctrl+A` / `Ctrl+E` | 跳到行首/行尾 |
| `Ctrl+U` | 删到行首 |
| `!!` | 上一条命令（`sudo !!` 忘加 sudo 救星 ★） |
| `alias ll='ls -alF'` | 起别名（写进 .bashrc） |

---

## 综合实战：把本课串起来（全跑一遍）

```bash
mkdir -p ~/cmd_drill && cd ~/cmd_drill
# 1. 造点素材
for i in 1 2 3; do echo "log line $i from host$i" > log$i.txt; done
# 2. 看看
ls -l
cat log1.txt
tail -n 2 log1.txt
# 3. 搜索连招
grep -rn "host" . | wc -l
grep -l "host3" *.txt
# 4. 管道连招
cat log*.txt | sort | head -3
cat log*.txt | wc -l
# 5. 权限
cp log1.txt secret.txt && chmod 600 secret.txt && ls -l secret.txt
# 6. 后台
sleep 100 &   jobs   kill %1
# 7. 收尾
cd ~ && rm -r cmd_drill
```

---

## 本课自测（合上课本回答）

1. /etc /home /var /proc /dev 各放什么？"一切皆文件"举两个例子。
2. `rm -rf` 为什么危险？保命习惯是什么？
3. `less` 里怎么搜索？`tail -f` 干什么用？
4. find 和 grep 分工是什么？各自写一条"递归搜"。
5. `chmod 755` 和 `644` 分别是什么权限？目录的 x 意味着什么？
6. 管道 `|` 干了什么事？`2>&1` 什么意思？`tee` 什么用？
7. kill 和 kill -9 区别？怎么把程序放后台？
8. PATH 是什么？为什么敲 gcc 不用写全路径？怎么让环境变量永久生效？

---

## 本课与后面课程的联系

- **阶段 1 系统编程**：写的服务器程序就用今天这套（`./server &` 后台跑、`tail -f` 看日志、`kill` 杀进程）。
- **阶段 3 驱动**：`ls /dev`、`dmesg`、`grep -rn` 翻内核源码——今天的肌肉记忆直接变现。
- **阶段 4 BSP**：`make 2>&1 | tee build.log` 编译内核、串口 `minicom` 里的命令行——全是这节课的延伸。
