#include<cstdio>
#include<string>

int main(){
    std::string s1 = "embedded";
    std::string s2 = s1+" Linux";
    std::printf("len=%zu\n",s2.size());
    std::printf("sub=%s\n",s2.substr(0,8).c_str());
    std::printf("%d\n",s1 == "embedded");
    size_t pos = s2.find("Linux");
    std::printf("pos=%zu nofind=%zu\n",pos , s2.find("xxxx"));
    return 0;
}