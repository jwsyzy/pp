#include <iostream>
#include <cstring>
#include </home/jwsyzy/software/lapack-3.10.1/CBLAS/include/cblas.h>
#include </home/jwsyzy/software/lapack-3.10.1/LAPACKE/include/lapacke.h>

using namespace std;

int main() {
        char jobz='V',uplo='U';
        int lda=3,n=3,info=8,lwork=9;
//      lapack_int lda=3,n=3,info=8;

        int i;
        double w[3],work[3];

        double a[9] = {
        3,2,4,
        2,0,2,
        4,2,3
        };
        // info=LAPACKE_dsyev_work(LAPACK_ROW_MAJOR,jobz,uplo,  n  ,a,  lda  , w,work,lwork);



        info=LAPACKE_dsyev(LAPACK_ROW_MAJOR,jobz,uplo,  n  ,a,  lda  , w);    
        //dsyev_( &jobz,&uplo,&n, a, &lda, w,work , &lwork, &info );
        if( info > 0 ) {
                printf( "The algorithm failed to compute eigenvalues.\n" );
                exit( 1 );
        }
        for(i=0;i<3;i++)
        {
            printf("%f\n",w[i]);
         } 
        for(i=0;i<9;i++)
        {
                printf("%f\n",a[i]);
        }

        exit( 0 );
} 