#include<stdio.h>
#include<stdlib.h>
int main(void){
    static int a[10*1024*1024];
    a[0] = 1;
    return 0;
}