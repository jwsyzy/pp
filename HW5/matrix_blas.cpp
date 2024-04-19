#include <iostream>
#include "timer.h"
#include "matrix_class.h"
#include <cblas.h>
using namespace std;

int main()
{
    //  1.matirx multiplication without cblas
    Mat_Demo A(3, 3, false, false);
    Mat_Demo B(3, 3, false);
    A.print();
    B.print();
    Mat_Demo C = A * B;
    C.print();
    C.save("C.txt");
    Mat_Demo CC("C.txt");
    
    Mat_Demo A1(100,100,false);
    Mat_Demo B1(100,100,false);
    //A1.print();
    //B1.print();
    Mat_Demo C1 = A1 * B1;
    C1.save("C1.txt");
    //C1.print();

    Mat_Demo A2(1000,1000,false);
    Mat_Demo B2(1000,1000,false);
    //A2.print();
    //B2.print();
    Mat_Demo C2 = A2 * B2;
    C2.save("C2.txt");
    //C2.print();

    //  2.matirx multiplication with cblas
    // let "/" denote matrix multiplication using cblas
    Mat_Demo D= A / B;
    D.print();
    D.save("D.txt");
    Mat_Demo D1= A1 / B1;
    D1.save("D1.txt");
    Mat_Demo D2= A2 / B2;
    D2.save("D2.txt");

    Timer::print_record();
    Timer::clear_record();

    //用于分尺寸比较的代码
    cout<<endl;
    cout<<"分尺寸比较："<<endl;
    //  1.matirx multiplication without cblas
    Mat_Demo E = A * B;
    Mat_Demo F= A / B;
    cout<<"3*3"<<endl;
    Timer::print_record();
    Timer::clear_record();

    Mat_Demo E1 = A1 * B1;
    Mat_Demo F1= A1 / B1;
    cout<<"100*100"<<endl;
    Timer::print_record();
    Timer::clear_record();

    Mat_Demo E2 = A2 * B2;
    Mat_Demo F2= A2 / B2;
    cout<<"1000*1000"<<endl;
    Timer::print_record();
    Timer::clear_record();   

    return 0;
}