#include<cstdio>
class Shape{
    public:
        Shape(){
            std::printf("Shape 构造\n");
        }
        virtual double area() const = 0;
        virtual ~Shape() {
            std::printf("Shape 析构\n");
        }
};

class Rect : public Shape{
        double w,h;
    public:
        Rect(double w,double h):w(w),h(h){
            std::printf("Rect 构造\n");
        }
        double area() const override{
            return w*h;
        }
        ~Rect(){
            std::printf("Rect 析构\n");
        }
};

class Circle : public Shape{
        double r;
    public:
        Circle(double r):r(r){
            std::printf("Circle 构造\n");
        }
        double area() const override{
            return 3.14 * r * r;
        }
        ~Circle(){
            std::printf("Circle 析构\n");
        }
};

int main(){
    Shape * arr[] = {new Rect(2,3), new Circle(1)};
    double total = 0;
    for(Shape *s :arr){
        total += s->area();
    }
    std::printf("total = %g\n", total);
    for(Shape * s :arr){
        delete s;
    }
    return 0;
}
//预测
//Shape 构造 -> Rect 构造 -> Shape 构造 -> Circle 构造 -> total = 9.14 -> Rect 析构 -> Shape 析构 -> Circle 析构 -> Shape 析构