#include<stdio.h>
#include<stdint.h>
int main(void){
    uint32_t x = 0xAABBCCDD;
    uint8_t *p = (uint8_t *)&x;
    printf("字节            内容\n");
    for(int i = 0; i < 4; i++){
        printf("%p  0x%02X\n",(void*)(p+i),p[i]);
    }
    return 0;
}