#include<stdio.h>
#include<stdint.h>
int main(void){
    uint32_t x = 0x12345678;
    uint8_t *p = (uint8_t *)&x;

    printf("地址            内容\n");
    for(int i = 0; i < 4; i++){
        printf("%p  0x%02X\n",(void*)(p+i),p[i]);
    }
    struct{char c; int i; char d;}s = {'A',0x12345678,'B'};
    uint8_t *q = (uint8_t*)&s;
    printf("\nstruct {char,int,char}的内存:\n");
    for(int i = 0; i < sizeof(s);i++){
        printf("字节%2d: 0x%2X\n",i,q[i]);
    }
    return 0;
}