# 作业 C04：STL 实战

> 老规矩：先预测再跑。本课预测重点是 **capacity 的增长规律**（Q4）和 **迭代器失效事故**（Q6）。
> 涉及 Q6 的题用 `g++ -Wall -std=c++17 -fsanitize=address -g` 编译。
> 只把"卡住的 / 想确认的"发我。配套讲义：`课本/02-C++/C04-STL实战.md`。

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
预测：
len=14
sub=embedded
1
pos=9 nofind=9999999，一个很大的值，我猜的这个

//运行结果
./01
len=14
sub=embedded
1
pos=9 nofind=18446744073709551615，结果比我猜的还要大得多啊




## 2. `[考：知识点1]` 两个世界的桥

写代码验证：① 把 `std::string s = "hello"` 喂给 `printf("%s", ...)`——缺什么、怎么补？② 反向：`const char* c = "world";` 怎么变成 string 并拼接到 s 后面？

**答**：
1.std::string s是一个对象，喂给%s的话，需要指针，所以要使用s.c_str();来补给%s；
2.s += \*c，这个我不会，这是我猜的，c的内容是地址，\*c是c里面的内容，

## 3. `[考：知识点2]` vector 全流程

创建空 vector，push_back 五个数，打印 size、第一个、最后一个；再 pop_back 一次打印 size。最后 `sizeof(std::vector<int>)` 是多少？为什么和元素个数无关？

**答**：
预测：push_back五个数，打印size=5，pop_back打印size=4，最后sizeof结果是24，因为它只存数据指针+size+capacity
./02
1 2 3 4 5 1 5 5
1 4 24
跟我预测一致

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
我猜会按照2的指数级增长，比如开始是1，然后是2，然后是4，然后是8等，到第31，就是第四次搬家完，且空间填满，第32开始第五次搬家，所以总共搬5次➕
./03
size =  1    capacity =  1
size =  2    capacity =  2
size =  3    capacity =  4
size =  4    capacity =  4
size =  5    capacity =  8
size =  6    capacity =  8
size =  7    capacity =  8
size =  8    capacity =  8
size =  9    capacity = 16
size = 10    capacity = 16
size = 11    capacity = 16
size = 12    capacity = 16
size = 13    capacity = 16
size = 14    capacity = 16
size = 15    capacity = 16
size = 16    capacity = 16
size = 17    capacity = 32
size = 18    capacity = 32
size = 19    capacity = 32
size = 20    capacity = 32
size = 21    capacity = 32
size = 22    capacity = 32
size = 23    capacity = 32
size = 24    capacity = 32
size = 25    capacity = 32
size = 26    capacity = 32
size = 27    capacity = 32
size = 28    capacity = 32
size = 29    capacity = 32
size = 30    capacity = 32
size = 31    capacity = 32
size = 32    capacity = 32
size = 33    capacity = 64
开始i=0的时候，创建vector<int> v,给的capacity是1；
i = 1的时候，vector空间不足，第一次搬家，搬家后给的capacity是2；
i = 2的时候，vector空间不足，第二次搬家，搬家后给的capacity是4；
i = 4的时候，vector空间不足，第三次搬家，搬家后给的capacity是8；
i = 8的时候，vector空间不足，第四次搬家，搬家后给的capacity是16；
i = 16的时候，vector空间不足，第五次搬家，搬家后给的capacity是32；
i = 32的时候，vector空间不足，第六次搬家，搬家狗给的capacity是64
我计算反了，少计算了一次


## 5. `[考：知识点4]` 遍历四式

同一个 vector 用讲义里的四种写法各遍历一遍（下标 / iterator / 范围 for / const auto&）。然后写 `void dump(const std::vector<int>& v)`——**这里为什么必须用引用？不用引用会发生什么？**

**答**：
代码写完了，引用传过去之后迭代器的写法用不了了，这里我不太理解为什么呢？引用传过去地址还是原来的地址，为啥begin和end用不了了呢？为什么必须用引用，我也不知道，这点跟我再解释一下
传参会把堆上的vector全部拷一份，但是dump只是看一下，所以必须用引用

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
预测：
可能会打印1，可能会打印其它数字，也可能会直接报错，因为在v.push_back之后，由于原来的v的capacity是3，空间不够，v会搬家，capacity会变成6；
v会新开辟一块内存空间，搬完家之后，把原来的内存空间释放掉；
报错名可能是内存泄漏相关的，在v.push_back(4)这里报错
p还是指向搬家之前的原来的位置，但是这里已经被释放了，是个悬空指针
我会的，第一种，在pushback之前，判断是否v.size == v.capacity,相等的话，等push之后，p = &v[0],重置一下p指针的位置。
第二种，在使用p之前，判断是否p指向null，如果是悬空指针，则重置一下p指针的指向位置
使用之前用p = &p[0],或者用v.reserve(4)来提前征容量

./05
-385730836

./05
=================================================================
==360379==ERROR: AddressSanitizer: heap-use-after-free on address 0x6f23425e0010 at pc 0x646ac9b525a8 bp 0x7ffc384d4390 sp 0x7ffc384d4380

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
我猜第一个size是1，第二个size是2
m["pear"] == 0的时候，如果m里没有pear的话，会创建一个pear，并初始化为0
正确的查询方式，map里有没有.exist方法呢？我能想到的就是用类内的方法里查询

./06
1
pear 是 0
2
运行完居然还输出了pear是0，说明m["pear"]的时候，就已经初始化了pear这个键，并且值为0，所以这里根本逻辑就错了，我猜正确的查询方式是有什么类内定义的方法。
重新翻了一下课件，查询用count或者find，修改才用[]

## 8. `[考：知识点5]` 词频统计

用讲义综合示例的数据 `{"the", "quick", "brown", "fox", "the", "jumps", "the"}` 写词频统计。**先预测**输出的行数和顺序，再跑。然后改用 `find` 只查询 "fox" 出现次数（不许新增条目）。

**答**（贴预测 + 输出）：
//预测，输入5行，顺序是 
// brown 1
// fox 1
// jumps 1
// quick 1
// the 3 
//实际运行和预测一致
// ./total
// brown   1
// fox     1
// jumps   1
// quick   1
// the     3

后面的该用find我不会，也没有理解题目的要求
## 9. `[考：知识点6]` sort + 自定义比较器

```cpp
struct Student {
    std::string name; 
    int score;
};
```

造 4 个学生 {{"Tom",78},{"Jerry",92},{"Ann",85},{"Bob,92"}→名字自定}，按**分数从高到低**排序后输出名次榜。分数相同的按名字字典序。**追问**：cmp 里为什么不能写 `a.score >= b.score`？（可以试试故意写错，看看会不会崩——不保证崩，这本身就是答案的一部分）

**答**：
这个代码我写起来并不熟练，还是很麻烦的，我边写边对照课本上的例题给出的代码，第一次写完的结果如下：
./08
Bob,92
Jerry,92
Ann,85
Tom,78
现在我把cmp函数改一下，看注释之后的效果：
./08
Bob,92
Jerry,92
Ann,85
Tom,78
从结果上来看，似乎和我的写法没什么区别，不能写等号是不同编译器的效果不一致吗？导致不够稳定？我不太懂

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
a行可能崩可能不崩，它肯定是越界了，但是[]并不会检查边界，所以发现不了，不加sfanitize=address的话，不会报错，但是结果肯定一直不一样
b会抓到out_of_range的异常，因为at会检查边界，越界会报异常
c我看不懂，是打印出异常的原因吗？

./09
/usr/include/c++/15/bits/stl_vector.h:1263: std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::operator[](size_type) [with _Tp = int; _Alloc = std::allocator<int>; reference = int&; size_type = long unsigned int]: Assertion '__n < this->size()' failed.
Aborted                    ./09
我的编辑环境版本有点高了，直接给我[]的溢出找出来了，然后中断了
./09
C: vector::_M_range_check: __n (which is 3) >= this->size() (which is 3)
把[]行注释了，看结果，如上面所示


## 11. `[考：知识点8]` 概念（面试口吻）

「你平时怎么选容器？vector 和 map 的取舍？」——30 秒版。
追问：「嵌入式项目里能用 STL 吗？」——用讲义知识点 8 的话术答。

**答**：
需要用到键值对的话选map，需要不固定的数组的可以选择vector，嵌入式项目里能用stl，但是如果和内核对接的，就用c的数组
这段话我大概知道，什么场景大概懂，但是我没办法很精确的表述出来

## 12. `[考：综合]` C01 Q12 续集：vector 版改写 ⭐ 呼应上一课

把 C01 作业 12.cpp（my_func::fill / dump 那个）改写成 vector 版：`fill(std::vector<int>& v, int val)`、`dump(const std::vector<int>& v)`——**上一课你没处安放的引用传参，现在有家了**。new/delete、malloc 全都不要了。写完说说：为什么 vector 版比指针版短、还不容易错？

**答**：
因为vector已经帮我们封装好了，我们只需要去调用它的接口就好，创建和注销都不要去管，大幅的减少了我们的工作内容，做的越少，错的越少，而且它的长度跟着对象走，不需要再参数里再传一个长度n，不用new/malloc和delete/free去配对了，自动释放空间

---

> 做完自检：Q4 能说出翻倍规律 + Q6 能讲清失效原因并修掉 + Q8 词频跑通且能解释 [] 副作用恰好有用 = 本课 pass。
> 批改 2026-10-15：预测-验证闭环执行好（Q1/Q3/Q4/Q7/Q8 预测全中，Q8 词频+字典序全对）；错题16 = Q2 `s += *c` 只拼一个字符、错题17 = Q5 const_iterator 型号拿错、错题18 = Q9 `>=` 比较器 UB（10 万同分实测 segfault）、错题19 = Q6 悬空≠null + UAF 猜成泄漏；Q10 撞上 gcc15 默认开边界断言的彩蛋；待收尾：07 补 find、08 换比较器+const&、10 写 fill+dump 改 const&
> 关课 2026-10-15：收尾三处全过（07 find 四行✓、08 严格弱序+const Student&✓、10 引用版 fill 无警告✓）✅
