#include<stdio.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
int main(void){
    int i = 5, j =3;
    int m = MAX(i++,j);
    printf("%d %d %d\n", m,i,j);
    return 0;
}