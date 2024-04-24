#include <iostream>
#include <fstream>
#include "timer.h"
#include "matrix_class.h"
#include </home/jwsyzy/software/lapack-3.10.1/LAPACKE/include/lapacke.h>
#include <cblas.h>
#ifdef __MPI
#include <mpi.h>
#endif

using namespace std;

int main( int argc , char** argv )
{

    int rank, size;
    // int size=4;
#ifdef __MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif

    bool print_mpi_log = false; 
    if (size > 1) {
        print_mpi_log = true; 
    }
    string output_filename = "result";
    if (print_mpi_log) {
        output_filename += to_string(rank) + ".txt"; 
    } else {
        output_filename += "0.txt"; 
    }

    ofstream output_file(output_filename); 
    output_file << "Hello from process " << rank << " of " << size << endl;

    // std::cout << "Hello from process " << rank << " of " << size << std::endl;
    Mat_Demo G(3, 3, false, true);
    G.print();
    G.diag();

#ifdef __MPI
    Timer::save_record(output_file);
#else
    Timer::print_record();
#endif

    Timer::clear_record();


#ifdef __MPI
    MPI_Finalize();
#endif

    // Mat_Demo H(100,100,false,true);
    // H.diag();
    // //H.save("H.txt");
    // Timer::print_record();
    // Timer::clear_record();
    // Mat_Demo I(1000,1000,false,true);
    // I.diag();
    // //I.save("I.txt");
    // Timer::print_record();
    // Timer::clear_record();

    return 0;
}