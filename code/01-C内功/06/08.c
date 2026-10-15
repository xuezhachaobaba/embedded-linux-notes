#include<stdio.h>
#include<stdlib.h>

int main(void){
    int a = 10;
    int *b = &a;
    free(b);
    return 0;
}