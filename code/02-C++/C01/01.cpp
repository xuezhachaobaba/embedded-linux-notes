#include <cstdio>
int main(){
    int a = 10;
    int & r = a;
    printf("a=%d r=%d\n",a,r);
    printf("a=%p r=%p\n",&a,&r);
    r = 99;
    printf("a = %d\n",a);
    return 0;
}