#include <iostream>
#include <cstring>
#include </home/jwsyzy/software/lapack-3.10.1/CBLAS/include/cblas.h>

using namespace std;
int main()
{
        int m = 3;
        int n = 4;
        int k = 2;
        double *a = new double[m * k]();
        double *b = new double[k * n]();
        double *c = new double[m * n]();
        a[0]=2;
        a[3]=3;
        b[0]=4;
        b[5]=5;
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, a, k, b, n, 1.0, c, n);
        for (int i = 0; i < m; i++)
        {
                for (int j = 0; j < n; j++)
                {
                        cout << c[i * n + j] << " ";
                }
                cout << endl;
        }
}