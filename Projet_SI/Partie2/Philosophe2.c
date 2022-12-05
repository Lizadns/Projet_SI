#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "semaphore.c"
#include "test_and_set.h"

typedef struct arg {
    int taille;
    int** baguette;
    int id;
}args_t;

void error(int err, char *msg){
    fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n", msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

void mange(int id) {
    //printf("Philosophe [%d] mange\n",id);
    //philosophe mange
}

void* philosophe (void* arg){

    args_t* arguments = (args_t*) arg;
    int id=arguments->id;
    int taille = arguments->taille;
    int** baguette = arguments->baguette;

    int left = id;
    int right = (left + 1) % taille; // pour si left est le dernier, celui à se droite est le premier
    int j = 0;
    while(j<100000) {
    // philosophe pense
        if(left<right) {
            mutex_lock(baguette[left]);
            mutex_lock(baguette[right]);
        }
        else {
            mutex_lock(baguette[right]);
            mutex_lock(baguette[left]);
        }
        mange(id);
        mutex_unlock(baguette[left]);
        mutex_unlock(baguette[right]);
        j++;
    }
    return (NULL);
}

int main(int argc, char * argv[]){//argc est le nombre d'argument,argv[0] pointe vers le nom du document et argv[1] vers le premier argument lors de l'appel
    
    int taille=atoi(argv[1]);
    int* baguette[taille];
    pthread_t phil[taille];
    int err;
    args_t arg[taille];
    
    for (int i =0; i<taille;i++){
        err=mutex_init(&(baguette[i]));
        if (err!=0){
            error(err,"pthread_mutex_init");
        }
    }

    for (int i =0; i<taille;i++){
        arg[i].taille = taille;
        arg[i].id = i;
        arg[i].baguette = baguette;
    }

    for(int i=0;i<taille;i++){
        err=pthread_create(&(phil[i]),NULL,&philosophe,(void*)&(arg[i]));
        if(err!=0){
            error(err,"pthread_create");
        }
    }
    
    for(int i=taille-1;i>=0;i--) {
        err=pthread_join(phil[i],NULL);
        if(err!=0){
            error(err,"pthread_join");
        }
        
    }
    for (int i = 0; i<taille; i++){
        mutex_destroy((baguette[i]));
        //if(err!=0){
        //    error(err,"pthread_mutex_destroy");
        //}
    }
    return(EXIT_SUCCESS);
}