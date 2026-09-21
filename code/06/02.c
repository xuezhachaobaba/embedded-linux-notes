#include <stdio.h>
#include <stdlib.h>

void inner(int depth){
    int x;
    printf("depth %d: %p\n",depth,(void*)&x);
    if(depth>0) inner(depth -1);
}
int main(void){
    inner(5);
    return 0;
}