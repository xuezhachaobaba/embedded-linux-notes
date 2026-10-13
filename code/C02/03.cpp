#include <cstdio>
class A{
    public: 
        A() {
            std::printf("构造\n");
        }
        ~A(){
            std::printf("析构\n");
        }
};
int main(){
    A a1;
    {
        A a2;
        A a3;
    }
    std::printf("-- 出内层{} --\n");
    A a4;
    return 0;
}