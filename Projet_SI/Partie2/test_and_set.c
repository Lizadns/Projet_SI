#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>  

#define NOMBRE 6400
    

void error(int err, char *msg){
    fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n", msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

int* lock;

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
    while(test_and_set(lock,1)){

    }
}

void mutex_unlock(int* lock){
    test_and_set(lock,0);
}

void* utilisation(void* nombreAcces){
    int* a = (int*) nombreAcces;
    for (int i =0; i< *a; i++){
        mutex_lock(lock);
        //section critique
        for (int j = 0; j<10000; j++);
        mutex_unlock(lock);
    }
    return NULL;
}



int main(int argc, char * argv[]){

    int nomThread = atoi(argv[1]);
    int err;

    int acces = NOMBRE/nomThread;
    mutex_init(&lock);
    pthread_t set[nomThread];
    for (int i =0; i<nomThread;i ++){
        err = pthread_create(&set[i],NULL, &utilisation, (void*)&acces);
        if(err!=0){
            error(err,"pthread_create");
        }
    }

    for(int i=nomThread-1;i>=0;i--) {
        err=pthread_join(set[i],NULL);
        if(err!=0){
            error(err,"pthread_join_producteur");
        }
        
    }

    return(EXIT_SUCCESS);


}
