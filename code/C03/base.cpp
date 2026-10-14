#include<cstdio>
class Base{
    public:
        Base(){
            std::printf("Base 构造\n");
        }
        ~Base(){
            std::printf("Base 析构\n");
        }
};
class Derived:public Base{
    int * data;
    public:
        Derived():data(new int[100]){
            std::printf("Derived 构造\n");
        }
        ~Derived(){
            delete[] data;
            std::printf("Derived 析构\n");
        }
};
int main(){
    Base* p = new Derived();
    delete p;
}
//=================================================================
//==329650==ERROR: AddressSanitizer: new-delete-type-mismatch on 0x6d5e591e0010 in thread T0: