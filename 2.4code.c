#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    key_t key = 1233;
    int shmid;
    char *shared_memory;

    // Create shared memory segment
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach shared memory
    shared_memory = (char *)shmat(shmid, NULL, 0);

    // Write data into shared memory
    printf("Enter message: ");
    fgets(shared_memory, 1024, stdin);

    printf("Message written to shared memory.\n");

    // Detach shared memory
    shmdt(shared_memory);

    return 0;
}