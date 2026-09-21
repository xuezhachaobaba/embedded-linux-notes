#include<stdio.h>
#include<stdlib.h>
int main(void){
    int * a = (int*)malloc(sizeof(int));
    free(a);
    free(a);
}