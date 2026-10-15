#include<cstdio>
class A {
    int x;
};
class B{
    virtual void f(){

    }
    int x;
};
int main(){
    std::printf("A: %zu\n",sizeof(A));
    std::printf("B: %zu\n",sizeof(B));
    return 0;
}