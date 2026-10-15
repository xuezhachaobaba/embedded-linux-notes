#include<stdio.h>
#if 0
#define LOG 100


int main(void){
    #ifdef DEBUG
        printf("%d\n", LOG);
    #endif
    printf("Hello World\n");
    return 0;
}
#endif
#if DEBUG
    #define LOG(fmt, ...) printf("[%s:%d] " fmt,__FILE__,__LINE__, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)
#endif

int main(void){
    int x = 10;
    LOG("Hello World\n");
    LOG("x = %d\n",x);  
    LOG("x = %d, y = %d\n",x,20);
    return 0;
}