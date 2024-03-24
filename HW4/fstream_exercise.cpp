#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
int main()
{
    // 1.读取文件
    ifstream inputFile("input.txt");
    // 2.检查文件是否打开
    if (!inputFile.is_open())
    {
        cerr << "Unable to open file: "<< "input.txt" << endl;
        return 1;
    }
    // // 3.逐行读取
    // string line;
    // while (getline(inputFile, line))
    // {
    //     cout << line << endl;
    // }
    // 4.逐字读取
    // string word;
    // while (inputFile >> word)
    // {
    //     cout << word << endl;
    // }
    // // 5.逐字符读取
    // char ch;
    // while (inputFile.get(ch))
    // {
    //     cout << ch;
    // }
    // cout << endl;

    // 6、设定读入位置
    inputFile.seekg(0, ios::end); // 定位到文件末尾
    inputFile.seekg(0, ios::beg); // 定位回文件开头

    // 7、关闭文件
    // inputFile.close();

    // 8.读取输入流中文件指针的位置
    // get length of file:
    // inputFile.seekg(0, inputFile.end);
    // int length = inputFile.tellg();
    // cout << "Length of file: " << length << " characters." << endl;

    // // 9.从特定位置读取
    // inputFile.seekg(10); // 定位到文件的第11个字节位置
    // char buffer[10];
    // inputFile.read(buffer, 10); // 从当前位置读取10个字节到缓冲区
    //10.忽略

    // 读取文件中的第一行，忽略其中的前两个字符
    inputFile.ignore(2);
    string line;
    getline(inputFile, line);
    cout << line << endl;

    inputFile.ignore(100, ' '); // 忽略100个字符，直到遇到空格
    getline(inputFile, line);
    cout << line << endl;

    return 0;
}
