#include<cstdio>
class Vec2{
    public:
        void get(){
            std::printf("(%.2f,%.2f)\n",this->x,this->y);
        }
        Vec2(double x,double y){
            this->x = x;
            this->y = y;
        }
        Vec2 operator+(const Vec2& a){
            return Vec2(a.x+this->x, a.y+this->y);
        }
        double dot(const Vec2& a,const Vec2& b){
            return a.x * b.x + a.y * b.y;            
        }
    private:
        double x,y;
};
int main(){
    Vec2 a(1,2),b(3,4);
    Vec2 c = a+b;
    double d = a.dot(a,b);
    c.get();
    std::printf("%.2f\n",d);
}

