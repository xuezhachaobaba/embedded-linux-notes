#include<cstdio>
#include<vector>

int main(){
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    std::printf("%d %d %d %d %d %d %d %lu\n",v[0],v[1],v[2],v[3],v[4],v[0],v.back(),v.size());
    v.pop_back();
    std::printf("%d %d %zu\n",v[0],v.back(),sizeof(std::vector<int>));
    return 0;
}