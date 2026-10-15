#include <stdio.h>
int main(void){
    int a[4] = {1,2,3,4};
    int *p = a;
    char *c = (char*)a;
    printf("%zu %zu\n",sizeof(p),sizeof(c));
}