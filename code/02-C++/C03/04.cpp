// #include<cstdio>
// class A {int x;};
// class B {virtual void f(){} int x;};
// class C : public B{int y;};

// int main(){
//     A * p1 = new A;
//     B * p2 = new B;
//     B * p3 = new C;
//     std::printf("%zu %zu %zu",sizeof(p1),sizeof(p2),sizeof(p3));
//     delete p1;delete p2; delete p3;
//     return 0;
// }
#include<cstdio>
class A {int x;};
class B {
public:
    virtual void f(){}
    virtual ~B() = default; // 加上虚析构
    int x;
};
class C : public B{int y;};
int main(){
// A * p1 = new A;
// B * p2 = new B;
// B * p3 = new C;
// std::printf("%zu %zu %zu",sizeof(p1),sizeof(p2),sizeof(p3));
// std::printf("%zu %zu %zu\n",sizeof(*p1),sizeof(*p2),sizeof(*p3));
// delete p1;delete p2; delete p3;
std::printf("%zu %zu %zu\n",sizeof(A),sizeof(B),sizeof(C));
return 0;
}
