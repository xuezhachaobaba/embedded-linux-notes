#include <cstdio>
class Animal{
    public:
        Animal(const char * name):name(name){}
    protected:
        const char * name;
        void eat(){
            std::printf("%s 在吃\n",this->name);
        }
};
class Dog : public Animal{
    
    public:
        Dog(const char * name):Animal(name){}
        void dogeat(){
            this->eat();
        }
        void bark(){
            std::printf("%s : 汪汪\n",this->name);
        }
};



int main(){
    Dog d("xiaobai");
    d.bark();
    d.dogeat();
    return 0;
}