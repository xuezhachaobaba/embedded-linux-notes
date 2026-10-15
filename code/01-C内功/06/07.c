#include<stdio.h>
#include<stdlib.h>

int main(void){
    int *a = (int *)malloc(sizeof(int));
    *a = 10;
    free(a);
    printf("%d",*a);
    return 0;
}