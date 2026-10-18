#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};
    int* p = &v[0];
    v.push_back(4);
    std::printf("%d\n", *p);
    return 0;
}