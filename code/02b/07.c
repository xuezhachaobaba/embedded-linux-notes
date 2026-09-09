#include <stdio.h>
int main(void){
    int a[5];
    int *p = a;
    printf("%zu %zu\n",sizeof(a),sizeof(p));
    return 0;
}