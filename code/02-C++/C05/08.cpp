#include <stdexcept>
#include<cstdio>

double divide(int a, int b){
    if(b == 0) throw std::runtime_error("div by zero");
    return (double) a/ b;
}
int main(){
    // try{
        // divide(1,0);
    // }catch(const std::exception& e){
        // std::printf("抓到了：%s\n",e.what());
    // }
    try{
        int x = 1/0;
    }catch(const std::exception& e){
        std::printf("抓到了：%s\n",e.what());
    }
    return 0;
}
