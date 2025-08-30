#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define VECTOR_SIZE 200000000
#define N 4

void heavy_work(double *vector, int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        vector[i] = sin(vector[i]) * cos(vector[i]) + sqrt(vector[i]);
    }
}

int main()
{
    double *vector = (double *)malloc(VECTOR_SIZE * sizeof(double));
    for (int i = 0; i < VECTOR_SIZE; i++)
        vector[i] = (double)i;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < N; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return 1;
        }
        else if (pid == 0)
        {
            heavy_work(vector, 0, VECTOR_SIZE);
            exit(0);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Versao paralela executou em %f segundos\n", time_spent);

    free(vector);
    return 0;
}
