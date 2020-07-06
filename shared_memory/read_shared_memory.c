#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void main(){
    int shmid;
    key_t key = 123456;
    char *shm, *s;
    
    /* connect shared_memory */
    if((shmid = shmget(key, SIZE, 0644))<0){
        perror("failed shmget");   // perror? - print error
        exit(1);
    }
    
    if((shm = shmat(shmid, NULL, 0))==(char*) -1){
        perror("failed shmat");
        exit(1);
    }

    s=shm;
    printf("%s\n",s);

    exit(0);
}
