#include "test-and-test-and-set.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h> 

#define NOMBRE 6400
    
    //première section instructions des assembleurs entre ""
    //deuxième section : spécification des des opérandes de sortie ds instructions
    //troisième section : contient les opérandes d'entrée
    //quatrième section : déclare les modifications apportées par les instructions
    //les sections sont séparées par :

int* lock;//si on met en long, il faut changer le l dans xchgl et testl en jsp qu elle autre lettre, peut être en r ou en q


void error(int err, char *msg){
    fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n", msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

void* test_and_test_and_set(void* nombreAcces){
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
        err = pthread_create(&set[i],NULL, &test_and_test_and_set, (void*)&acces);
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
