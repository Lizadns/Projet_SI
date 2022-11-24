#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int buffer[8];
int in =0;//index auquel les produceurs mettre la porchaine item
int out = 0;//index de l'item qui va être consumer par le consomateur
int elem = 16;//nombre d'éléments consomer et produit
int countProduc = 0;
int countConsum = 0;

void error(int err, char *msg){
    fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n", msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}
int remov(){
    int item =buffer[out];
    out = (out +1)%8;
    return item;
}

void insert_item(int item){
    buffer[in]=item;
    in = (in+1)%8;
}

// Producteur
void* producer(){
    int item;
    while(countProduc<elem){
        item=rand();//produce(item) de base 
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);
        printf("Producteur produit\n");
        // section critique
        insert_item(item);//utiliser des indices(2) pour savoir ou on est dans la tableau pour savoir si il a ete consumer ou pas
        for (int i=0; i<10000; i++);//pour pas que c soit trop séquentiel, on ajoute du temps
        countProduc++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // une place remplie en plus
        
    }
}

// Consommateur
void* consumer(){
    int item;
    while(countConsum<elem){
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);
        printf("Consomateur consome\n");
        // section critique
        item=remov();
        for (int i=0; i<10000; i++);
        countConsum++;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // une place libre en plus
        
    }
}



int main(int argc, char * argv[]){

    pthread_mutex_init(&mutex, NULL);
    int err;

    err = sem_init(&empty, 0 , 8); // buffer rempli, pshared=0 donc le semaphore est partagé entre les diff thread; valeur initiale est 8,
    if (err!=0){
        error(err,"sem_init");
    }

    err=sem_init(&full, 0 , 0); // buffer vide, valeur initiale est 0,
    if (err!=0){
        error(err,"sem_init");
    }

    int produc=atoi(argv[1]);
    int conso=atoi(argv[2]);
    pthread_t producteur[produc];
    pthread_t consomateur[conso];

    for(int i=0;i<produc;i++){
        err=pthread_create(&(producteur[i]),NULL,&producer,NULL);
        if(err!=0){
            error(err,"pthread_create");
        }
    }

    for(int i=0;i<conso;i++){
        err=pthread_create(&(consomateur[i]),NULL,&consumer,NULL);
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
        err=pthread_join(consomateur[i],NULL);
        if(err!=0){
            error(err,"pthread_join_consomateur");
        }
        
    }
    err=pthread_mutex_destroy(&(mutex));
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
