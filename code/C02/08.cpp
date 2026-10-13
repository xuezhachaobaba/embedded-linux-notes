#include<cstdio>
class Timer{
    public:
        // Timer(int i, int &c):id(i),counter(c){

        // }
        Timer(int i , int & c){
            id = i;
            counter = c;
        }
        void get(){
            std::printf("%d,%d\n",this->id,this->counter);
        }
    private:
        const int id;
        int &counter;
};
int main(){
    int b = 20;
    Timer a(10,b);
    a.get();
    return 0;
}