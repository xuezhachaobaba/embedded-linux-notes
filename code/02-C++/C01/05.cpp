#include<cstdio>
void f(int x){x = 100;}
void g(int *p){*p = 100;}
void h(int &r){r = 100;}

int main(){
    int a = 1,b = 2, c = 3;
    f(a);g(&b);h(c);
    std::printf("%d %d %d\n",a,b,c);
}