#include <cstdio>
// 修正版：每处 "修N" 都是你原版出问题的地方，对照着看

class FileGuard {
        FILE* fp;
    public:
        // 修1: 文件名参数用 const char*（指向字符串的指针），不是 const char&（单个字符的别名）
        FileGuard(const char* path, const char* mode) {
            fp = fopen(path, mode);          // 修2(崩溃根因): 这里写 FILE* fp = ... 会新建一个局部变量，
                                             //     把成员 fp 遮住——成员从头到尾没被赋值，析构时 fclose(垃圾值) → 段错误
                                             //     赋值给成员：类型不写，直接 fp = fopen(...)
                                             // 修3: 用参数 path/mode，不是字面量 "filename"；读文件模式是 "r"，"a" 是追加写
            if (!fp)
                std::printf("文件打开失败: %s\n", path);
        }
        bool ok() const { return fp != nullptr; }   // 修4: bool ok() 就是个成员函数，"你开成了吗？"——外界不碰 fp 也能问
        void getfilecontent() {                     // 修5: 拼写 context（原 congtext）
            if (!ok()) return;                      //     没开成就别往下读，fgets(NULL) 会崩
            char line[256];
            while (fgets(line, sizeof(line), fp))
                std::printf("%s", line);
        }
        ~FileGuard() {
            if (fp != nullptr) {
                fclose(fp);
                std::printf("[FileGuard] fclose 已执行\n");   // 这行打印 = "关了"的证据
            }
        }
};

int main() {
    // 修6: 字符串字面量给 const char*（char* 收字面量 -Wall 会警告）
    const char* filename = "/home/zhuchao/project/02_teach/code/02-C++/C05/zhuchao.txt";
    FileGuard a(filename, "r");
    a.getfilecontent();

    // 【你自己做】把下面两行解开再跑：提前 return，fclose 那行照样打印——这就是 RAII 兜底的证据
    // std::printf("--- 读一半提前撤退 ---\n");
    // return 0;

    return 0;
}
