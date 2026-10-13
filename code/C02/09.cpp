#include<cstdio>
class IntArray{
    public:
        IntArray(int n){
            size = n;
            arr = new int[n]{};
        }
        IntArray(const IntArray & other){
            std::printf("拷贝构造\n");
            this->size = other.size;
            this->arr = new int[this->size]{};
            for(int i = 0; i < this->size; i++){
                this->arr[i] = other.arr[i];
            }        
        }
        IntArray& operator=(const IntArray & other){
            if (this == &other)
            return *this; // 自赋值保护

            delete[] arr;
            this->size = other.size;
            this->arr = new int[this->size]{};
            for(int i = 0; i < this->size; i++){
                this->arr[i] = other.arr[i];
            } 
            return *this;
        }
        ~IntArray(){
            delete[] arr;
        }
        // void init(int * a,int n){
        //     for(int i = 0; i < n ; i++){
        //         this->arr[i] = *(a+i);
        //     }
        // }
        
        void mod(int i , int a){
            this->arr[i-1] = a;
        }

        int & at(int i){
            return this->arr[i];
        }
        void print(){
            for(int i = 0; i < size; i++){
                std::printf("%d ",arr[i]);
            }
            std::printf("\n");
        }
    private:
        int size;
        int * arr;
};

void dump(IntArray x){
    std::printf("函数里: \n");
    x.print();
}

int main(){
    IntArray a(10);
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    // a.init(arr,10);
    for(int i = 0; i < 10; i++){
        a.at(i) = i*i;
    }
    a.print();
    dump(a);
    return 0;
}