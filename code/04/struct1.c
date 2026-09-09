#include <stdio.h>
#include <stdint.h>

struct A
{
    char c;
    int i;
    char d;
};

struct B
{
    int i;
    char c;
    char d;
};

int main(void){
    printf("Sizeof(struct A) = %zu\n",sizeof(struct A));
    printf("Sizeof(struct B) = %zu\n",sizeof(struct B));
    return 0;
}