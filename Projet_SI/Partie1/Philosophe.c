#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct arg {
    int taille;
    pthread_mutex_t* baguette;
    int id;
}args_t;

void error(int err, char *msg){
    fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n", msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

void mange(int id) {
    printf("Philosophe [%d] mange\n",id);
    for(int i=0;i< rand(); i++) {
    // philosophe mange
    }
}

void* philosophe (void* arg){

    args_t* arguments = (args_t*) arg;
    int id=arguments->id;
    int taille = arguments->taille;
    pthread_mutex_t* baguette = arguments->baguette;

    int left = id;
    int right = (left + 1) % taille; // pour si left est le dernier, celui à se droite est le premier
    int j = 0;
    while(j<10) {//mais le problème c que il fait 100 000 d'affilé
    // philosophe pense
        if(left<right) {
            pthread_mutex_lock(&baguette[left]);
            pthread_mutex_lock(&baguette[right]);
        }
        else {
            pthread_mutex_lock(&baguette[right]);
            pthread_mutex_lock(&baguette[left]);
        }
        mange(id);
        pthread_mutex_unlock(&baguette[left]);
        pthread_mutex_unlock(&baguette[right]);
        j++;
    }
    return (NULL);
}

int main(int argc, char * argv[]){//argc est le nombre d'argument,argv[0] pointe vers le nom du document et argv[1] vers le premier argument lors de l'appel
    
    int taille=atoi(argv[1]);
    pthread_mutex_t baguette[taille];
    pthread_t phil[taille];
    int err;
    args_t arg[taille];
    
    for (int i =0; i<taille;i++){
        err=pthread_mutex_init(&(baguette[i]),NULL);
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
        err=pthread_mutex_destroy(&(baguette[i]));
        if(err!=0){
            error(err,"pthread_mutex_destroy");
        }
    }
    return(EXIT_SUCCESS);
}

//gcc -o philo Philosophe.c -lpthread
//./philo NombreDeThread
//rm -f philo