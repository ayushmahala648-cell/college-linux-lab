#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// reader program

int main()
{
    key_t key = 1233;
    int shmid;
    char *shared_memory;

    
    shmid = shmget(key, 1024, 0666);

   
    shared_memory = (char *)shmat(shmid, NULL, 0);

   
    printf("Message read from shared memory: %s\n", shared_memory);

  
    shmdt(shared_memory);

   
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}