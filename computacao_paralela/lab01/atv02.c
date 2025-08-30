#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define N 4

int main()
{
    printf("Eu sou o pai! Meu PID e %d.\n", getpid());

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
            printf("Eu sou o filho %d, meu PID eh %d, meu pai eh %d.\n", i + 1, getpid(), getppid());
            exit(0);
        }
    }

    printf("Esperando meus filhos terminarem...\n");

    for (int i = 0; i < N; i++)
    {
        wait(NULL);
    }

    printf("Todos os filhos terminaram.\n");
    return 0;
}
