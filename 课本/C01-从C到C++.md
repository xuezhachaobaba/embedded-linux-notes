# C01：从 C 到 C++（起步课）

> 欢迎进入 **阶段 0.5：C++**。定位先说死：目标是**面试够用 + 能写应用层**——不钻模板元编程、不追新标准全部特性。你有 7 课 C 内功底子，这节课的打法是"**新概念全部对照 C 讲**"，学起来会快得多。
>
> 编译器换 `g++`（已装好，15.2）。编译：`g++ xx.cpp -o xx`；开警告：`g++ -Wall -std=c++17 xx.cpp -o xx`（C++ 用标准 c++17）。
> 文件后缀：`.cpp`（头文件 `.hpp` 或不带后缀的 `.h` 都行，我们用 `.hpp`）。

---

## 知识点清单（共 8 个）

| # | 知识点 | 考频 |
|---|--------|------|
| 1 | C++ 是什么关系：兼容大部分 C、新增大件 | ⭐ 背景 |
| 2 | 引用（reference）：`int&` ——指针的"糖衣"，必考 | ⭐⭐⭐ |
| 3 | 引用 vs 指针：三大区别（必考对比题） | ⭐⭐⭐ |
| 4 | 函数重载（overload）+ 为什么 C 不行 | ⭐⭐⭐ |
| 5 | 默认参数 | ⭐⭐ |
| 6 | new / delete：C++ 的 malloc/free（带构造析构） | ⭐⭐⭐ |
| 7 | 命名空间 namespace | ⭐⭐ |
| 8 | C++ 杂项速览：bool / iostream 初见 / 函数必须声明原型 | ⭐⭐ |

---

## 知识点 1：C++ 和 C 是什么关系

- C++ 最初就是"C with Classes"（Bjarne Stroustrup, 1979），**几乎兼容所有 C 语法**——你的 C 功夫直接带过来
- 但**思想升级了**：C 是"过程式"（函数+数据），C++ 是"多范式"（面向对象 + 泛型 + 过程式都行）
- 兼容≠相同：C++ 更严格（比如 `void*` 不能隐式转、函数必须先声明），有些 C 代码用 g++ 编不过——正常
- 一个文件两种编法体会差异：`gcc hello.c` vs `g++ hello.cpp`。实际项目里常见**混合编程**（驱动内核纯 C，应用层 C++）——嵌入式两种都要会

> 学法建议：每个新概念都问一句"这解决了 C 的什么痛点？"——这节课的答案分别是：引用→传参改值太绕、重载→起名地狱、new→malloc 不管初始化、namespace→全局命名爆炸。

---

## 知识点 2：引用——给变量起别名

C 里想让函数改外面的变量，得传指针：

```c
// C 风格
void add_ten(int *x) { *x += 10; }
int a = 5;
add_ten(&a);        // 要取地址、函数里要解引用
```

C++ 给了更优雅的写法——**引用**：

```cpp
// C++ 风格
void add_ten(int& x) { x += 10; }   // x 是外面那个变量的别名
int a = 5;
add_ten(a);         // 直接传，函数里改 x 就是改 a
printf("%d\n", a);  // 15
```

**读法**：`int& x` = "x 是某个 int 的引用（别名）"。调用时**什么都不用做**，C++ 在背后把 a 的"挂钩"传了进去。

**本质（面试要会）**：引用在底层**通常就是用指针实现的**（传地址），只是编译器帮你自动解引用、不让你看到地址。所以"引用是指针的安全糖衣"。

三条规则（都是考试点）：

1. **定义时必须初始化**，且**绑定后不能换人**：

```cpp
int a = 1, b = 2;
int& r = a;    // ✅ r 是 a 的别名
r = b;         // ⚠️ 这不是"改绑"！这是把 b 的值赋给 a（a 变 2）
int& r2;       // ❌ 编译错：引用必须初始化
```

2. **对引用的一切操作都作用在被引用者身上**：`r++` 就是 `a++`；`&r` 就是 `&a`（同一个地址）。

3. 没有"引用的引用"、没有引用数组、没有引用的指针（都是语法层面禁止——因为它不是对象，只是别名）。

**跑一个看清一切**：

```cpp
#include <cstdio>
int main() {
    int a = 10;
    int& r = a;
    printf("a=%d r=%d\n", a, r);        // 10 10
    printf("&a=%p &r=%p\n", &a, &r);    // 同一个地址！
    r = 99;
    printf("a=%d\n", a);                // 99 —— 改 r 就是改 a
    return 0;
}
```

---

## 知识点 3：引用 vs 指针——三大区别（必考）

| | 指针 `int*` | 引用 `int&` |
|---|---|---|
| ① 本体 | 独立对象，**占 8 字节**，有自己的地址 | 别名，**不占额外空间**（底层是指针但语法上无实体） |
| ② 可否换指向 | 可以 `p = &b;` 随便换 | **绑定终身**，不能换 |
| ③ 可否为空 | 可以 `NULL`/`nullptr` | **不能为空**（必须初始化绑定实体） |

由此推出的工程习惯：

- 函数参数想"改外面"或"避免拷贝大对象" → **能用引用就用引用**（安全：不可能空、不会忘初始化）
- 需要"可能不指向任何东西"（可空）或"需要换指向"或"做数组遍历" → 用指针
- 由此诞生 C++ 最常见的函数签名形态：

```cpp
void big_func(const std::string& name);   // const 引用传参：不拷贝 + 承诺不改 —— C++ 传大对象的标准姿势
```

`const T&` 传参 = "只读 + 免拷贝"，**这个组合后面每一课都在用**，现在混个脸熟。

---

## 知识点 4：函数重载——同名函数，不同参数

C 的痛点：算最大值要 `max_int / max_double / max_float` 起一串名。C++ 允许**同名、参数不同**的函数共存：

```cpp
int    my_max(int a, int b)        { return a > b ? a : b; }
double my_max(double a, double b)  { return a > b ? a : b; }
int    my_max(int a, int b, int c) { return my_max(my_max(a, b), c); }   // 参数个数不同也行

my_max(3, 5);        // 调 int 版
my_max(3.14, 2.71);  // 调 double 版
```

编译器按**实参类型/个数**自动挑——这个机制叫**重载决议**。

**重载的判据是参数（类型/个数/顺序），跟返回值无关**：

```cpp
int  f(int);
void f(int);     // ❌ 不构成重载，编译错：仅返回值不同不行
```

**为什么 C 不行（面试常问）**：编译器生成的符号名不同。C 里 `my_max` 就是 `"my_max"`一个符号，两个同名必冲突；C++ 会把参数类型编进符号（叫 **name mangling**，如 `_Z6my_maxii`），天然不冲突。这个知识点阶段 1 讲链接时还会回来（`extern "C"` 就是关掉 mangling，让 C++ 函数被 C 调）。

> 小实验：`printf("%p\n", (void*)my_max);` 各重载版本地址不同。也可以 `nm a.out | grep my_max` 看到编译后的真实符号名（作业里玩）。

---

## 知识点 5：默认参数——从后往前连续给

```cpp
void log_msg(const char* s, int level = 1, bool flush = false) {
    /* ... */
}
log_msg("hi");            // level=1, flush=false，没写的用默认
log_msg("hi", 3);         // flush=false
log_msg("hi", 3, true);   // 全给
```

规则两条：

1. 默认值**只能从右往左连续**地给（右边有了左边才能有）：

```cpp
void f(int a, int b = 2, int c = 3);   // ✅
void f(int a = 1, int b, int c = 3);   // ❌ 中间断档不行
```

2. 调用时有默认的实参**从左往右**填，不能跳过中间的。

**坑**：声明和实现分离时，默认值只能写在**声明**里（写两遍会报重定义默认值）。

---

## 知识点 6：new / delete——带"生命周期管理"的 malloc/free

对照着记：

```cpp
// C
int *p = malloc(10 * sizeof(int));
free(p);

// C++
int* p = new int;             // 单个 int（未初始化）
int* q = new int(42);         // 单个 int，初始化 42
int* arr = new int[10]{};     // 10 个 int 的数组，{} 全清零（C++11 起）
delete p;                     // 单对象用 delete
delete[] arr;                 // 数组必须用 delete[] ！！
```

三条铁律：

1. **配对**：`new` ↔ `delete`，`new[]` ↔ `delete[]`。**混用是 UB**（`new[]` 的内存头部记着元素个数，`delete` 不处理这个头——和 free 靠堆元数据是同款道理，06 课的堆知识直接平移）。
2. new 失败**不返回 NULL**，而是抛异常 `std::bad_alloc`（C 的 malloc 返回 NULL）。想拿到老行为用 `new (std::nothrow) int`，返回可能为空。
3. new/delete 和 malloc/free **最本质的区别**：**new 会调用构造函数，delete 会调用析构函数**（下节课的主角）。对 int 这种没构造函数的，行为几乎一样；对类对象，天差地别——这就是为什么**不能用 free 释放 new 出来的类对象**。

**malloc/free 和 new/delete 现在怎么选**：写 C++ 就用 new/delete（马上全换智能指针，C05 课）；只有跟 C 接口打交道时才用 malloc。

---

## 知识点 7：命名空间——治全局命名爆炸

C 的痛点：项目大了，`read()` `count()` 这种名字到处撞（03 课学过 static 能藏文件内，但跨文件的全局函数/类型还是撞）。C++ 的解法：

```cpp
namespace driver {
    void init() { /* ... */ }
    namespace v2 {                     // 可以嵌套
        void init() { /* 新版 */ }
    }
}

driver::init();        // :: 是作用域运算符
driver::v2::init();

using namespace driver;    // 引入后可省前缀（写练习方便）
init();
```

三个使用守则（工程习惯，也是面试谈资）：

1. **头文件里永远不写 `using namespace std;`**（会污染所有包含者的全局空间）；`.cpp` 里随意
2. 习惯写 `std::` 前缀的人被认为更专业 😄（本书课本也尽量 std::）
3. `std::cout` 的 `std` 就是命名空间——C++ 标准库全家都住在 `std` 里

---

## 知识点 8：杂项速览

**bool 类型**：C 里用 `int 0/1` 模拟（C99 的 `_Bool` 没人用），C++ 是一等公民：

```cpp
bool ok = true;
if (ok) { /* ... */ }
```

**iostream 初见**（C++ 的 printf）：

```cpp
#include <iostream>
int main() {
    int x = 42;
    std::cout << "x = " << x << std::endl;   // 自动识别类型，不用 %d
    return 0;
}
```

`<<` 是左移运算符的**重载**（C++ 可以给运算符换含义，下下节课讲）；`std::endl` = 换行+刷新缓冲。好处：类型安全（不会 %d 写成 %s 崩掉）；坏处：比 printf 啰嗦、慢。两种都会用即可，我们课里 printf/cout 混着来。

**函数必须先声明再使用**：C 里 int 函数不声明也能偷偷编过（警告），C++ **直接报错**。老老实实写原型/头文件。

**变量可以随用随定义**：C89 必须块首声明变量，C++/C99 起随处定义（`for (int i = 0; ...)` 你早就这么写了）。

---

## 综合示例：一页纸用上全部 8 个知识点

```cpp
#include <cstdio>

namespace calc {
int  add(int a, int b)             { return a + b; }
double add(double a, double b)     { return a + b; }          // 重载

void double_it(int& x)             { x *= 2; }                 // 引用

int  scale(int v, int factor = 10) { return v * factor; }      // 默认参数
}

int main() {
    int n = 21;
    calc::double_it(n);                       // 命名空间 + 引用：n 变 42
    std::printf("%d\n", calc::add(n, 8));     // 重载决议选 int 版 → 50
    std::printf("%g\n", calc::add(1.5, 2.5)); // double 版 → 4
    std::printf("%d\n", calc::scale(3));      // 默认参数 → 30

    int* p = new int(7);                      // new
    std::printf("%d\n", *p);
    delete p;                                 // delete
    return 0;
}
```

**先预测每行输出，再 `g++ -Wall -std=c++17` 跑**。

---

## 本课自测（合上课本回答）

1. 引用是什么？底层怎么实现？三条规则？
2. 引用 vs 指针的三大区别？什么时候选谁？`const T&` 传参为什么是标准姿势？
3. 重载的判据是什么？为什么 C 不支持？（name mangling 说了什么）
4. 默认参数的两条规则？
5. new/delete vs malloc/free：配对铁律、失败行为、本质区别？
6. `new[]` 出来的用 `delete` 释放会怎样？
7. 命名空间解决什么问题？头文件里为什么不能 using namespace？

---

## 本课与后面课程的联系

- **C02**：类与对象——构造/析构函数就是 new/delete 调用的那两个东西，这课的伏笔立刻兑现。
- **C03**：虚函数——函数指针（05 课）+ 类（C02）合体，驱动的 ops 表原理全打通。
- 阶段 1 混合编程：C++ 程序调 C 库（`extern "C"`），name mangling 知识落地。
