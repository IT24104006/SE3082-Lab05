#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main() {
    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *C = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        A[i] = i * 0.5;
        B[i] = i * 2.0;
    }

    double tstart = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        C[i] = A[i] * B[i];
    }

    double tstop = omp_get_wtime();

    printf("Sample check: C[100] = %f (expected %f)\n", C[100], A[100] * B[100]);
    printf("Time = %.4f sec\n", tstop - tstart);

    free(A); free(B); free(C);
    return 0;
}
