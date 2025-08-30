#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

#define VECTOR_SIZE 200000000
#define NUM_PROCESSES 4

void heavy_work(double *v, int start, int end)
{
    for (int i = start; i < end; ++i)
        v[i] = sin(v[i]) * cos(v[i]) + sqrt(v[i]);
}

int main()
{
    double *v = (double *)malloc(VECTOR_SIZE * sizeof(double));
    for (int i = 0; i < VECTOR_SIZE; i++)
        v[i] = (double)i;

    int chunk = VECTOR_SIZE / NUM_PROCESSES;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        if (pid == 0)
        {
            int start = i * chunk;
            int end = (i == NUM_PROCESSES - 1) ? VECTOR_SIZE : (i + 1) * chunk;
            heavy_work(v, start, end);
            _exit(0);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++)
        wait(NULL);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double dt = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
    printf("Versao paralela (P=%d) executou em %f segundos\n", NUM_PROCESSES, dt);

    free(v);
    return 0;
}
