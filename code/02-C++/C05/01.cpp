#include<cstdio>

struct Guard{
    Guard(const char * n ):name(n){
        std::printf("%s : enter\n",name);
    }
    ~Guard(){
        std::printf("%s : leave\n",name);
    }
    const char *name;
};

int main(){
    Guard a("a");
    {
        Guard b("b");
    }
    Guard c("c");
    return 0;
}

// a : enter
// b : enter
// b : leave
// c : enter
// c : leave
// a : leave