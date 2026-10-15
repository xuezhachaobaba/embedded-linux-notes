#include <cstdio>
#include <cstring>
class Buf{
    public:
        Buf(const char * s){
            this->data = new char [strlen(s)+1];
            strcpy(this->data,s);
        }
        //深拷贝构造,我不太会写，看课件写的
        Buf(const Buf &other){
            this->data = new char[strlen(other.data)+1];
            strcpy(this->data,other.data);
        }
              
        ~Buf(){
            delete[] this->data;
        }
    private:
        char *data;
};
int main(){
    Buf a("hello");
    Buf b = a;
    return 0;
}
//=================================================================
//==318684==ERROR: AddressSanitizer: attempting double-free on 0x759d71be0010 in thread T0: