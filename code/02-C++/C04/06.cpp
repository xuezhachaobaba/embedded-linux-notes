#include<cstdio>
#include<string>
#include<map>
int main(){
    std::map<std::string, int> m;
    m["apple"] = 3;
    std::printf("%zu\n", m.size());
    if (m["pear"] == 0) std::printf("pear 是 0\n");
    std::printf("%zu\n", m.size());
    return 0;
}
