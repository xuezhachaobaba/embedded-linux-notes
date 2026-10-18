#include<cstdio>
#include<vector>
#include <stdexcept> 

int main(){
    std::vector<int> v = {1, 2, 3};
    // std::printf("A: %d\n", v[3]);
    try {
        std::printf("B: %d\n", v.at(3));
    } catch (const std::out_of_range& e) {
        std::printf("C: %s\n", e.what());
    }
}