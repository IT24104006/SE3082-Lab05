#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define STRIP_SIZE 8   /* aligned with common SIMD width (AVX = 4 doubles, AVX-512 = 8) */

int main() {
    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *C = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        A[i] = i * 0.5;
        B[i] = i * 2.0;
    }

    double tstart = omp_get_wtime();

    int num_strips = N / STRIP_SIZE;

    #pragma omp parallel for
    for (int s = 0; s < num_strips; s++) {
        int start = s * STRIP_SIZE;
        int end = start + STRIP_SIZE;

        #pragma omp simd
        for (int i = start; i < end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    /* handle any leftover elements if N is not a multiple of STRIP_SIZE */
    for (int i = num_strips * STRIP_SIZE; i < N; i++) {
        C[i] = A[i] * B[i];
    }

    double tstop = omp_get_wtime();

    printf("Sample check: C[100] = %f (expected %f)\n", C[100], A[100] * B[100]);
    printf("Sample check: C[999999] = %f (expected %f)\n", C[999999], A[999999] * B[999999]);
    printf("Strip size = %d, Number of strips = %d\n", STRIP_SIZE, num_strips);
    printf("Time = %.4f sec\n", tstop - tstart);

    free(A); free(B); free(C);
    return 0;
}
