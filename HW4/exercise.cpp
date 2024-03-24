#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Matrixhandler
{
private:
    // 用映射表存储，类似python中的字典
    unordered_map<string, string> P_M;
    // 内部函数，用于转换字符串为小写
    string toLower(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

public:
    void setkeys()
    {
        P_M["ncols"] = "";
        P_M["nrows"] = "";
        P_M["matrix_print"] = "";
        P_M["matrix_type"] = "";
        P_M["calculation"] = "";
    }

    // 读取输入文件，解析参数和方法，并存储在P_M映射表中
    void readInputFile(const string &filename)
    {
        ifstream inputFile(filename); // 打开文件

        if (!inputFile.is_open())
        {
            cerr << "Unable to open file " << filename << endl;
            // cerr 是 C++ 标准库中的标准错误输出流，cerr 的输出是不经过缓冲的，直接输出到终端。
            return;
        }

        string line;
        while (getline(inputFile, line))
        {                            // 逐行读取文件内容
            istringstream iss(line); // istringstream 将字符串解析为单词并进行后续处理。
            string parameter, method;
            iss >> parameter >> method; // 从每行提取参数名和具体方法

            // 忽略注释行和空行
            if (!parameter.empty() && parameter[0] == '#')
            {
                continue;
            }

            parameter = toLower(parameter);
            for (const auto &pair : P_M)
            {
                if (parameter == pair.first)
                {
                    P_M[parameter] = method; // 将参数名和方法存储到映射表中
                    break;
                }
            }
        }

        inputFile.close(); // 关闭文件
    }

    // 打印存储的参数和对应的方法
    void printP_M()
    {
        for (const auto &pair : P_M)
        {
            cout << "Parameter: " << pair.first << ", Method: " << pair.second << endl;
        }
    }
};

int main()
{
    Matrixhandler matrix1;
    matrix1.setkeys();
    matrix1.readInputFile("input.txt");
    matrix1.printP_M();

    return 0;
}
