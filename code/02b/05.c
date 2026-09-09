#include <stdio.h>
int main(void){
    int a[5] = {10,20,30,40,50};
    int * p = a;
    for(; p < a+5; p++){
        printf("%d ",*p);
    }
    return 0;
}