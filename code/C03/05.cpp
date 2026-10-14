#include <cstdio>
class A{
    public :
    int x;
};
class B{
    public:
        virtual void f(){}
        int y;
};

/* ===== 旧实验（printf 直接塞对象，B 编译不过——教训留在注释里）=====
int main(){
    A *a = new A;
    A *c = new A;
    B *b = new B;
    B *d = new B;
    a->x = 0x1122;
    b->y = 0x3344;
    c->x = 0x5566;
    d->y = 0x7788;
    std::printf("地址   内容？\n");
    std::printf("%p 0x%lx\n",(void*)a,*a);
    std::printf("%p 0x%lx\n",(void*)c,*c);
    std::printf("%p 0x%lx\n",(void*)b,*b);
    std::printf("%p 0x%lx\n",(void*)d,*d);
    delete a;
    delete b;
    delete c;
    delete d;
    return 0;
}
===== 旧实验结束 ===== */

/* ===== Q6 正确姿势版（把上面 main 的实验整个换成这个）=====
   上一个版本的坑：printf 不能直接塞对象——A 会给警告（读不到 vptr），
   B 有虚函数连编译都过不了。正确做法：memcpy 把对象【头 8 字节】
   搬进 uint64_t 再打印。

#include <cstdio>
#include <cstdint>
#include <cstring>

class P { public: virtual void f(){} int y; };
class Q { public: virtual void g(){} int z; };

int main(){
    P b1, b2;          // 同类两个对象
    Q d;               // 不同类对象
    uint64_t h1, h2, h3;
    std::memcpy(&h1, &b1, 8);   // 把 b1 的头 8 字节搬进 h1
    std::memcpy(&h2, &b2, 8);
    std::memcpy(&h3, &d,  8);
    std::printf("b1 头8字节: 0x%lx\n", h1);
    std::printf("b2 头8字节: 0x%lx\n", h2);
    std::printf("d  头8字节: 0x%lx\n", h3);
    std::printf("b1==b2? %s   b1==d? %s\n",
                (h1==h2)?"相同":"不同", (h1==h3)?"相同":"不同");
    return 0;
}

===== 先预测再跑：三行各是什么？最后的"相同/不同"各是什么？=====
===== 结论一句话填空：这 8 字节是________，同类对象它________，不同类对象它________。===== */
