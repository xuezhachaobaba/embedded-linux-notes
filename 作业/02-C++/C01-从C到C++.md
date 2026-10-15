# 作业 C01：从 C 到 C++

> 编译用 `g++ -Wall -std=c++17 xx.cpp -o xx`（注意不是 gcc）。老规矩：先预测再跑。
> 只把"卡住的 / 想确认的"发我。配套讲义：`课本/02-C++/C01-从C到C++.md`。

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
预测：a=15 r=15
    &a=a的地址 &r=a的地址
    a=100 r=100
    因为引用是直接引用原来的变量的地址，而且初始化之后，是不会改变对象的，所以r从一开始用的就是a的地址，所以两个的数值和地址是一样的；再r = b时候，r不是修改引用的对象，而是r现在对象的数值从15变成b的数值，所以第二次a和r的数值还是一样，都是100；
运行结果：
a=15 r=15
&a=0x7ffdcdd4d838 &r=0x7ffdcdd4d838
a=100 r=100


## 2. `[考：知识点2]` 传参对比

用两种写法各写一个"交换两个变量"的函数并调用验证：① C 风格指针版 `void my_swap(int* a, int* b)` ② 引用版 `void my_swap(int& a, int& b)`。贴代码+输出。然后说说调用端哪个更难误用（提示：指针版可能传什么进去？）：

**答**：
#include<cstdio>
void my_swap(int *a,int *b){
    int c;
    c = *a;
    *a = *b;
    *b = c;
}
void my_swap(int &a,int &b){
    int c;
    c = a;
    a = b;
    b = c;
}
int main(){
    int a = 10,b = 5;
    int c = 1,d = 2;
    std::printf("a=%d b=%d\n",a,b);
    std::printf("c=%d d=%d\n",c,d);
    my_swap(&a,&b);
    my_swap(c,d);
    std::printf("a=%d b=%d\n",a,b);
    std::printf("c=%d d=%d\n",c,d);
    return 0;
}
我觉得调用段指针版更难，指针版可能会传a和b的数值，而不是地址
a=10 b=5
c=1 d=2
a=5 b=10
c=2 d=1

## 3. `[考：知识点3]` 对比题（面试原题）

引用和指针的三大区别？各在什么场景用？——合上课本用自己的话写：

**答**：
1.指针可以为空，引用必须初始化；
2.指针可以修改对象，引用初始化之后对象不可变
3.指针可以指向数组和指针，引用不能指向数组和指针
普通的变量，且后续补修改对象的，可以使用引用，但是需要更换对象、指向数组指针的，只能用指针。

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
a=1，b=100，c=100；
a是把数值传给形式参数的，在f函数里，x=100，再函数结束之后，也消散了，数值没有传回给a
b是通过指针把b的地址传递给p的，再g函数里，*p直接是使用b的地址的内容修改的，修改的数值就是b的数值
c是通过引用传递参数的，r就是c，r的地址就是c的地址，所以修改r，就是修改c本身

## 5. `[考：知识点4]` 重载实操

写三个重载的 `print`：`print(int)`、`print(double)`、`print(const char*)`，main 里各调一次。再试：`print(3.14f)`（float）能调吗？调的是哪个？为什么？

**答**（贴代码+输出+分析）：
代码：
#include<cstdio>
void print(int a){std::printf("%d\n",a);}
void print(double a){std::printf("%f\n",a);}
void print(const char* a){std::printf("%c\n",*a);}
int main(){
    print(10);
    print(12.6);
    char a = 'c';
    print(&a);
    print(3.14f);
    return 0;
}
输出：
10
12.600000
c
3.140000
分析：
print(3.14f)是可以调用的，调用的是float的那个，因为3.14f也是float的数据格式，所以就调用了这个

## 6. `[考：知识点4]` 动手验证 name mangling

写一个只有 `int add(int,int)` 和 `double add(double,double)` 的程序编译成可执行文件，然后：

```bash
nm ./a.out | grep add
```

**贴出 nm 的输出**（能看到两个 add 的真实符号名长得不一样）。再写一个纯 C 的 `int add(int,int)` 用 `gcc` 编译，同样 `nm | grep add`——对比 C 和 C++ 的符号名区别：

**答**：
nm ./07 | grep add
0000000000001141 T _Z3adddd
0000000000001129 T _Z3addii

nm ./08 | grep add
0000000000001129 T add

## 7. `[考：知识点4]` 判断

"`int f(int)` 和 `void f(int)` 能构成重载。"——对吗？为什么？

**答**：
不能，如果只有函数类型不一样的话，不能构成重载

## 8. `[考：知识点5]` 默认参数

写 `void greet(const char* name, const char* prefix = "Hello", int times = 1)`，循环打印 times 次 `prefix, name!`。三种调用各跑一遍：`greet("Tom")` / `greet("Tom", "Hi")` / `greet("Tom", "Hi", 3)`。再试 `greet("Tom", , 2)` 会怎样？

**答**：
Tom hello
Tom Hi
Tom Hi
Tom Hi
Tom Hi

再尝试greet("Tom",,2)的时候，直接编译报错了：
09.cpp: In function ‘int main()’:
09.cpp:14:17: error: expected primary-expression before ‘,’ token
   14 |     greet("Tom",,2);
      |                 ^
我们默认参数是从右往左定义的，要依次定义；使用的时候要从左往右使用，不能左边默认右边使用自己的值；

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
预测输出:42 7 0
new int[5]{}的{}是将申请的5个数组的值初始化为0

./10
42 7 0

## 10. `[考：知识点6]` 错配实验（感受一下就行）

把上面第 9 题的 `delete[] arr` 故意改成 `delete arr`，用 `g++ -Wall -fsanitize=address` 编译运行。**贴 ASan 报错第一行**（你会看到 alloc-dealloc-mismatch 之类的字样）。看完改回来。

**答**：
g++ -Wall -std=c++17 10.cpp -o 10
10.cpp: In function ‘int main()’:
10.cpp:8:12: warning: ‘void operator delete(void*, long unsigned int)’ called on pointer returned from a mismatched allocation function [-Wmismatched-new-delete]
    8 |     delete arr;
      |            ^~~
10.cpp:4:27: note: returned from ‘void* operator new [](long unsigned int)’
    4 |     int* arr = new int[5]{};

## 11. `[考：知识点7]` 命名空间

建 `ns` 命名空间，里面放 `int version = 2;` 和 `void info()`（打印 "ns v2"）。分别用三种方式调用 info：① `ns::info()` ② `using ns::info; info();` ③ `using namespace ns; info();`。然后回答：为什么头文件里不能写 ③？

**答**：
如果头文件里写上using namespace ns，就相当于携带了该头文件的文件里的info都用ns里的info，这样起不到命名空间该有的作用
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
看12.cpp的代码，new/delete和命名空间我有使用上，但是传参，这个例子里好使用引用吗？

---

> 做完自检：Q1/Q4/Q7/Q9 全对 + Q3 能说满三条 = 本课 pass。
> 批改 2026-10-10：过 ✅（错题12：float 提升误判；Q3 第三条、Q7 理由见批改记录）
> 总结已停写（2026-09-30 起）。
