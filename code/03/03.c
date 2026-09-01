#include<stdio.h>
int main(void){
    int a[5] = {0,10,20,30,40};
    int *p = a;
    printf("%d\n",*(p+3));
}