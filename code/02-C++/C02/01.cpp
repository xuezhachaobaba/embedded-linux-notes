#include<cstdio>
class Counter{
    public:
        void inc(int count){
            this->count += count;
        }
        int get(){
            return this->count;
        }
    private:
        int count = 0;
};
int main(){
    Counter c;
    // c.count = 100;  //这里肯定会报错，因为class里，count定义在private区，所以它是私密的，只能由类内调用，
                    //类外不允许调用
    c.inc(100);
    std::printf("%d\n",c.get());
}