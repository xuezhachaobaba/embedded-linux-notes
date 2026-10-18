// #include <stdio.h>
// #include <stdlib.h>
// void fill(int* arr, int n, int val) {
//     for (int i = 0; i < n; i++) arr[i] = val;
// }
// void dump(int* arr, int n) {
//     for (int i = 0; i < n; i++) printf("%d ", arr[i]);
//     printf("\n");
// }
// int main(void) {
//     int n = 5;
//     int* a = malloc(n * sizeof(int));
//     fill(a, n, 9);
//     dump(a, n);
//     free(a);
//     return 0;
// }

#include<cstdio>
#include<vector>

void fill(std::vector<int> & a,int val){
    for(int &i : a){
        i = val;
        //这里要怎么初始化呢？我不会了
    }
}
void dump(const std::vector<int>& a){
    for(int i : a){
        std::printf("%d ",i);
    }
    printf("\n");

}

int main(){
    // int n = 5;
    std::vector<int> a(5);
    fill(a,9);
    dump(a);
    return 0;
}