# 作业 C04：STL 实战

> 老规矩：先预测再跑。本课预测重点是 **capacity 的增长规律**（Q4）和 **迭代器失效事故**（Q6）。
> 涉及 Q6 的题用 `g++ -Wall -std=c++17 -fsanitize=address -g` 编译。
> 只把"卡住的 / 想确认的"发我。配套讲义：`课本/C04-STL实战.md`。

---

## 1. `[考：知识点1]` string 基操（先预测再跑）

```cpp
#include <cstdio>
#include <string>

int main() {
    std::string s1 = "embedded";
    std::string s2 = s1 + " linux";
    std::printf("len=%zu\n", s2.size());
    std::printf("sub=%s\n", s2.substr(0, 8).c_str());
    std::printf("%d\n", s1 == "embedded");
    size_t pos = s2.find("linux");
    std::printf("pos=%zu nofind=%zu\n", pos, s2.find("xxxx"));
    return 0;
}
```

**预测**（五行输出各是什么？`find` 找不到时那个数大概长什么样？）：

## 2. `[考：知识点1]` 两个世界的桥

写代码验证：① 把 `std::string s = "hello"` 喂给 `printf("%s", ...)`——缺什么、怎么补？② 反向：`const char* c = "world";` 怎么变成 string 并拼接到 s 后面？

**答**：

## 3. `[考：知识点2]` vector 全流程

创建空 vector，push_back 五个数，打印 size、第一个、最后一个；再 pop_back 一次打印 size。最后 `sizeof(std::vector<int>)` 是多少？为什么和元素个数无关？

**答**：

## 4. `[考：知识点3]` capacity 增长实验 ⭐ 本课必做

```cpp
std::vector<int> v;
for (int i = 0; i < 33; i++) {
    v.push_back(i);
    std::printf("size=%2zu capacity=%2zu\n", v.size(), v.capacity());
}
```

**预测**：capacity 会按什么规律涨？总共搬几次家？
**跑完回答**：gcc 实际的规律是什么？(1,2,4,8,16,32,64…？) 搬家发生在哪些时刻？

**答**：

## 5. `[考：知识点4]` 遍历四式

同一个 vector 用讲义里的四种写法各遍历一遍（下标 / iterator / 范围 for / const auto&）。然后写 `void dump(const std::vector<int>& v)`——**这里为什么必须用引用？不用引用会发生什么？**

**答**：

## 6. `[考：知识点3]` 迭代器失效事故现场 ⭐ 本课 Boss 题

```cpp
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};
    int* p = &v[0];
    v.push_back(4);
    std::printf("%d\n", *p);
    return 0;
}
```

a) **预测**：`*p` 会打印什么？为什么？
b) 用 ASan 编译运行——贴报错（报错名 + 哪一行）
c) 用知识点 3 的"搬家三步"解释：p 到底还指着什么？
d) 两种修法？

**答**：

## 7. `[考：知识点5]` map[] 的副作用（先预测再跑）

```cpp
std::map<std::string, int> m;
m["apple"] = 3;
std::printf("%zu\n", m.size());
if (m["pear"] == 0) std::printf("pear 是 0\n");
std::printf("%zu\n", m.size());
```

**预测**：两个 size 各是多少？为什么第二行之后变了？查询的正确姿势是什么？

**答**：

## 8. `[考：知识点5]` 词频统计

用讲义综合示例的数据 `{"the", "quick", "brown", "fox", "the", "jumps", "the"}` 写词频统计。**先预测**输出的行数和顺序，再跑。然后改用 `find` 只查询 "fox" 出现次数（不许新增条目）。

**答**（贴预测 + 输出）：

## 9. `[考：知识点6]` sort + 自定义比较器

```cpp
struct Student {
    std::string name;
    int score;
};
```

造 4 个学生 {{"Tom",78},{"Jerry",92},{"Ann",85},{"Bob,92"}→名字自定}，按**分数从高到低**排序后输出名次榜。分数相同的按名字字典序。**追问**：cmp 里为什么不能写 `a.score >= b.score`？（可以试试故意写错，看看会不会崩——不保证崩，这本身就是答案的一部分）

**答**：

## 10. `[考：知识点7]` 越界两种下场（先预测再跑）

```cpp
std::vector<int> v = {1, 2, 3};
std::printf("A: %d\n", v[3]);
try {
    std::printf("B: %d\n", v.at(3));
} catch (const std::out_of_range& e) {
    std::printf("C: %s\n", e.what());
}
```

**预测**：A 行会怎样（一定崩吗）？B/C 行呢？跑两三次感受 A 的"不保证"。

**答**：

## 11. `[考：知识点8]` 概念（面试口吻）

「你平时怎么选容器？vector 和 map 的取舍？」——30 秒版。
追问：「嵌入式项目里能用 STL 吗？」——用讲义知识点 8 的话术答。

**答**：

## 12. `[考：综合]` C01 Q12 续集：vector 版改写 ⭐ 呼应上一课

把 C01 作业 12.cpp（my_func::fill / dump 那个）改写成 vector 版：`fill(std::vector<int>& v, int val)`、`dump(const std::vector<int>& v)`——**上一课你没处安放的引用传参，现在有家了**。new/delete、malloc 全都不要了。写完说说：为什么 vector 版比指针版短、还不容易错？

**答**：

---

> 做完自检：Q4 能说出翻倍规律 + Q6 能讲清失效原因并修掉 + Q8 词频跑通且能解释 [] 副作用恰好有用 = 本课 pass。
