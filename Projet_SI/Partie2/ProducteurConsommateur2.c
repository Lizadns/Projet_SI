#include "semaphore.h"
#include "test-and-test-and-set.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h> 

#define MAX 8192//nombre d'éléments consommés et produits
#define BUFFERSIZE 8
int* mutex;
int* produ;
int* consom;

my_sem_t* empty;
my_sem_t* full;
int buffer[BUFFERSIZE];
int in =0;//index auquel les produceurs mettent le prochain item
int out = 0;//index de l'item qui va être consumer par le consommateur
int countProduc = 0;
int countConsum = 0;

void error(int err, char *msg){
    fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n", msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

// Producteur
void* producer(void *pno){
    int item;
    while(true){
        mutex_lock(produ);
        if(countProduc==MAX){
            mutex_unlock(produ);
            break;
        }
        else{
            countProduc++;
            mutex_unlock(produ);
        }
        item=rand();//produce(item) de base 
        my_sem_wait(empty); // attente d'une place libre
        mutex_lock(mutex);
        // section critique
        buffer[in] = item;
        //printf("Producer %d: Insert Item %d at %d\n",*((int *)pno),buffer[in],in);
        for (int i=0; i<10000; i++);
        in = (in+1)%BUFFERSIZE;
        mutex_unlock(mutex);
        my_sem_post(full); // une place remplie en plus
        
    }
    return NULL;
}

// Consommateur
void* consumer(void *cno){
    while(true){
        mutex_lock(consom);
        if(countConsum==MAX){
            mutex_unlock(consom);
            break;
        }
        else{
            countConsum++;
            mutex_unlock(consom);
        }
        my_sem_wait(full); // attente d'une place remplie
        mutex_lock(mutex);
        // section critique
        int item = buffer[out];
        //printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item,out);
        for (int i=0; i<10000; i++);
        out = (out+1)%BUFFERSIZE;
        mutex_unlock(mutex);
        my_sem_post(empty); // une place libre en plus
        
    }
    return NULL;
}


int main(int argc, char * argv[]){
    mutex_init(&mutex);
    mutex_init(&produ);
    mutex_init(&consom);

    int err;

    err = my_sem_init(&empty, BUFFERSIZE); // buffer rempli, pshared=0 donc le semaphore est partagé entre les diff thread; valeur initiale est 8,
    if (err!=0){
        error(err,"my_sem_init");
    }

    err=my_sem_init(&full,0); // buffer vide, valeur initiale est 0,
    if (err!=0){
        error(err,"my_sem_init");
    }

    int produc=atoi(argv[1]);
    int conso=atoi(argv[1]);
    pthread_t producteur[produc];
    pthread_t consommateur[conso];
    int arg[produc];
    for (int i = 0; i<produc; i++){
        arg[i]=i;
    }
    for(int i=0;i<produc;i++){
        err=pthread_create(&(producteur[i]),NULL,&producer,(void*)&arg[i]);
        if(err!=0){
            error(err,"pthread_create");
        }
    }
    
    for(int i=0;i<conso;i++){
        err=pthread_create(&(consommateur[i]),NULL,&consumer,(void*)&arg[i]);
        if(err!=0){
            error(err,"pthread_create");
        }
    }

    for(int i=produc-1;i>=0;i--) {
        err=pthread_join(producteur[i],NULL);
        if(err!=0){
            error(err,"pthread_join_producteur");
        }
        
    }
    
    for(int i=conso-1;i>=0;i--) {
        err=pthread_join(consommateur[i],NULL);
        if(err!=0){
            error(err,"pthread_join_consommateur");
        }
        
    }
    mutex_destroy(mutex);

    err=my_sem_destroy(empty);
    if(err!=0){
        error(err,"my_sem_destroy_empty");
    }

    err=my_sem_destroy(full);
    if(err!=0){
        error(err,"my_sem_destroy_full");
    }

    mutex_destroy(produ);
    mutex_destroy(consom);
    

    return(EXIT_SUCCESS);


}