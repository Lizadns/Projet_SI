#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>  

#define NOMBRE 6400
    
    //première section instructions des assembleurs entre ""
    //deuxième section : spécification des des opérandes de sortie ds instructions
    //troisième section : contient les opérandes d'entrée
    //quatrième section : déclare les modifications apportées par les instructions
    //les sections sont séparées par :



int mutex_init(int** lock){
    *lock = (int*) malloc(sizeof(int));
    if (lock == NULL){
        return -1;
    }
    **lock=0;
    return 0;
}

int test_and_set(int* lock, int val){
    int b = val;
    asm volatile("xchgl %0, %1"//%0=input,%1=output  -> échange la valeur de lock et la met dans b            
    :"+r"(b)//input
    :"m"(*lock)//output
    :"memory");
    return b;
}

void mutex_lock(int* lock){
    while(test_and_set(lock, 1)){
        while(*lock){
        }
    }
}

void mutex_unlock(int* lock){
    test_and_set(lock,0);
}

void mutex_destroy(int* lock){
    free(lock);
}

