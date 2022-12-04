#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h> 
#include "test-and-set.c"

typedef struct my_sem {
    int lock;
    int val;
}my_sem_t;

int my_sem_init(my_sem_t* sem, int value){
    sem = malloc(sizeof(my_sem_t));
    if (sem == NULL){
        return -1;
    }
    sem->val = value;
    mutex_init(&sem->lock);
    return 0;
}

int my_sem_wait(my_sem_t* sem){
    bool wait = true;
    while (wait){
        if(sem->val>0){
            mutex_lock(&sem->lock);
            sem->val --;
            mutex_unlock(&sem->lock);
            wait = false;
        }
    }
    return 0;
}


int my_sem_post(my_sem_t* sem){
    mutex_lock(&sem->lock);
    sem->val ++;
    mutex_unlock(&sem->lock);
    return 0;
}

int my_sem_destroy(my_sem_t* sem){
    free(sem);
    return 0;
}