#include<stdio.h>

#define WHERE_AM_I() printf("%s:%d:%s\n",__FILE__,__LINE__,__func__)

int main(void){
    WHERE_AM_I();
    return 0;
}