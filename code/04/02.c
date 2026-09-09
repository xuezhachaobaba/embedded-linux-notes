#include<stdio.h>
#include<stdint.h>
struct __attribute__((packed)) Hdr {
    uint8_t ver;
    uint32_t seq;
    uint16_t len;
};
int main(void){
    struct Hdr s;
    s.ver = 0x12;
    s.seq = 0xAABBCCDD;
    s.len = 0x3344;
    uint8_t *p = (uint8_t*)&s;
    printf("字节            内容\n");
    for(int i = 0; i <7; i++){
        // printf("%d,%0xp\n",i+1,p[i]);
        printf("%p  0x%02X\n",(void*)(p+i),p[i]);
    }
    return 0;
}