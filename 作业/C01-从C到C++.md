# 作业 C01：从 C 到 C++

> 编译用 `g++ -Wall -std=c++17 xx.cpp -o xx`（注意不是 gcc）。老规矩：先预测再跑。
> 只把"卡住的 / 想确认的"发我。配套讲义：`课本/C01-从C到C++.md`。

---

## 1. `[考：知识点2]` 引用初体验（先预测再跑）

```cpp
#include <cstdio>
int main() {
    int a = 10;
    int& r = a;
    r += 5;
    std::printf("a=%d r=%d\n", a, r);
    std::printf("&a=%p &r=%p\n", &a, &r);
    int b = 100;
    r = b;
    std::printf("a=%d r=%d\n", a, r);
    return 0;
}
```

**预测**（三行输出各是什么？"r = b" 之后 a 是多少？为什么）：

## 2. `[考：知识点2]` 传参对比

用两种写法各写一个"交换两个变量"的函数并调用验证：① C 风格指针版 `void my_swap(int* a, int* b)` ② 引用版 `void my_swap(int& a, int& b)`。贴代码+输出。然后说说调用端哪个更难误用（提示：指针版可能传什么进去？）：

**答**：

## 3. `[考：知识点3]` 对比题（面试原题）

引用和指针的三大区别？各在什么场景用？——合上课本用自己的话写：

**答**：

## 4. `[考：知识点3]` 读代码

```cpp
void f(int  x)  { x = 100; }
void g(int* p)  { *p = 100; }
void h(int& r)  { r = 100; }

int main() {
    int a = 1, b = 2, c = 3;
    f(a); g(&b); h(c);
    // a b c 各是多少？
}
```

**预测**（a/b/c 各多少？为什么）：

## 5. `[考：知识点4]` 重载实操

写三个重载的 `print`：`print(int)`、`print(double)`、`print(const char*)`，main 里各调一次。再试：`print(3.14f)`（float）能调吗？调的是哪个？为什么？

**答**（贴代码+输出+分析）：

## 6. `[考：知识点4]` 动手验证 name mangling

写一个只有 `int add(int,int)` 和 `double add(double,double)` 的程序编译成可执行文件，然后：

```bash
nm ./a.out | grep add
```

**贴出 nm 的输出**（能看到两个 add 的真实符号名长得不一样）。再写一个纯 C 的 `int add(int,int)` 用 `gcc` 编译，同样 `nm | grep add`——对比 C 和 C++ 的符号名区别：

**答**：

## 7. `[考：知识点4]` 判断

"`int f(int)` 和 `void f(int)` 能构成重载。"——对吗？为什么？

**答**：

## 8. `[考：知识点5]` 默认参数

写 `void greet(const char* name, const char* prefix = "Hello", int times = 1)`，循环打印 times 次 `prefix, name!`。三种调用各跑一遍：`greet("Tom")` / `greet("Tom", "Hi")` / `greet("Tom", "Hi", 3)`。再试 `greet("Tom", , 2)` 会怎样？

**答**：

## 9. `[考：知识点6]` new/delete 全流程（先预测再跑）

```cpp
#include <cstdio>
int main() {
    int* p = new int(42);
    int* arr = new int[5]{};
    arr[2] = 7;
    std::printf("%d %d %d\n", *p, arr[2], arr[4]);
    delete p;
    delete[] arr;
    return 0;
}
```

**预测**：输出？`new int[5]{}` 的 `{}` 干了什么？

## 10. `[考：知识点6]` 错配实验（感受一下就行）

把上面第 9 题的 `delete[] arr` 故意改成 `delete arr`，用 `g++ -Wall -fsanitize=address` 编译运行。**贴 ASan 报错第一行**（你会看到 alloc-dealloc-mismatch 之类的字样）。看完改回来。

**答**：

## 11. `[考：知识点7]` 命名空间

建 `ns` 命名空间，里面放 `int version = 2;` 和 `void info()`（打印 "ns v2"）。分别用三种方式调用 info：① `ns::info()` ② `using ns::info; info();` ③ `using namespace ns; info();`。然后回答：为什么头文件里不能写 ③？

**答**：

## 12. `[考：综合]` 改写实战

把下面 C 代码改写成"C++ 风格"（引用传参 + new/delete + 命名空间 + 重载），功能不变：

```c
#include <stdio.h>
#include <stdlib.h>
void fill(int* arr, int n, int val) {
    for (int i = 0; i < n; i++) arr[i] = val;
}
void dump(int* arr, int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}
int main(void) {
    int n = 5;
    int* a = malloc(n * sizeof(int));
    fill(a, n, 9);
    dump(a, n);
    free(a);
    return 0;
}
```

**代码**（改写要点至少体现：引用传参、new/delete、命名空间；重载可选——比如 dump 支持换分隔符）：

---

> 做完自检：Q1/Q4/Q7/Q9 全对 + Q3 能说满三条 = 本课 pass。
> 本课总结也先欠着，阶段末统一补 😄
