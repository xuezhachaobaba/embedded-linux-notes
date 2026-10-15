#include<stdlib.h>
int main(void){
    char *p = malloc(100);
    p[0] = 'x';
    free(p);
    return 0;
}