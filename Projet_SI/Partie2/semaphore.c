#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h> 
#include "test-and-test-and-set.h"
#include "semaphore.h"

int my_sem_init(my_sem_t** sem, int value){
    *sem = (my_sem_t*) malloc(sizeof(my_sem_t));
    if (*sem == NULL){
        return -1;
    }
    (*sem)->val = value;
    mutex_init(&(*sem)->lock);
    return 0;
}

int my_sem_wait(my_sem_t* sem){
    bool wait = true;
    while (wait){
        if(sem->val>0){
            mutex_lock(sem->lock);
            sem->val --;
            mutex_unlock(sem->lock);
            wait = false;
        }
    }
    return 0;
}


int my_sem_post(my_sem_t* sem){
    mutex_lock(sem->lock);
    sem->val ++;
    mutex_unlock(sem->lock);
    return 0;
}

int my_sem_destroy(my_sem_t* sem){
    mutex_destroy(sem->lock);
    free(sem);
    return 0;
}