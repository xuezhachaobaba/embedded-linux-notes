#include<cstdio>
class Shape{
    public:
        virtual double area() const = 0;
        virtual ~Shape(){}
};

class Circle : public Shape{
    double r;
    public:
        Circle(double r):r(r){}
        double area() const override{
            return 3.14 * r * r;
        }
        ~Circle(){}
};

class Rect : public Shape{
    double a,b;
    public:
        Rect(double a, double b):a(a),b(b){}
        double area() const override{
            return a*b;
        }
        ~Rect(){}
};
int main(){
    new Shape;
    Shape s;
    return 0;
}