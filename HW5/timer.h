#ifndef __TIMER__
#define __TIMER__
#include <string.h>
#include <iostream>
#include<iomanip>
#include <vector>
using namespace std;
class Record
    {
    public:
    std::string class_name;
    std::string function_name;
    int calls=0;
    double total_time=0;
    bool running_flag=false;
    double start_time=0;
    double end_time=0;
    Record(const std::string& class_name,const std::string& function_name)
    {
        this->class_name=class_name;
        this->function_name=function_name;
    };
    };
class Timer
{
    public:
    static vector<Record> R;
    static void tick(const std::string& class_name,const std::string& function_name);
    static void print_record();
    static void clear_record();
};
#endif