#include <iostream>
#include "timer.h"
#include "matrix_class.h"
#include <cblas.h>
#include </home/jwsyzy/software/lapack-3.10.1/LAPACKE/include/lapacke.h>
#include <random>
#include <fstream>
using namespace std;
Mat_Demo::Mat_Demo()
{
    nrows = 0;
    ncols = 0;
    d = nullptr;
}
Mat_Demo::Mat_Demo(const int &nrows_in,
                   const int &ncols_in,
                   const bool flag_zero,
                   const bool symmetry)
{

    nrows = nrows_in;
    ncols = ncols_in;
    d = new double[nrows * ncols];

    if (symmetry)
    {
        for (int i = 0; i < nrows; i++)
        {
            for (int j = 0; j < ncols; j++)
            {
                if (i <= j)
                {
                    d[i * ncols + j] = (rand() % (9 - 0 + 1));
                }
                else
                {
                    d[i * ncols + j] = d[j * ncols + i];
                }
            }
        }
    }
    else
    {
        if (flag_zero)
        {
            zero();
        }
        else
        {
            for (int i = 0; i < nrows * ncols; i++)
            {
                d[i] = (rand() % (9 - 0 + 1));
            }
        }
    }
}
Mat_Demo::Mat_Demo(const int &nrows_in,
                   const int &ncols_in,
                   double *data)
{
    nrows = nrows_in;
    ncols = ncols_in;
    d = new double[nrows * ncols];
    for (int i = 0; i < nrows * ncols; i++)
    {
        d[i] = data[i];
    }
}
Mat_Demo::~Mat_Demo()
{
    delete[] d;
}
int Mat_Demo::nr() const
{
    return nrows;
}
int Mat_Demo::nc() const
{
    return ncols;
}
double &Mat_Demo::operator()(int &i, int &j)
{
    return d[i * ncols + j];
}

double Mat_Demo::max_element() const
{
    double max = d[0];
    for (int i = 0; i < nrows * ncols; i++)
    {
        if (d[i] > max)
        {
            max = d[i];
        }
    }
    return max;
}
double Mat_Demo::min_element() const
{
    double min = d[0];
    for (int i = 0; i < nrows * ncols; i++)
    {
        if (d[i] < min)
        {
            min = d[i];
        }
    }
    return min;
}
double* Mat_Demo::get_d() const
{
    return d;
}
void Mat_Demo::zero()
{
    Timer::tick("Mat_Demo", "zero");
    for (int i = 0; i < nrows * ncols; i++)
    {
        d[i] = 0;
    }
    Timer::tick("Mat_Demo", "zero");
}
void Mat_Demo::zero(const int &nrows_in, const int &ncols_in)
{
    nrows = nrows_in;
    ncols = ncols_in;
    delete[] d;
    d = new double[nrows * ncols];
    zero();
}
Mat_Demo &Mat_Demo::operator=(const Mat_Demo &other)
{
    Timer::tick("Mat_Demo", "operator=");
    if (this == &other)
    {
        Timer::tick("Mat_Demo", "operator=");
        return *this;
    }
    nrows = other.nrows;
    ncols = other.ncols;
    delete[] d;
    d = new double[nrows * ncols];
    for (int i = 0; i < nrows * ncols; i++)
    {
        d[i] = other.d[i];
    }
    Timer::tick("Mat_Demo", "operator=");
    return *this;
}
Mat_Demo Mat_Demo::operator+(const Mat_Demo &other) const
{
    Timer::tick("Mat_Demo", "operator+");
    Mat_Demo result(nrows, ncols, false);
    for (int i = 0; i < nrows * ncols; i++)
    {
        result.d[i] = d[i] + other.d[i];
    }
    Timer::tick("Mat_Demo", "operator+");
    return result;
}
Mat_Demo Mat_Demo::operator-(const Mat_Demo &other) const
{
    Timer::tick("Mat_Demo", "operator-");
    Mat_Demo result(nrows, ncols, false);
    for (int i = 0; i < nrows * ncols; i++)
    {
        result.d[i] = d[i] - other.d[i];
    }
    Timer::tick("Mat_Demo", "operator-");
    return result;
}

Mat_Demo Mat_Demo::operator*(const Mat_Demo &other) const
{
    Timer::tick("Mat_Demo", "operator*");
    Mat_Demo result(nrows, other.ncols, true);
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < other.ncols; j++)
        {
            for (int k = 0; k < ncols; k++)
            {
                result.d[i * result.ncols + j] += d[i * ncols + k] * other.d[k * other.ncols + j];
            }
        }
    }
    Timer::tick("Mat_Demo", "operator*");
    return result;
}

Mat_Demo Mat_Demo::operator/(const Mat_Demo &other)
{
    Timer::tick("Mat_Demo", "operator/");
    Mat_Demo result(nrows, other.ncols, true);
    //result=d*other.d
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, nrows, other.ncols, ncols, 1.0, d, ncols, other.d, other.ncols, 0.0, result.d, other.ncols);
    Timer::tick("Mat_Demo", "operator/");
    return result;
}

Mat_Demo Mat_Demo::row_spilt(const int &row_start, const int &row_end) const
{
    int row_num = row_end - row_start+1;
    Mat_Demo result(row_num, ncols, true);
    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            result.d[i * ncols + j] = d[(row_start + i) * ncols + j];
        }
    }
    return result;
}

void Mat_Demo::print() const
{
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            cout << d[i * ncols + j] << " ";
        }
        cout << endl;
    }
    cout << "----------------" << endl;
}

void Mat_Demo::save(const std::string &filename) const
{
    Timer::tick("Mat_Demo", "save");
    ofstream file(filename);
    file << nrows << " " << ncols << endl;
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            file << d[i * ncols + j] << " ";
        }
        file << endl;
    }
    file.close();
    Timer::tick("Mat_Demo", "save");
}

Mat_Demo::Mat_Demo(const std::string &filename)
{
    Timer::tick("Mat_Demo", "load");
    ifstream file(filename);
    file >> nrows >> ncols;
    d = new double[nrows * ncols];
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            file >> d[i * ncols + j];
        }
    }
    file.close();
    Timer::tick("Mat_Demo", "load");
}
void Mat_Demo::diag() const
{
    Timer::tick("Mat_Demo", "diag");
    int n=nrows;
    int lda=n;
    double w[n];
    int info=LAPACKE_dsyev(LAPACK_ROW_MAJOR,'V','U',n,d,lda,w);
    if (info!=0)
    {
        cout<<"error"<<endl;
    }
    cout<<"Eigenvalues:"<<endl;
    for (int i=0;i<n;++i)
    {
        cout<<w[i]<<" ";
    }
    cout<<endl;
    // cout<<"Eigenvectors:"<<endl;
    // for (int i=0;i<n;++i)
    // {
    //     for (int j=0;j<n;++j)
    //     {
    //         cout<<d[i*n+j]<<" ";
    //     }
    //     cout<<endl;
    // }

    Timer::tick("Mat_Demo", "diag");

}

Complex_Mat_Demo::Complex_Mat_Demo()
{
    real = Mat_Demo();
    imag = Mat_Demo();
}
Complex_Mat_Demo::Complex_Mat_Demo(const int &nrows_in,
                                   const int &ncols_in,
                                   const bool flag_zero,
                                   const bool symmetry)
{
    real = Mat_Demo(nrows_in, ncols_in, flag_zero, symmetry);
    imag = Mat_Demo(nrows_in, ncols_in, flag_zero, symmetry);
}
// int main()
// {
//     // Mat_Demo M(3,3);
//     // Mat_Demo N(3,3);
//     // for (int i=0;i<M.nr();++i){
//     //     for (int j=0;j<M.nc();++j){
//     //         M(i,j)=i+j;
//     //         N(i,j)=i-j;
//     //     }
//     // }
//     // cout<<"number of M rows:"<<M.nr()<<endl;
//     // cout<<"number of M cols:"<<M.nc()<<endl;
//     // cout<<"max element of M:"<<M.max_element()<<endl;
//     // cout<<"min element of M:"<<M.min_element()<<endl;
//     // cout<<endl;
//     // M.print();
//     // N.print();
//     // N.zero();
//     // N.print();
//     // N=M;
//     // Mat_Demo P=M+N;
//     // P.print();
//     // Mat_Demo Q=M-N;
//     // Q.print();

//     // Mat_Demo R=P+Q;
//     // R.print();

//     Mat_Demo A(3, 3, false);
//     Mat_Demo B(3, 3, false);
//     A.print();
//     B.print();
//     Mat_Demo C = A * B;
//     C.print();

//     Mat_Demo A1(100,100,false);
//     Mat_Demo B1(100,100,false);
//     //A1.print();
//     //B1.print();
//     Mat_Demo C1 = A1 * B1;
//     //C1.print();

//     Mat_Demo A2(1000,1000,false);
//     Mat_Demo B2(1000,1000,false);
//     //A2.print();
//     //B2.print();
//     Mat_Demo C2 = A2 * B2;
//     //C2.print();

//     Timer::print_record();
//     return 0;
// }