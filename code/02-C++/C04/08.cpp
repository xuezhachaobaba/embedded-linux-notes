#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include <algorithm>
struct Student{
    std::string name;
    int score;
};

bool bycmp(const Student & a, const Student & b)
{
    if(a.score>b.score){
        return true;
    }else if (a.score < b.score)
    {
        return false;
    }else{
        return (a.name<b.name);
    }
}

// {
//     return a.score>=b.score;
// }

int main(){
    std::vector<Student>  student = {{"Tom",78},{"Jerry",92},{"Ann",85},{"Bob",92}};
    std::sort(student.begin(),student.end(),bycmp);
    for(const Student & a : student){
        std::printf("%s,%d\n",a.name.c_str(),a.score);
    }
    return 0;
}