#include<cstdio>
class Point {
    public:

        Point& move(int dx,int dy){
            this->x += dx;
            this->y += dy;
            return *this;
        }
        //为什么move返回引用而不是void？因为如果返回void，函数也可以实现move功能，但是不能实现链式调用；
        //最开始是point来调用的move，返回*this后，还是point的引用，也就是说当前的结果可以继续调用point的方法，来实现链式调用
        void set(int x, int y){
            this->x = x;
            this->y = y;
        }
        void get(){
            std::printf("(%d,%d)\n",this->x,this->y);
        }
    private:
        int x,y;

};
int main(){
    Point p;
    p.set(1,2);
    p.move(1,2).move(10,20).move(100,200);
    p.get();
}
//关于this的值和&p之间的关系，this指的是point这个类的位置，它就是&p，this->x和&p.x的位置相同，
//不过this是在类内使用的，所以尽管xy是private，也可以访问，但是&p是在类外，无法访问&p.x或y

