#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Input
{
public:
    //构造函数和析构函数不是很必须，会有默认的构造函数和析构函数
    // Input();
    // ~Input();
    void init(const string &filename, ofstream &ofs_out){
        ifstream ifs(filename);
        if (!ifs.is_open())
        {
            cerr << "Unable to open file " << filename << endl;
            return;
        }
        read(ifs);
        ifs.close();
        print(ofs_out);
    }

    // parameters
    string cal;     // type of calculation
    string mat_typ; // type of matrix
    int nr;         // number of rows
    int nc;         // number of columns
    int mat_prt;    // the way to print matrix

private:
    void read (ifstream &ifs){
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            string parameter, method;
            iss >> parameter >> method;

            if (!parameter.empty() && parameter[0] == '#')
            {
                continue;
            }

            parameter = toLower(parameter);
            if (parameter == "calculation")
            {
                cal = method;
            }
            else if (parameter == "matrix_type")
            {
                mat_typ = method;
            }
            else if (parameter == "nrows")
            {
                nr = stoi(method);
            }
            else if (parameter == "ncols")
            {
                nc = stoi(method);
            }
            else if (parameter == "matrix_print")
            {
                mat_prt = stoi(method);
            }
        }
    }
    string toLower(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
    void print(ofstream &ofs_out){
        ofs_out << "calculation: " << cal << endl;
        ofs_out << "matrix_type: " << mat_typ << endl;
        ofs_out << "matrix_print: " << mat_prt << endl;
        ofs_out << "nrows: " << nr << endl;
        ofs_out << "ncols: " << nc << endl;
    
    }
};

int main()
{
    Input input;
    ofstream ofs("output.txt");
    input.init("input.txt", ofs);
    return 0;
}
