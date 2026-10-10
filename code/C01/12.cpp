#include<cstdio>
namespace my_func{
    void fill(int *arr, int n,int val){
        for(int i = 0; i < n; i++) arr[i] = val;
    }
    void dump(int * arr, int n){
        for(int i = 0; i < n; i++ ) std::printf("%d ",arr[i]);
        std::printf("\n");
    }
}

int main(){
    int n = 5;
    int *a = new int[n]{};
    my_func::fill(a,n,9);
    my_func::dump(a,n);
    delete[] a; 
    return 0;
}