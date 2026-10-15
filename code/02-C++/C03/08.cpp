#include<cstdio>
class Base {
public:
    Base()  { std::printf("Base 构造\n"); }
    ~Base() { std::printf("Base 析构\n"); }
};
class Member {
public:
    Member()  { std::printf("Member 构造\n"); }
    ~Member() { std::printf("Member 析构\n"); }
};
class Derived : public Base {
    Member m;
public:
    Derived()  { std::printf("Derived 构造\n"); }
    ~Derived() { std::printf("Derived 析构\n"); }
};
int main() {
    { Derived d; }
    std::printf("-- 出作用域 --\n");
    return 0;
}