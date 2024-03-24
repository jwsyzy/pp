#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

#define PI 3.141592653589793
int main()
{

    // // 1.setprecision(n) 设置浮点数有效位
    // cout << setprecision(1) << PI << endl;
    // cout << setprecision(2) << PI << endl;
    // cout << setprecision(10) << PI << endl;
    // cout << setprecision(0) << PI << endl;   // 至少保留一位
    // cout << setprecision(1.9) << PI << endl; // floor(1.9)=1
    // cout << setprecision(-1) << PI << endl;  // 无效，输出默认6位

    // // 2.setbase(n) 进制转换，只有16,10,8三种进制
    // cout << setbase(16) << 1234 << endl;
    // cout << setbase(10) << 1234 << endl;
    // cout << setbase(8) << 1234 << endl;

    // // 3.fixed + setprecision(n) 四舍六入五成双,setprecision只限定小数部分的位数
    // cout << fixed << setprecision(2) << PI << endl;
    // cout << fixed << setprecision(3) << PI << endl;

    // // 4.setfill(c) 和setw(n) 设置字符填充
    // cout << setfill('%') << setw(20) << PI << endl;
    // cout << setfill('%') << setw(20) << left << PI << endl;
    // cout << setfill('%') << setw(2) << PI << endl; // 超出宽度不填充

    // // 5.设置输出宽度,在设置了 setfill('%') 后，填充字符会一直保持为 '%' 直到下次更改
    // cout << setw(10) << "Hello" << endl;          // 输出 "     Hello"
    // cout << setw(10) << right << "Hello" << endl; // 输出 "Hello     "

    // // 6.scientific 科学计数法
    // cout << scientific << PI << endl; // 小数部分默认保留3位
    // cout << scientific << 53224343.45465734 << endl;

    // // 7.对齐
    // cout << setiosflags(ios::left) << setw(10) << "Hello" << endl;
    // cout << setiosflags(ios::left) << setw(10) << "hi" << endl;

    // // 8.格式化当前日期和时间
    // time_t now = time(0);
    // cout << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") << endl;

    // 9.输出正数时显示+
    cout << setiosflags(ios::showpos) << 45 << endl;

    // 10.强制显示小数点。即使小数部分是0
    double num = 123.00;
    cout << noshowpos << setiosflags(ios::showpoint) << num << endl;
    // 除了setw()是一次有效的，其余的均是一直有效，直至被修改；这样使用完毕必须做相应的恢复操作，对用户来说 并不方便。
}