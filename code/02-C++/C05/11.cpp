#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include<algorithm>

struct Student{
    std::string name;
    int score;
};

int main(){
    std::vector<Student> stu = {{"tom",78},{"jerry",92},{"Ann",85},{"Bob",92}};
    std::sort(stu.begin(),stu.end(),[](const Student & a, const Student &b){
        if(a.score>b.score)
            return true;
        else if(a.score<b.score)
            return false;
        else 
            return a.name<b.name;
    });
    // std::sort(stu.begin(),stu.end(),[](const Student & a, const Student &b){
    //     return a.score > b.score || (a.score == b.score && a.name < b.name);
    // });
    for(const Student & a : stu){
        std::printf("%s:%d\n",a.name.c_str(),a.score);
    }

    return 0;

}