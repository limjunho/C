#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 100

int main(int argc, char *argv[]) {
    int shmid;
    
    key_t key = 123456;

    char *shared_memory;

    /* shared_memory create */
    if ((shmid = shmget(key, SIZE, IPC_CREAT | 0644)) < 0)
    {   // failed create shared_memory
        printf("shmget error\n");
        exit(1);
    }
    
    /* add to segment to shared_memory */
    if ((shared_memory = shmat(shmid, NULL, 0)) == (char *) - 1)
    {   // failed add segment to shared_memory
        printf("shmat error\n");
        exit(1);
    }
    
    memset(shared_memory, 0, strlen(shared_memory));   // shared_memory reset
    memcpy(shared_memory, argv[1], strlen(argv[1]));    // first parameter copy to shared_memory
}
