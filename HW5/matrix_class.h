#ifndef __MATRIX__
#define __MATRIX__
#include <string.h>
#include <iostream>
#include<iomanip>
#include <vector>
using namespace std;
class Mat_Demo
{
public:
    int nr(void) const; // 常量成员函数
    int nc(void) const;

    Mat_Demo();
    // 通过行数列数初始化矩阵
    Mat_Demo(const int &nrows_in,
             const int &ncols_in,
             const bool flag_zero = true,
             const bool symmetry=false);

    // 从文件中读取矩阵
    Mat_Demo(const std::string &filename);

    ~Mat_Demo();
    // 获得矩阵元素
    double &operator()(int &i, int &j);
    double max_element() const;
    double min_element() const;
    // 将矩阵元置为0
    void zero();
    // 根据行数列数置矩阵元素为0
    void zero(const int &nrows_in, const int &ncols_in);
    // 重载赋值运算符
    Mat_Demo &operator=(const Mat_Demo &other);
    // 重载加法运算符:结尾有const：在函数内部，不会修改当前对象和other的状态
    Mat_Demo operator+(const Mat_Demo &other) const;
    // 重载减法运算符
    Mat_Demo operator-(const Mat_Demo &other) const;
    // 重载乘法运算符
    Mat_Demo operator*(const Mat_Demo &other) const;
    //spilt
    Mat_Demo row_spilt(const int &row_start, const int &row_end) const;
    void print() const;
    void save (const std::string &filename) const;
    // 重载乘法运算符with blas
    Mat_Demo operator/(const Mat_Demo &other);
    //对角化
    void diag() const;

private:
    int nrows = 0;       // 行数
    int ncols = 0;       // 列数
    double *d = nullptr; // 存矩阵元
};
#endif