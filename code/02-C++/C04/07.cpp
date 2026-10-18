#include<cstdio>
#include<string>
#include<map>

int main(){
    const char* words[] = {"the","quick","brown","fox","the","jumps","the"};
    std::map<std::string,int > freq;
    for(const char * w: words){
        freq[w]++;
    }
    for(const auto & kv : freq){
        std::printf("%-8s%d\n",kv.first.c_str(),kv.second);
    }
    auto it = freq.find("fox");
    if(it != freq.end()){
        std::printf("fox %d\n",it->second);
    }
    return 0;
}