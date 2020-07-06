#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

static pthread_t thr;
static int thr_id;
static void *treturn;

void thread_start();
void thread_stop();
void* thread_function1();

void thread_start(){
    thr_id = pthread_create(&thr, NULL, thread_function1, NULL);
}

void thread_stop(){
    thr_id = pthread_join(thr, &treturn);
}

void *thread_function1(){
    for(int i = 0; 1; i++){
        printf("thread_func1(%d)!!\n",i);

        sleep(3);
    }
}

int main(){
    thread_start();
    for(int i = 0; 1 ; i++){
        printf("main thread(%d)!\n", i);

        sleep(1);
    }
}
