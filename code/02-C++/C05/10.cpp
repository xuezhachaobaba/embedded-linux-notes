#include<cstdio>
int main(){
    int base = 100;
    auto f1 = [base](int x){ return base + x;    };
    auto f2 = [&base](int x){ base += x; return base;};
    std::printf("%d\n",f1(1));
    std::printf("%d\n",f2(1));
    std::printf("%d\n",f1(1));
    std::printf("base = %d\n",base);
    return 0;
}