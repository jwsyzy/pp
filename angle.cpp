#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
int main()
{
    ifstream ifs("input.txt");
    char ch;
    int line[100];
    int i = 0;
    while (ifs.get(ch))
    {
        if (ch == ' ')
            continue;
        else
        {
            line[i] = ch - '0';
            i++;
        }
    }

    return 0;
}