#include <cstdio>

class Stack{

    public:
        Stack(int cap) : cap_(cap),data_(new int[cap]{}),top_(0) {
            std::printf("构造 cap = %d \n",cap);
        }
        // Stack(const Stack& o): cap_(o.cap_), data_(new int[o.cap_]),top_(o.top_){
        //     for(int i = 0; i < top_;i++)
        //         data_[i] = o.data_[i];
        //     std::printf("拷贝构造（深）\n");
        // }

        ~Stack(){
            std::printf("析构 top = %d \n",top_);
            delete[] data_;
        }
        void push(int v){
            data_[top_++] = v;
        }
        int top() const{
            return data_[top_ - 1];
        }
        Stack& operator << (int v){
            push(v);
            return *this;
        }

    private:
        int cap_;
        int *data_;
        int top_;

};

int main(){
    Stack s(8);
    s << 10 << 20 << 30;
    Stack t = s;
    std::printf("top = %d\n",t.top());
    return 0;
}
