
#include <iostream>
#ifdef __MPI
#include <mpi.h>
#endif

using namespace std;

int main(int argc, char **argv){


    int rank,size;
    //int size=4;
#ifdef __MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif
    cout << "Hello from process " << rank << " of " << size << endl;
   
    
#ifdef __MPI
    MPI_Finalize();
#endif

    return 0;
}