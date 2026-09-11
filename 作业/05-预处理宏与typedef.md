# 作业 05：预处理、宏与 typedef

> 老规矩：**每题先预测，能跑的编译运行验证**。宏的题特别适合"先脑内展开再跑"——展开对了才算真会。
> 只把"卡住的 / 想确认的"发我。配套讲义：`课本/05-预处理宏与typedef.md`。

---

## 1. `[考：知识点1]` 上机：亲眼看预处理

写一个 `dump.c`（内容照课本知识点1），然后：

```bash
gcc -E dump.c -o dump.i
wc -l dump.i
grep -n 'int a' dump.i
```

**答**（贴出 wc -l 的行数，和 grep 到的那一行替换后的样子）：
wc -l dump.i 
845 dump.i
grep -n 'int a' dump.i
532:extern int asprintf (char **__restrict __ptr,
841:    int a = 10;

## 2. `[考：知识点2]` 对比

`#define PI 3.14` 和 `const double pi = 3.14;` 的三个区别（提示：类型、时机、作用域）：

**答**：类型，#define PI 3.14没有类型，const double pi = 3.14是double类型；时机，define在预处理阶段就会把文件内的所有PI替换成3.14，纯替换，const double pi是const修饰的变量，编译期还会用；作用域，define的作用于是整个.c文件内，const是定义的作用域内

## 3. `[考：知识点3]` 找错并改正

```c
#define SQUARE(x)  x * x
```

用 `SQUARE(a+1)` 调用时展开成什么？结果对吗？**写出正确版本**：


**答**：
展开成 a+1*a+1 = a+a+1,结果不对
正确版本：#define SQUARE(x) ((x)*(x))

## 4. `[考：知识点3]` 铁律二

```c
#define ADD(a, b)  (a) + (b)
int r = 10 * ADD(2, 3);
```

r = ____？为什么？正确写法：

**答**：
展开之后 r = 10 * (2) + (3) = 23
正确写法:#define ADD(a,b)((a)+(b))

## 5. `[考：知识点4]` 经典翻车（先预测再跑）

```c
#define MAX(a, b)  ((a) > (b) ? (a) : (b))
int i = 5, j = 3;
int m = MAX(i++, j);
printf("%d %d %d\n", m, i, j);
```

**预测**（m、i、j 各是多少？写出展开后的代码）：
m = 6 , i = 7 , j = 3
展开后是int m = ((i++)>(j)?(i++):(j))
开始i = 5, 在(i++)>(j)时，i++之后，i = 6;
所以后面的(i++)里，i是6，所以m = 6，同时i又自增，结束时i = 7;
编译运行后和推测结果一致

## 6. `[考：知识点4]` 举一反三

```c
#define SQUARE(x)  ((x) * (x))
int i = 5;
int r = SQUARE(i++);
printf("%d %d\n", r, i);
```

**预测**（先写展开式再算）：
int r = ((i++)*(i++));
i初始值是5，所以第一个i++的实际值是5，使用完i后，i自增，此时i等于6，所以第二个i的实际值是6，使用完i后，i自增，此时i = 7。所以，r = 5*6 = 30，i = 7
代码运行验证正确，同时编译时，编译器给出了下面的警告：
02.c:5:21: warning: operation on ‘i’ may be undefined [-Wsequence-point]
    5 |     int r = SQUARE(i++);
      |                     ^
02.c:2:27: note: in definition of macro ‘SQUARE’
    2 | #define SQUARE(x) ((x) * (x))
      |  

## 7. `[考：知识点5]` 头文件卫士

为什么每个头文件都要写 `#ifndef/#define/#endif`？从 **#include 的本质**出发解释（什么场景下不加会出错）：

**答**：可以防止重复定义，导致预处理报错。我理解的是，比如说我又三个头文件，a.h b.h c.h，然后a.h和b.h同时都define max，然后c.h #include'a.h' #include'b.h'，这时候如果使用ifndef的话可以防止再预处理阶段出现两次define max导致报错

## 8. `[考：知识点5]` 条件编译实战

写一个 `debug.c`：定义 `LOG` 宏，在 `#ifdef DEBUG` 里打印变量值。然后分别用

```bash
gcc debug.c -o d1
gcc -DDEBUG debug.c -o d2
```

**预测**：两个程序输出有什么区别？（跑完贴对比）

**答**：怎么定义log宏我不会，我等下要回顾课本来写
代码写完了，使用-DDEBUG的会输出ifdef Debug下面的内容，没有使用的则直接跳过了

## 9. `[考：知识点5]` 想一想

`#if 0 ... #endif` 在日常写代码时最常见的用途是什么？比 `/* */` 强在哪？

**答**：可以大段的注视。比如说一段代码比较老旧了，有新代码可以替换了，可以用if0 endif，下次还要用这段代码的时候，直接把0改成1即可，很方便。

## 10. `[考：知识点6]` 玩一下预定义宏

用 `__FILE__`、`__LINE__`、`__func__` 写一个宏 `WHERE_AM_I`，打印"文件:行号:函数名"。写出代码和一次调用的输出：

**答**：这个我不会，等下对照课本写一遍
代码写完了，结果如下
where.c:6:main

## 11. `[考：知识点7]` 对比题

```c
typedef int* tp_t;
#define TP   int*
tp_t a, b;
TP   c, d;
```

a、b、c、d 各是什么类型？**为什么**？

**答**：a和b都是int类型的指针，c是int类型的指针，d是int类型的变量。因为typedef相当于是给类型一个别名，后续都还是这样，而define则是在预处理阶段会替换文字的，所以TP c，d；展开后是 int* c,d;所以给c是指针变量而d是int变量。

## 12. `[考：知识点7]` 综合（函数指针热身 ⭐ 有点超纲，做不出正常）

```c
typedef int (*cmp_t)(const void *, const void *);
```

这定义了个什么？尝试用它声明一个变量并赋值（可以先写一个 `int my_cmp(const void *a, const void *b)` 函数）。能跑通即可，用途下阶段讲。

**答**：感觉像是函数的内容，我看不懂。
我在网上搜了结果，但是代码我看不懂，还是留给你跟我解释吧

---

> 做完自检：Q3/Q4/Q5/Q6/Q11 全对 + 能讲清 Q7 = 本课 pass。
> 然后凭记忆写 `总结/05-预处理宏与typedef.md`。
> 欠账提醒：`总结/02b` 和 `总结/03`（03 刚 12/12，趁热写效果最好）😄
