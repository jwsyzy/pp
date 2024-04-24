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
    double *result1 = new double[m * n];
    double *result2 = new double[m * n];
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

        Complex_Mat_Demo A(m, n, false, false);
        Complex_Mat_Demo B(m, n, false, false);
        //we can also use ''Mat_Demo A(const std::string &filename)'' to load a matrix from a file
        Mat_Demo A1=A.real;
        A1.print();
        Mat_Demo A2=A.imag;
        A2.print();
        Mat_Demo B1=B.real;
        B1.print();
        Mat_Demo B2=B.imag;
        B2.print();
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
                Mat_Demo C1 = A1.row_spilt(m - left_row, m - left_row + row);
                double *c1_data = C1.get_d();
                Mat_Demo C2 = A2.row_spilt(m - left_row, m - left_row + row);
                double *c2_data = C2.get_d();
                Mat_Demo D1 = B1.row_spilt(m - left_row, m - left_row + row);
                double *d1_data = D1.get_d();
                Mat_Demo D2 = B2.row_spilt(m - left_row, m - left_row + row);
                double *d2_data = D2.get_d();
                if (i == 0)
                {
                    Mat_Demo E1 = C1 + D1;
                    double*e1_data = E1.get_d();
                    for (int j = 0; j < row; j++)
                    {
                        for (int k = 0; k < n; k++)
                        {
                            result1[(row_start + j) * n + k] = e1_data[j * n + k];
                        }
                    }
                    Mat_Demo E2 = C2 + D2;
                    double*e2_data = E2.get_d();
                    for (int j = 0; j < row; j++)
                    {
                        for (int k = 0; k < n; k++)
                        {
                            result2[(row_start + j) * n + k] = e2_data[j * n + k];
                        }
                    }
                }

                else
                {
                    MPI_Send(&row, 1, MPI_INT, i, i * 1000 + 1, MPI_COMM_WORLD);
                    // MPI_Send(&n, 1, MPI_INT, i, i*1000+2, MPI_COMM_WORLD);
                    MPI_Send(c1_data, row * n, MPI_DOUBLE, i, i * 1000 + 3, MPI_COMM_WORLD);
                    MPI_Send(c2_data, row * n, MPI_DOUBLE, i, i * 1000 + 5, MPI_COMM_WORLD);
                    MPI_Send(d1_data, row * n, MPI_DOUBLE, i, i * 1000 + 4, MPI_COMM_WORLD);
                    MPI_Send(d2_data, row * n, MPI_DOUBLE, i, i * 1000 + 6, MPI_COMM_WORLD);
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

                double *e1_data = new double[row * n];
                MPI_Recv(e1_data, row * n, MPI_DOUBLE, i, i * 1000+7, MPI_COMM_WORLD, &status);
                double *e2_data = new double[row * n];
                MPI_Recv(e2_data, row * n, MPI_DOUBLE, i, i * 1000+8, MPI_COMM_WORLD, &status);
                cout<<"process0 receive "<<i <<endl;
                for (int j = 0; j < row; j++)
                {
                    for (int k = 0; k < n; k++)
                    {
                        result1[(row_start + j) * n + k] = e1_data[j * n + k];
                    }
                }
                delete[] e1_data;
                for (int j = 0; j < row; j++)
                {
                    for (int k = 0; k < n; k++)
                    {
                        result2[(row_start + j) * n + k] = e2_data[j * n + k];
                    }
                }
                delete[] e2_data;
            }
        }
        Mat_Demo E1(m, n, result1);
        Mat_Demo E2(m, n, result2);
        string output_filename1 = "real0.txt";
        E1.save(output_filename1);
        string output_filename2 = "imag0.txt";
        E2.save(output_filename2);
        
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
        double *c1_data = new double[row * col];
        MPI_Recv(c1_data, row * col, MPI_DOUBLE, 0, rank * 1000 + 3, MPI_COMM_WORLD, &status);
        double *c2_data = new double[row * col];
        MPI_Recv(c2_data, row * col, MPI_DOUBLE, 0, rank * 1000 + 5, MPI_COMM_WORLD, &status);
        double *d1_data = new double[row * col];
        MPI_Recv(d1_data, row * col, MPI_DOUBLE, 0, rank * 1000 + 4, MPI_COMM_WORLD, &status);
        double *d2_data = new double[row * col];
        MPI_Recv(d2_data, row * col, MPI_DOUBLE, 0, rank * 1000 + 6, MPI_COMM_WORLD, &status);
        cout<<"process "<<rank<<" receive"<<endl;
        double *e1_data = new double[row * col];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                e1_data[i * col + j] = c1_data[i * col + j] + d1_data[i * col + j];
            }
        }
        MPI_Send(e1_data, row * col, MPI_DOUBLE, 0, rank * 1000+7, MPI_COMM_WORLD);
        double *e2_data = new double[row * col];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                e2_data[i * col + j] = c2_data[i * col + j] + d2_data[i * col + j];
            }
        }
        MPI_Send(e2_data, row * col, MPI_DOUBLE, 0, rank * 1000+8, MPI_COMM_WORLD);
        cout<<"process "<<rank<<" send"<<endl;
        delete[] e1_data;
        delete[] c1_data;
        delete[] d1_data;
        delete[] e2_data;
        delete[] c2_data;
        delete[] d2_data;
    }
    
    // else
    // {
    //     cout << "rank: " << rank << " receive: " << -1 << endl;
    // }

    MPI_Finalize();

    return 0;
}