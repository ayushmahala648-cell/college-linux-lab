// dinning philosopher problem

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];

sem_t mutex;
sem_t S[N];

void test(int i)
{
    if (state[i] == HUNGRY &&
        state[(i + N - 1) % N] != EATING &&
        state[(i + 1) % N] != EATING)
    {
        state[i] = EATING;
        printf("Philosopher %d is eating\n", i + 1);
        sem_post(&S[i]);
    }
}

void take_forks(int i)
{
    sem_wait(&mutex);

    state[i] = HUNGRY;
    printf("Philosopher %d is hungry\n", i + 1);

    test(i);

    sem_post(&mutex);
    sem_wait(&S[i]);
}

void put_forks(int i)
{
    sem_wait(&mutex);

    state[i] = THINKING;
    printf("Philosopher %d puts down forks\n", i + 1);

    test((i + N - 1) % N);
    test((i + 1) % N);

    sem_post(&mutex);
}

void *philosopher(void *arg)
{
    int i = *(int *)arg;

    printf("Philosopher %d is thinking\n", i + 1);
    sleep(1);

    take_forks(i);
    sleep(1);

    put_forks(i);

    return NULL;
}

int main()
{
    pthread_t tid[N];
    int id[N];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++)
    {
        state[i] = THINKING;
        sem_init(&S[i], 0, 0);
    }

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    sem_destroy(&mutex);

    for (int i = 0; i < N; i++)
        sem_destroy(&S[i]);

    return 0;
}