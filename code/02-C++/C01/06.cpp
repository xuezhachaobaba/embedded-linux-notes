#include<cstdio>
void print(int a){std::printf("%d\n",a);}
void print(double a){std::printf("%f\n",a);}
void print(const char* a){std::printf("%c\n",*a);}
int main(){
    print(10);
    print(12.6);
    char a = 'c';
    print(&a);
    print(3.14f);
    return 0;
}