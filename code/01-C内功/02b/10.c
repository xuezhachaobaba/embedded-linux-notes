#include<stdio.h>
int main(void){
    int a=1, b=2;
    const int *p1= &a;
    int * const p2 = &a;

    *p1 = 10;
    p1 = &b;
    *p2 = 10;
    p2 = &b;
}