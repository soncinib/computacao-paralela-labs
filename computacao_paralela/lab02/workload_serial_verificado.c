#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define VECTOR_SIZE 200000000

void heavy_work(double *v, int a, int b)
{
    for (int i = a; i < b; ++i)
        v[i] = sin(v[i]) * cos(v[i]) + sqrt(v[i]);
}

int main()
{
    double *v = (double *)malloc(VECTOR_SIZE * sizeof(double));
    for (int i = 0; i < VECTOR_SIZE; i++)
        v[i] = (double)i;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    heavy_work(v, 0, VECTOR_SIZE);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double dt = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
    printf("Versao sequencial executou em %f segundos\n", dt);
    printf("Resultado de verificacao: vector[10] = %f\n", v[10]);

    free(v);
    return 0;
}
