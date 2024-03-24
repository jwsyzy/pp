#include <iostream>
#include<string>
#include<ctime>

int main()
{
    // std::string s1="hello";
    // std::string s2("world");
    // std::cout<<s1<<std::endl;
    // return 0;
    time_t curr_time;
    curr_time = time(NULL);
    char *tm = ctime(&curr_time); //tm指针现在指向一个包含当前时间的字符串。
    std::cout<<"Today is : "<<tm<<std::endl;
}