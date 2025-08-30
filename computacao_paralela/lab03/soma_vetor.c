#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define N 4
#define NUM_PROCESSES 4
#define VECTOR_SIZE 1000

int main()
{
    int vector[VECTOR_SIZE];

    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        vector[i] = i + 1;
    }

    int pipes[NUM_PROCESSES][2];

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Processo Filho
            close(pipes[i][0]);

            int chunk = (VECTOR_SIZE + NUM_PROCESSES - 1) / NUM_PROCESSES;
            int start = i * chunk;
            int end = start + chunk;

            if (end > VECTOR_SIZE)
            {
                end = VECTOR_SIZE;
            }

            double local_sum = 0;

            for (int j = start; j < end; j++)
            {
                local_sum += vector[j];
            }

            write(pipes[i][1], &local_sum, sizeof(double));
            close(pipes[i][1]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            // Processo Pai
            close(pipes[i][1]);
        }
    }

    // Processo Pai
    double total_sum = 0;

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        double partial_sum = 0;

        read(pipes[i][0], &partial_sum, sizeof(double));
        close(pipes[i][0]);

        total_sum += partial_sum;
    }

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        wait(NULL);
    }

    printf("Soma do vetor: %f\n", total_sum);
    return 0;
}
