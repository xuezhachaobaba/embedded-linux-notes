#include<stdio.h>
#include<stdlib.h>

int main(void){
    int *a = (int*)malloc(10*sizeof(int));
    int *b = (int*)malloc(10*sizeof(int));
    for(int i = 0; i <=10; i++){
        a[i] = i;
    }
    for(int i = 0; i <10; i++){
        b[i] = i;
    }
    free(a);
    free(b);
    return 0;
}