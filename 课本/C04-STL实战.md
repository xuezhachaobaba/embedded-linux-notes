# C04：STL 实战

> STL = C++ 的标准工具箱。面试里 C++ 题一半在考容器（vector 必考、string 必用）；写应用层代码基本是 string + vector 起手。这课的地基你全有：**vector 内部 = 06 课的堆 + 02b 的数组，sort 的比较器 = 05 课的函数指针**——STL 不玄学，就是把你手写过的东西自动化。
> 编译：`g++ -Wall -std=c++17 xx.cpp -o xx`。

---

## 知识点清单（共 8 个）

| # | 知识点 | 考频 |
|---|--------|------|
| 1 | std::string——告别 char* 裸奔 | ⭐⭐⭐ |
| 2 | std::vector——会自己长大的数组 | ⭐⭐⭐ |
| 3 | vector 的内存机制：搬家与失效 ⭐ 头号面试坑 | ⭐⭐⭐ |
| 4 | 迭代器：统一遍历一切容器 | ⭐⭐⭐ |
| 5 | std::map：有序键值表 + [] 的副作用 | ⭐⭐ |
| 6 | sort 与比较器（05 课函数指针回接） | ⭐⭐⭐ |
| 7 | at() vs []：越界的两种下场 | ⭐⭐ |
| 8 | 容器选型 + 嵌入式能不能用 STL | ⭐ |

---

## 知识点 1：std::string——告别 strcat/strlen/strcmp

```cpp
#include <cstdio>
#include <string>

int main() {
    std::string s1 = "hello";
    std::string s2 = s1 + " world";        // 拼接：不用 strcat、不怕越界
    int         n  = s1.size();            // 长度 5：strlen 拜拜
    char        c  = s1[0];                // 下标访问，跟数组一样
    bool      same = (s1 == "hello");      // ⚠️ 比的是内容！
    std::string sub = s2.substr(0, 5);     // 子串：(起点, 个数)
    size_t     pos = s2.find("world");     // 找子串
    std::printf("%s %d %d %zu\n", s2.c_str(), n, (int)same, pos);
    return 0;
}
```

- **内部**= 堆上的动态字符数组（06 课）+ 自动 new/delete——**你一根手指都不用碰**
- `s1 == "hello"`：char* 世界里 `==` 比的是**地址**（所以 C 里要用 strcmp），string 重载了 `==` 比**内容**——运算符重载的第一次见面，C02 讲过原理，这就是它的日常价值
- `find` 找不到返回 `std::string::npos`（一个特大值），判断要写 `if (pos != std::string::npos)`
- `c_str()`：转成 `const char*`，喂给 printf / 老接口（两个世界的桥）

---

## 知识点 2：std::vector——会自己长大的数组

```cpp
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v;             // 空的
    v.push_back(3);                 // 尾部追加
    v.push_back(1);
    v.push_back(4);
    std::printf("size=%zu\n", v.size());   // 3
    std::printf("%d %d\n", v[0], v.back()); // 3 4
    v.pop_back();                   // 删尾部（变 3 1）

    std::vector<int> a(5, 0);       // 5 个 0
    std::vector<int> b = {1, 2, 3}; // 列表初始化
    return 0;
}
```

- C 数组 `int a[5]` 编译期定死；vector **运行期随便长**——这就是 C01 作业 Q12 里"传参别扭"的根源解药：vector 可以整个传（见知识点 4）
- **内存视角（06 课技能）**：元素在堆上；vector 对象本身（一般在栈上）只存"数据指针 + size + capacity"三个字段——所以 `sizeof(std::vector<int>)` 恒为 24（64 位），跟装了多少元素无关

---

## 知识点 3：搬家与失效 ⭐ vector 头号坑（面试必考）

push_back 时容量不够了，vector 会：

1. 在堆上 new 一块**更大的**新数组（gcc 的实现通常**翻倍**）
2. 把旧元素全部搬过去
3. delete 旧数组
4. 更新自己的数据指针

于是有了两个概念：

- **size**：实际装了几个
- **capacity**：不搬家最多能装几个

**头号坑**：搬家之后，**所有指向旧位置的指针、引用、迭代器全部失效**（06 课的悬空指针换了个马甲）。经典事故：

```cpp
std::vector<int> v = {1, 2, 3};
int* p = &v[0];
v.push_back(4);        // 容量 3 已满 → 搬家！
std::printf("%d\n", *p);   // 💥 p 还指着已 delete 的旧数组（UAF）
```

- 已知要装 n 个：`v.reserve(n)` 预先备足容量，避免反复搬家（性能手段）
- 面试话术：「push_back 可能触发重新分配，导致原有的迭代器和指针失效；避免方法是 reserve 预留，或操作后重新获取迭代器。」

---

## 知识点 4：迭代器——统一遍历一切容器

```cpp
std::vector<int> v = {1, 2, 3, 4};

// 写法一：下标（数组的老朋友）
for (size_t i = 0; i < v.size(); i++) std::printf("%d ", v[i]);

// 写法二：迭代器
for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    std::printf("%d ", *it);

// 写法三：范围 for——就是写法二的语法糖
for (int x : v) std::printf("%d ", x);

// 写法四：只读 + 零拷贝（string/大结构体必用这个）
for (const auto& x : v) std::printf("%d ", x);
```

- `begin()` 指向第一个，`end()` 指向**最后一个的下一个**（半开区间 `[begin, end)`——`end()` 本身永远不能解引用）
- `*it` 解引用——迭代器就是"泛化指针"，string、map、vector 全用同一套写法遍历，这就是"统一"的含义
- `auto`：让编译器推类型（`const auto&` = 元素只读且不拷贝）
- **引用传参回来了**：`void dump(const std::vector<int>& v)`——C01 Q12 里引用没处放的问题，这里自然解决（vector 按引用传，不拷贝全部元素）

---

## 知识点 5：std::map——有序键值表

```cpp
#include <map>

std::map<std::string, int> freq;
freq["apple"] = 3;              // key 不存在 → 创建；存在 → 覆盖
freq["apple"] += 1;

if (freq.count("pear") == 0)    // 查存在：count 或 find
    std::printf("没有 pear\n");

for (const auto& kv : freq)     // 遍历自动按 key 的字典序！
    std::printf("%s -> %d\n", kv.first.c_str(), kv.second);
```

- 内部是红黑树（平衡二叉搜索树）——面试说得出「**有序、查找 O(log n)**」即可，手写实现是阶段 2 的事
- **`[]` 的副作用（坑）**：访问**不存在**的 key 会**自动插入默认值**（int 就是 0）——`if (freq["x"] == 0)` 这一查，map 里多了个 "x"！**查询用 find/count，修改才用 []**
- 经典应用：词频统计、配置表、缓存计数

---

## 知识点 6：sort 与比较器（05 课函数指针回接）

```cpp
#include <algorithm>   // sort 在这里，不在 vector 里

std::sort(v.begin(), v.end());              // 默认升序（用 <）

bool cmp_desc(int a, int b) { return a > b; }
std::sort(v.begin(), v.end(), cmp_desc);    // 降序：传函数指针！
```

给结构体排序（嵌入式/业务代码天天干的事）：

```cpp
struct Student {
    std::string name;
    int score;
};

bool by_score(const Student& a, const Student& b) {
    return a.score > b.score;        // 分数高的排前面
}

std::vector<Student> stus = {{"Tom", 78}, {"Jerry", 92}, {"Ann", 85}};
std::sort(stus.begin(), stus.end(), by_score);
```

- **cmp(a, b) 返回 true 的含义：「a 应该排在 b 前面」**
- ⚠️ **cmp 里别写 `>=`**：相等也返回 true 违反"严格弱序"，sort 可能越界崩溃（UB）——只写 `<` / `>`
- 这就是 05 课 qsort 比较器的 C++ 版：类型安全（不用 `const void*` + 强转），传的还是函数指针
- 预告 C05：lambda 三行变一行 `std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });`

---

## 知识点 7：at() vs []——越界的两种下场

```cpp
std::vector<int> v = {1, 2, 3};
std::printf("%d\n", v[3]);     // 越界：未定义行为——可能崩，更可能静默输出垃圾
try {
    std::printf("%d\n", v.at(3));   // 越界：抛异常 std::out_of_range
} catch (const std::out_of_range& e) {
    std::printf("抓到了: %s\n", e.what());
}
```

- `[]`：不检查，极致性能，出了事自己负责（02b 课越界读垃圾的老朋友）
- `at()`：带边界检查，越界抛异常，可以被抓住处理
- 异常机制 C05 正式讲，今天先混个脸熟，见到 `try/catch` 不慌即可

---

## 知识点 8：容器选型 + 嵌入式视角

选型三句话：

- **默认 vector**：连续内存、缓存友好、按下标最快
- 要 **key→value 查找且要有序**：map（O(log n)）
- **定长且小**（尤其是要和 C 接口对接、映射寄存器/协议）：C 数组最直接

面试可能问「嵌入式能用 STL 吗？」——加分回答：

> 「资源允许就用：string/vector 在现代嵌入式完全常规；map 内存开销大、异常在实时/极小资源场景要慎重。另外内核和驱动是纯 C，STL 用不上——它属于应用层和面试技能包。」

这也正是我们阶段 0.5 的定位：**面试够用 + 能写应用层**。

---

## 综合示例：词频统计（一页串起本课）

```cpp
#include <cstdio>
#include <string>
#include <map>

int main() {
    const char* words[] = {"the", "quick", "brown", "fox", "the", "jumps", "the"};
    std::map<std::string, int> freq;

    for (const char* w : words)
        freq[w]++;   // ⚠️ 想想：这里 [] 的"副作用"这次为什么反而正好有用？

    for (const auto& kv : freq)          // 自动按字典序输出
        std::printf("%-8s%d\n", kv.first.c_str(), kv.second);
    return 0;
}
```

**先预测**：输出几行？顺序是什么？the 是几？（提示：`freq[w]++` = 不存在就插入 0、然后 ++。）

---

## 本课自测（合上课本回答）

1. string 的 `==` 和 char* 的 `==` 比的东西有什么本质区别？
2. vector 的 size 和 capacity 分别是什么？push_back 时两者怎么变？
3. **为什么 push_back 会导致指针/迭代器失效？**（把"搬家三步"说一遍）怎么避免？
4. `end()` 指向哪？为什么不能解引用？
5. map 的 `[]` 有什么副作用？查询应该用什么？
6. cmp(a,b) 返回 true 是什么意思？为什么不能写 `>=`？
7. `v[i]` 和 `v.at(i)` 越界时分别发生什么？
8. 「嵌入式能用 STL 吗」——你的 30 秒面试版回答？

---

## 本课与后面课程的联系

- **C05**：lambda 让 sort 比较器三行变一行；智能指针 + vector 合体管资源；异常正式讲。
- **阶段 2 数据结构**：你会手写一个简化 vector——亲眼看懂"搬家"是怎么实现的。
- **阶段 1 系统编程**：读文件、解析配置、socket 收发的缓冲区，string/vector 是日常主食。
- **对照内核（阶段 3）**：内核没有 STL，但 `list_head`、`rbtree`、`kfifo` 就是 C 手写的容器——现在学的是"它们在 C++ 里的样子"。
