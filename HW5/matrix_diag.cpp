#include <iostream>
#include "timer.h"
#include "matrix_class.h"
#include </home/jwsyzy/software/lapack-3.10.1/LAPACKE/include/lapacke.h>
#include </home/jwsyzy/software/lapack-3.10.1/CBLAS/include/cblas.h>
using namespace std;

int main(){

    Mat_Demo G("symmetry.txt");
    G.print();
    G.diag();
    G.save("G.txt");
    Timer::print_record();
    Timer::clear_record();  

    Mat_Demo H(100,100,false,true);
    H.diag();
    H.save("H.txt");
    Timer::print_record();
    Timer::clear_record();  

    Mat_Demo I(1000,1000,false,true);
    I.diag();
    I.save("I.txt");
    Timer::print_record(); 
    Timer::clear_record();

    return 0;
    
}