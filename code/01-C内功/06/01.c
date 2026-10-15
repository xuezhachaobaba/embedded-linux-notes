#include<stdio.h>
#include<stdlib.h>

int g_init = 42; 
int g_uninit;
static int s_v = 7;

int main(void){
    int local = 1; 
    static int s_local = 2;
    int *heap = malloc(100);
    char *str = "hello";

    printf("代码区     text:        %p\n",(void*)main);
    printf("已初始化区  .data:       %p\n",(void*)&g_init);
    printf("未初始化区  .bss:        %p\n",(void*)&g_uninit);
    printf("堆区       heap:        %p\n",(void*)heap);
    printf("栈区       stack:       %p\n",(void*)&local);
    printf("常量区     rodata:      %p\n",(void*)str);
    free(heap);

    return 0;

    // 从高地址到低地址分别为栈、内存映射区、堆、.bss、.data、.text
    // 所以预测地址从高到低是，local、heap、g_init、g_uninit、main
    // 常量区在data和bass到那一个，我不知道，好像没具体写
    // 从输出的结果看常量区在bss和data之下，在text之前
}