// void greet(const char* name, const char* prefix = "Hello", int times = 1)
#include <cstdio>
void greet(const char* name,const char * prefix = "hello",int times = 1){
    for(int i = 0; i < times; i++){
        printf("%s ",name);
        printf("%s\n",prefix);
    }
}

int main(void){
    greet("Tom");
    greet("Tom","Hi");
    greet("Tom","Hi",3);
    greet("Tom",,2);
    return 0;
}