#include<cstdio>
#include<vector>
#include<stdexcept>

int main(){
    std::vector<int> v = {1,2,3};
    try{
        v.at(5);
    }catch(const std::exception & e) {
        std::printf("抓到了：%s\n",e.what());
    }
    return 0;
}