#include<cstdio>
class A{
    public:
        void f(){
            std::printf("A::f\n");
        }
        virtual void g(){
            std::printf("A::g\n");
        }
};
class B : public A{
    public:
        void f(){
            std::printf("B::f\n");
        }
        void g(){
            std::printf("B::g\n");
        }
};

int main(){
    A * p = new B;
    p->f();
    p->g();
    return 0;
}

