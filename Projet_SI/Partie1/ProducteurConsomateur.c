#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>

#define MAX 8192//nombre d'éléments consommés et produits
#define BUFFERSIZE 8
pthread_mutex_t mutex;
pthread_mutex_t produ;
pthread_mutex_t consom;

sem_t empty;
sem_t full;
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
    pthread_mutex_lock(&produ);
    while(countProduc<MAX){
        countProduc++;
        pthread_mutex_unlock(&produ);
        item=rand();//produce(item) de base 
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);
        // section critique
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n",*((int *)pno),buffer[in],in);
        for (int i=0; i<10000; i++);//pour pas que c soit trop séquentiel, on ajoute du temps
        in = (in+1)%BUFFERSIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // une place remplie en plus
        
    }
}

// Consommateur
void* consumer(void *cno){
    pthread_mutex_lock(&consom);
    while(countConsum<MAX){
        countConsum++;
        pthread_mutex_unlock(&consom);
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);
        // section critique
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item,out);
        for (int i=0; i<10000; i++);
        out = (out+1)%BUFFERSIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // une place libre en plus
        
    }
}


int main(int argc, char * argv[]){
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&produ, NULL);
    pthread_mutex_init(&consom, NULL);

    int err;

    err = sem_init(&empty, 0 , BUFFERSIZE); // buffer rempli, pshared=0 donc le semaphore est partagé entre les diff thread; valeur initiale est 8,
    if (err!=0){
        error(err,"sem_init");
    }

    err=sem_init(&full, 0 , 0); // buffer vide, valeur initiale est 0,
    if (err!=0){
        error(err,"sem_init");
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
    err=pthread_mutex_destroy(&(mutex));
    if(err!=0){
        error(err,"pthread_mutex_destroy");
    }
    err=pthread_mutex_destroy(&consom);
    if(err!=0){
        error(err,"pthread_mutex_destroy");
    }
    err=pthread_mutex_destroy(&produ);
    if(err!=0){
        error(err,"pthread_mutex_destroy");
    }

    err=sem_destroy(&empty);
    if(err!=0){
        error(err,"sem_destroy_empty");
    }

    err=sem_destroy(&full);
    if(err!=0){
        error(err,"sem_destroy_full");
    }
    return(EXIT_SUCCESS);


}
