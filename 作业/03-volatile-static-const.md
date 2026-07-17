# 作业 03：volatile / static / const

> 本节 **volatile 的效果要在 `-O2` 下才明显，且很多题是概念题（没法直接跑）**——这正常，理解 WHY 比跑代码重要。static / const 的题可以跑。
> 做完只把"卡住的 / 想确认的"发我。配套讲义：`课本/03-volatile-static-const.md`。

---

## 1. `[考：知识点1、3]` 概念（这题跑不出效果，靠想）

```c
int flag = 0;          // 在中断里会被设成 1
while (flag == 0) { }  // 等 flag 变 1
```

开了优化（`-O2`）时，这段代码可能出什么问题？**怎么修？**

**答**：

## 2. `[考：知识点4]` 判断对错

"`volatile` 让变量的读写在单条指令内完成，不会被中断打断（即原子操作）。"

**对还是错？为什么？**

**答**：

## 3. `[考：知识点4]` 判断对错

"`volatile` 能保证多线程下的正确同步，用了 volatile 就不用加锁。"

**对还是错？为什么？**

**答**：

## 4. `[考：知识点2]` 嵌入式场景

为什么要这样写硬件寄存器访问？
```c
volatile uint32_t *reg = (volatile uint32_t*)0x40021000;
```
**不加 volatile 会怎样？**

**答**：

## 5. `[考：知识点5]`

`const volatile int *status` 表示什么？**什么场景会用**？

**答**：

## 6. `[考：知识点6]` 预测输出（可跑）

```c
int counter(void) {
    static int n = 0;
    return ++n;
}
int main(void) {
    printf("%d\n", counter());
    printf("%d\n", counter());
    printf("%d\n", counter());
    return 0;
}
```

**预测**：

## 7. `[考：知识点6]` 概念

`static` 局部变量存在**哪里**（栈 / 静态存储区）？**初始化几次**？

**答**：

## 8. `[考：知识点7]` 概念

在 `a.c` 里写 `static int secret;` 和（不写 static 的）`int secret;` 有什么**区别**？

**答**：

## 9. `[考：知识点8]` 预测（可编译验证）

```c
const int x = 5;
x = 10;
```

能编译过吗？为什么？

**答**：

## 10. `[考：知识点8]` 概念

为什么要用 const 修饰函数参数，比如 `void print(const char *s)`？至少说两点好处。

**答**：

## 11. `[考：综合]` 用一句话分别解释

各用一句话说清 `volatile` / `static` / `const` 的作用（像面试那样口头表达）。

- volatile：
- static：
- const：

## 12. `[考：知识点1、2]` 找错（不用跑，会段错误）

```c
uint32_t *p = (uint32_t*)0x40000000;   // 某状态寄存器地址
while ((*p & 0x01) == 0) { }           // 等 bit0 变 1
```

这段在开了优化时**可能不工作**，为什么？**怎么修？**

**答**：
