#include <iostream>
#include <fstream>
#include "timer.h"
#include "matrix_class.h"
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    const int m = 5;
    const int n = 3;
    int rank, size;
    double *rank_row_start = new double[4];
    bool start = false;
    double *result = new double[m * n];
    int max_rank = 3;
    if (m<4){
        max_rank = m-1;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (rank == 0)
    {

        Mat_Demo A(m, n, false, false);
        Mat_Demo B(m, n, false, false);
        //we can also use ''Mat_Demo A(const std::string &filename)'' to load a matrix from a file
        A.print();
        B.print();
        int left_row = m;

        for (int i = size-1; i >= 0; i--)
        {
            int row = left_row / (i+1);
            if (row == 0)
            {
                rank_row_start[i] = -1;
                continue;
            }
            else
            {
                rank_row_start[i] = m - left_row;
                int row_start = m - left_row;
                int row_end = m - left_row + row;
                Mat_Demo C = A.row_spilt(m - left_row, m - left_row + row);
                double *c_data = C.get_d();
                Mat_Demo D = B.row_spilt(m - left_row, m - left_row + row);
                double *d_data = D.get_d();
                if (i == 0)
                {
                    Mat_Demo E = C + D;
                    double*e_data = E.get_d();
                    for (int j = 0; j < row; j++)
                    {
                        for (int k = 0; k < n; k++)
                        {
                            result[(row_start + j) * n + k] = e_data[j * n + k];
                        }
                    }
                }

                else
                {
                    MPI_Send(&row, 1, MPI_INT, i, i * 1000 + 1, MPI_COMM_WORLD);
                    // MPI_Send(&n, 1, MPI_INT, i, i*1000+2, MPI_COMM_WORLD);
                    MPI_Send(c_data, row * n, MPI_DOUBLE, i, i * 1000 + 3, MPI_COMM_WORLD);
                  
                    MPI_Send(d_data, row * n, MPI_DOUBLE, i, i * 1000 + 4, MPI_COMM_WORLD);
                }
                left_row -= row;
            }
        }
            
        for (int i = 0; i < 4; ++i) {
            cout << "rank_row_start[" << i << "] = " << rank_row_start[i] << endl;
        }

        
        for (int i = 1; i < size; i++)
        {
            int row_start = rank_row_start[i];
            if (row_start == -1)
            {
                continue;
            }
            else
            {
                int row= rank_row_start[i - 1] - rank_row_start[i];
                

                double *e_data = new double[row * n];
                MPI_Recv(e_data, row * n, MPI_DOUBLE, i, i * 1000, MPI_COMM_WORLD, &status);
                cout<<"process0 receive"<<rank<<endl;
                for (int j = 0; j < row; j++)
                {
                    for (int k = 0; k < n; k++)
                    {
                        result[(row_start + j) * n + k] = e_data[j * n + k];
                    }
                }
                delete[] e_data;
            }
        }
        Mat_Demo E(m, n, result);
        string output_filename = "result0.txt";
        E.save(output_filename);
        
    }
    else if(rank>max_rank){
        cout<<"rank: "<<rank<<" no work"<<endl;
    }
    else 
    {
        
        int row;
        MPI_Recv(&row, 1, MPI_INT, 0, rank * 1000 + 1, MPI_COMM_WORLD, &status);
        int col = n;
        cout << "rank: " << rank << " receive: " << row << endl;
        double *c_data = new double[row * col];
        MPI_Recv(c_data, row * col, MPI_DOUBLE, 0, rank * 1000 + 3, MPI_COMM_WORLD, &status);
        double *d_data = new double[row * col];
        MPI_Recv(d_data, row * col, MPI_DOUBLE, 0, rank * 1000 + 4, MPI_COMM_WORLD, &status);
        cout<<"process "<<rank<<" receive"<<endl;
        double *e_data = new double[row * col];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                e_data[i * col + j] = c_data[i * col + j] + d_data[i * col + j];
            }
        }
        MPI_Send(e_data, row * col, MPI_DOUBLE, 0, rank * 1000, MPI_COMM_WORLD);
        cout<<"process "<<rank<<" send"<<endl;
        delete[] e_data;
        delete[] c_data;
        delete[] d_data;
    }
    
    // else
    // {
    //     cout << "rank: " << rank << " receive: " << -1 << endl;
    // }

    MPI_Finalize();

    return 0;
}