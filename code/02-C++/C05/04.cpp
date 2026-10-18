#include<cstdio>
#include<memory>

class Guard{
        const char * name;
    public:
        Guard(const char * name):name(name){
            std::printf("Guard enter\n");
        }
        ~Guard(){
            std::printf("Guard leave\n");
        }
};

int main(){
    std::unique_ptr<int> p = std::make_unique<int>(42);
    std::printf("%d\n",*p);
    // std::unique_ptr<int> q = p;
    {
        std::unique_ptr<Guard> g(new Guard("g"));
    }
    
    std::unique_ptr<int> q = std::move(p);
    if(!p){
        std::printf("p现在为空\n");
    }

    // std::printf("%d %d\n",*q,*p);
    return 0;

}
//用guard类可以看到，unique_ptr在出定义域的时候是会被delete的