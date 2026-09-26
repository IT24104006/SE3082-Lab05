#include <stdio.h>
#include <omp.h>

int fib(int n) {
    int i, j;
    if (n < 2)
        return n;
    else {
        i = fib(n - 1);
        j = fib(n - 2);
        return i + j;
    }
}

int main() {
    int n = 35;
    double tstart = omp_get_wtime();
    int result = fib(n);
    double tstop = omp_get_wtime();

    printf("Serial fib(%d) = %d\n", n, result);
    printf("Time = %.4f sec\n", tstop - tstart);
    return 0;
}
