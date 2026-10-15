#include<cstdio>
#include<string>
#include<map>

int main(){
    const char* words[] = {"the","quick","brown","fox","the","jumps","the"};
    std::map<std::string,int > freq;
    for(const char * w: words){
        freq[w]++;
        //[]不检查边界，但是性能机智，w自己有边界，只需要给定w就好，不会出错
    }
    for(const auto & kv : freq){
        std::printf("%-8s%d\n",kv.first.c_str(),kv.second);
    }
    return 0;
}

//预测，输入5行，顺序是 
// brown 1
// fox 1
// jumps 1
// quick 1
// the 3 
//实际运行和预测一致
// ./total
// brown   1
// fox     1
// jumps   1
// quick   1
// the     3
