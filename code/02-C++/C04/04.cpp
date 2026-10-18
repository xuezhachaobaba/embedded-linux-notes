#include<cstdio>
#include<vector>


void dump( const std::vector<int>& v){
    for(int i = 0; i < 5; i++){
        std::printf("%d ",v[i]);
    }
    std::printf("\n");

    //迭代器的写法我忘记了，我又看了课本写上的
    for(auto a = v.begin(); a != v.end(); ++a ){
        std::printf("%d ",*a);
    }
    std::printf("\n");


    for(int x : v){
        std::printf("%d ",x);
    }


    std::printf("\n");
    for(const auto& x: v){
        std::printf("%d ",x);
    }
    std::printf("\n");
}

int main(){
    std::vector<int> v = {1,2,3,4,5};
    dump(v);
    // for(int i = 0; i < 5; i++){
    //     std::printf("%d ",v[i]);
    // }
    // std::printf("\n");

    // //迭代器的写法我忘记了，我又看了课本写上的
    // for(std::vector<int>::iterator a = v.begin(); a != v.end(); ++a ){
    //     std::printf("%d ",*a);
    // }
    // std::printf("\n");
    // for(int x : v){
    //     std::printf("%d ",x);
    // }


    // std::printf("\n");
    // for(const auto& x: v){
    //     std::printf("%d ",x);
    // }
    // std::printf("\n");



    return 0;
}