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
void f(void){
    A in_f;
    std::printf("-- f 体内 --\n");
}
int main(){
    A outer;
    f();
    std::printf("-- f 返回后 --\n");
    A *p = new A;
    delete p;
    std::printf("-- delete 后 --\n");
    return 0;
}