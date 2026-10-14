#include <cstdio>
class Animal{
    public:
        Animal(const char * name):name(name){}
        virtual void speak(){}
        virtual ~Animal() = default;
    protected:
        const char * name;
};

class Dog :public Animal{
    public:
        Dog(const char * name):Animal(name){}
        void speak() override{
            std::printf("%s : 汪汪\n",name);
        }
};

class Cat : public Animal{
    public: 
        Cat(const char *name):Animal(name){}
        void speak() override{
            std::printf("%s : 喵喵\n",name);
        }
};

void make_sound(Animal ** arr,int count){
    for(int i = 0; i < count ; i++){
        arr[i]->speak();
    }
}

int main(){
    Animal * arr[] = {new Dog("小白"),new Cat("Bamboo")};
    int count = 2;
    make_sound(arr,count);
    for(Animal * a: arr){
        delete a;
    }
    return 0;
}