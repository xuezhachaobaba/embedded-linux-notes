#include<cstdio>
#include<memory>

int main(){
    auto a = std::make_shared<int>(10);
    std::printf("A: %ld\n",a.use_count());
    {
        auto b = a;
        auto c = a;
        std::printf("B: %ld\n",a.use_count());
    }
    std::printf("C: %ld\n",a.use_count());
    auto d = a;
    std::printf("D: %ld\n",a.use_count());
    return 0;
}