#include<cstdio>
#include<vector>

int main(){
    std::vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    std::printf("sizeof=%zu\n",v.size());
    std::printf("%d %d\n",v[0], v.back());
    v.pop_back();
    //vector是不是像栈一样，只能从尾进、从尾出呢？有没有push_head这种的方法？

    std::vector<int> a(5,0);
    //这里（5，0）可以直接这么创建，那么（5，1）是否也能这么创建呢？
    std::vector<int> b = {1,2,3};

    int *p = &b[0];
    // b.push_back(4);
    // std::printf("%d\n",*p);
//     ./vector 
// sizeof=3
// 3 4
// =================================================================
// ==354227==ERROR: AddressSanitizer: heap-use-after-free on address 0x70ec043e0070 at pc 0x5d84cffb69b2 bp 0x7ffcab157250 sp 0x7ffcab157240
    return 0;
}