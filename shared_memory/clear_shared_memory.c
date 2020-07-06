#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 100

int main(){
    int shmid;

    key_t key = 123456;

    char *shared_memory;

    /* create shared_memory */
    if((shmid = shmget(key, SIZE, IPC_CREAT | 0644)) < 0){
        // failed create shared_memory
        printf("failed create shared_memory\n");
        exit(0);
    }

    /* delete shared_memory */
    if((shmctl(shmid, IPC_RMID, 0) == -1)){
        printf("failed delete shared_memory\n");
        exit(0);
    }else{
        printf("success delete shared_memory\n");
    }
    
    return 0;
}
