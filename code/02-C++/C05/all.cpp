#include<cstdio>
#include<stdexcept>
#include<memory>

struct Guard{
    const char * name;
    Guard(const char * n): name(n){
        std::printf("%s: 拿资源\n",name);
    }
    ~Guard(){
        std::printf("%s: 还资源\n",name);
    }
};

void work(bool fail){
    Guard g1("g1");
    if(fail) 
        throw std:: runtime_error("中途出错");
    Guard g2("g2");
}

int main(){
    try{
        work(true);
    } catch (const std::exception & e){
        std::printf("main 抓到： %s\n", e.what());
    }

    return 0;
}
//我猜g2的拿资源不会出现，g1的还资源回出现，main里面，trywork，调用work函数，首先guardg1，这时候，g1拿资源，然后iftrue，抛出error，函数中断；
//g1是work函数内的，所以函数中断后g1析构，g1还资源，跳转回main，catch到error，输出main抓到中途出错

// ./all
// g1: 拿资源
// g1: 还资源
// main 抓到： 中途出错