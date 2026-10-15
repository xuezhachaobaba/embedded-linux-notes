#include<stdio.h>
#define SQUARE(x) ((x) * (x))
int main(void){
    int i = 5;
    int r = SQUARE(i++);
    printf("%d %d\n",r,i);
    return 0;
}