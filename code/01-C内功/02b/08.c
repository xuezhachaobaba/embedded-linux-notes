#include<stdio.h>
void print_size(int arr[]){
    printf("%zu\n", sizeof(arr));
}
int main(void){
    int a[5];
    print_size(a);
    return 0;
}