#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;
pthread_mutex_t mutex;

int read_count = 0;
int shared_data = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);

    read_count++;

    if (read_count == 1)
        sem_wait(&rw_mutex);

    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading data: %d\n", id, shared_data);
    sleep(1);

    pthread_mutex_lock(&mutex);

    read_count--;

    if (read_count == 0)
        sem_post(&rw_mutex);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&rw_mutex);

    shared_data += 10;

    printf("Writer %d is writing data: %d\n", id, shared_data);
    sleep(1);

    sem_post(&rw_mutex);

    return NULL;
}

int main()
{
    pthread_t readers[5], writers[3];

    int reader_id[5] = {1, 2, 3, 4, 5};
    int writer_id[3] = {1, 2, 3};

    pthread_mutex_init(&mutex, NULL);
    sem_init(&rw_mutex, 0, 1);

    // Create reader and writer threads
    pthread_create(&readers[0], NULL, reader, &reader_id[0]);
    pthread_create(&writers[0], NULL, writer, &writer_id[0]);

    pthread_create(&readers[1], NULL, reader, &reader_id[1]);
    pthread_create(&readers[2], NULL, reader, &reader_id[2]);

    pthread_create(&writers[1], NULL, writer, &writer_id[1]);

    pthread_create(&readers[3], NULL, reader, &reader_id[3]);
    pthread_create(&readers[4], NULL, reader, &reader_id[4]);

    pthread_create(&writers[2], NULL, writer, &writer_id[2]);

    // Wait for all readers
    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);

    // Wait for all writers
    for (int i = 0; i < 3; i++)
        pthread_join(writers[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}