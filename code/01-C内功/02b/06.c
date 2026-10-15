#include <stdio.h>
int main(void){
    int a[5];
    int *p1 = &a[1],*p2=&a[4];
    printf("%ld\n",p2-p1);
}