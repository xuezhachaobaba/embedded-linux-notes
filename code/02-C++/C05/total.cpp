#include<memory>
#include<vector>
#include<cstdio>

class Shape{
    public:
        virtual void speak() = 0;
        virtual ~Shape(){}
};

class Dog : public Shape {
    public:
        void speak() override{
            std::printf("汪！\n");
        }
};

class Cat : public Shape {
    public: 
        void speak() override{
            std::printf("喵~\n");
        }
};

std::unique_ptr<Shape> make_dog(){
    return std::make_unique<Dog>();
}

int main(){
    std::vector<std::unique_ptr<Shape>> zoo;
    zoo.push_back(make_dog());
    zoo.push_back(std::make_unique<Cat>());
    for(const auto & s: zoo){
        s->speak();
    }

    return 0;
}
