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



void mutex_init(void* lock){
    int* ptr= (int*) lock;
    *ptr=0;
}

int test_and_set(void* lock, int val){
    int* ptr = (int*) lock;
    int b = val;
    asm volatile("xchgl %0, %1"//%0=input,%1=output  -> échange la valeur de lock et la met dans b            
    :"+r"(b)//input
    :"m"(*ptr)//output
    :"memory");
    return b;
}

void mutex_lock(void* lock){
    int* ptr = (int*) lock;
    while(test_and_set(lock, 1)){
        while(*ptr){
        }
    }
    
    //printf("%d %d lock2\n", lock, b);
}

void mutex_unlock(void* lock){
    test_and_set(lock,0);
}

