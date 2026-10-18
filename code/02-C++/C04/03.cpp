#include<cstdio>
#include<vector>

int main(){
    std::vector<int> v;
    for(int i = 0; i < 33; i++){
        v.push_back(i);
        std::printf("size = %2zu    capacity = %2zu\n",v.size(), v.capacity());
    }
    return 0;
}