#include <memory>
#include<vector>
#include<cstdio>
#include<stdexcept>

class Shape{
    public:
        virtual void speak() = 0;
        virtual ~Shape(){}
};

class Dog : public Shape{
    void speak() override{
        std::printf("汪!\n");
    }
};
class Cat : public Shape{
    void speak() override{
        std::printf("喵～\n");
    }
};

std::unique_ptr<Shape> make_dog(){
    return std::make_unique<Dog>();
}

std::unique_ptr<Shape> make_Shape(char type ){
    switch(type){
        case 'd': return std::make_unique<Dog>();
        case 'c': return std::make_unique<Cat>();
        default : throw std::runtime_error("不认识的动物!");
    }
}

int main(){
    std::vector<std::unique_ptr<Shape>> zoo;
    // zoo.push_back(make_dog());
    // zoo.push_back(std::make_unique<Cat>());
    try{
        zoo.push_back(make_Shape('d'));
    }catch(const std::exception &e){
        std::printf("抓到了: %s\n",e.what());
    }
    try{
        zoo.push_back(make_Shape('c'));
    }catch(const std::exception &e){
        std::printf("抓到了: %s\n",e.what());
    }

    for(const auto & s : zoo){
        s->speak();
    }
    return 0;
    
}

//工厂函数我不会写，char type要怎么写呢？难道输入cat或者dog，然后用if判断，选择哪一个嘛？