// #include<cstdio>
// class C{
//     public:
//         C(){
//             std::printf("默认构造\n");
//         };
//         C(const C& o){
//             std::printf("拷贝构造\n");
//         }
// };
// void take(C c){
//     std::printf("take 体内\n");
// }
// C make(void){
//     C t;
//     return t;
// }

// int main(){
//     C a;
//     C b = a;
//     take(a);
//     C c2 = make();
//     std::printf("main 结束前");
//     return 0;
// }

#include <cstdio>
class C {
public:
    C()            { std::printf("默认构造\n"); }
    C(const C& o)  { std::printf("拷贝构造\n"); }
};
void take(C c) { std::printf("take 体内\n"); }
C make(void)  { C t; return t; }    // 返回值优化可能会跳过拷贝，跑了看结果
int main() {
    C a;
    C b = a;
    take(a);
    C c2 = make();
    std::printf("main 结束前\n");
    return 0;
}