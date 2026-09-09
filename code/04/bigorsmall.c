#include<stdio.h>
#include<stdint.h>
int main(void){
    uint32_t x = 0x11223344;
    uint8_t * p = (uint8_t * ) &x;
    if(*p == 0x44){
        printf("小端 (little-endian)\n");
    }else{
        printf("大端 (big-endian)\n");
    }
}
