#include <cstdio>
namespace calc{
    int add(int a, int b){return a+b;}
    double add(double a, double b){return a+b;}

    void double_it(int &x){x *= 2;}

    int scale(int v,int factor = 10){return v * factor;}
}

int main(){
    int n = 21;
    calc::double_it(n);
    std::printf("%d\n",calc::add(n,8));
    std::printf("%g\n",calc::add(1.5,2.5));
    std::printf("%d\n",calc::scale(3));

    int *p = new int(7);
    std::printf("%d\n",*p);
    delete p;



    return 0;
}