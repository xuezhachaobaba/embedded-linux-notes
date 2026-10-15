#include<cstdio>
namespace ns {
    int version = 2;
    void info(){
        std::printf("ns v2\n");
    }
}

int main(){
    // ns::info();
    // using ns::info; info();
    using namespace ns; info();

    return 0;
}