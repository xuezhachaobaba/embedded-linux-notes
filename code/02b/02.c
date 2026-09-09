#include <stdio.h>
int main(void){
    int a[3] = {10, 20, 30};
    printf("%d %d\n", a[1],*(a+1));
    return 0;
}