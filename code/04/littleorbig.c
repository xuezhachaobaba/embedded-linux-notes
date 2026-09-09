#include<stdio.h>
#include<stdint.h>
union 
{
    uint32_t num;
    uint8_t p[4];
}t;
int main(void){
    t.num = 0x11223344;
    // if(t.p[0] == 0x44){
    //     printf("小端 little-endian\n");
    // }else{
    //     printf("大端 big-endian\n");
    // }
    printf("%s\n",t.p[0] == 0x44 ? "小端":"大端");
    return 0;
}
