#include <stdio.h>
int main(void){
    int a[3] = {10, 20, 30};
    int *p = a;
    printf("%d %d\n",*p,*(p+2));
}