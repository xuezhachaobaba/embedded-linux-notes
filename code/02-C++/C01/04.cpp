#include<cstdio>
void my_swap(int *a,int *b){
    int c;
    c = *a;
    *a = *b;
    *b = c;
}
void my_swap(int &a,int &b){
    int c;
    c = a;
    a = b;
    b = c;
}
int main(){
    int a = 10,b = 5;
    int c = 1,d = 2;
    std::printf("a=%d b=%d\n",a,b);
    std::printf("c=%d d=%d\n",c,d);
    my_swap(&a,&b);
    my_swap(c,d);
    std::printf("a=%d b=%d\n",a,b);
    std::printf("c=%d d=%d\n",c,d);
    return 0;
}