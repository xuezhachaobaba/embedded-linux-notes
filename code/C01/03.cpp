#include <cstdio>
int main(){
    int a = 10;
    int & r = a;
    r += 5;
    std::printf("a=%d r=%d\n",a,r);
    std::printf("&a=%p &r=%p\n",&a,&r);
    int b = 100;
    r = b;
    std::printf("a=%d r=%d\n",a,r);
    return 0;
}