#include<memory>
#include<cstdio>

int main(){
    std::unique_ptr<int> p = std::make_unique<int>(42);
    std::printf("%d\n",*p);

    std::unique_ptr<int> q = std::move(p);
    if(!p) 
        std::printf("p 已经交出去了\n");

    return 0;
}