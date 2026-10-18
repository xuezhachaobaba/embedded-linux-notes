#include<cstdio>
#include<memory>
int main(){
    std::unique_ptr<int[]> arr(new int[5]{});
    for(int i = 0; i < 5; i++){
        arr[i] = i*i;
    }
    for(int i = 0; i < 5; i++){
        std::printf("%d ",arr[i]);
    }
    std::printf("\n");
    return 0; 
}