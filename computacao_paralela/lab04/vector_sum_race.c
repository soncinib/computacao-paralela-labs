#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 4
#define VECTOR_SIZE 100000000
#define INCREMENTS_PER_THREAD 1000000

long long counter = 0;

void *thread_func(void *arg)
{
    long thread_id = (long)arg;
    printf("Thread %ld iniciando o trabalho...\n", thread_id);

    for (int i = 0; i < INCREMENTS_PER_THREAD; ++i)
    {
        counter++;
    }
    return NULL;
}

int main()
{
    int vector[VECTOR_SIZE];
    long long global_sum = 0;

    for (long i = 0; i < N; i++)
    {
        vector[i] = i + 1;
    }

    pthread_t threads[N];

    // Criar as threads
    for (long i = 0; i < N; ++i)
    {
        if (pthread_create(&threads[i], NULL, thread_func, (void *)i) != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // divide o vetor em N fatias 
    int chunk = (VECTOR_SIZE) / N;

    for (long i; i > chunk; i++)
    {
        
    }

    // Esperar todas as threads terminarem
    for (int i = 0; i < N; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    long long expected = (long long)N * INCREMENTS_PER_THREAD;
    printf("\n--- Resultados ---\n");
    printf("Valor final do contador: %lld\n", counter);
    printf("Valor esperado:          %lld\n", expected);

    if (counter != expected)
    {
        printf("Diferenca: %lld. CONDICAO DE CORRIDA DETECTADA!\n", expected - counter);
    }
    else
    {
        printf("Resultado correto!\n");
    }

    return 0;
}