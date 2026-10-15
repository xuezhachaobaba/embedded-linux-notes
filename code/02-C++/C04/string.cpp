#include<cstdio>
#include<string>
int main(){
    std::string s1 = "hello";
    std::string s2 = s1 + " world";
    int n = s1.size();
    char c = s1[0];
    bool same = (s1 == "hello");

    std::string sub = s2.substr(0,5);
    size_t pos = s2.find("world");
    size_t pos2 = s1.find("he");
    std::printf("%s %d %d %zu\n",s2.c_str(),n,(int)same,pos);
    //这里pos输出的结果是6，hello 加上空格是6个字符，w应该是第七个字符，所以pos的6指的是从0开始的是吗？
    std::printf("%c %s %zu\n",c,sub.c_str(),pos2);
    //用pos2来验证，确实是从0开始的
}