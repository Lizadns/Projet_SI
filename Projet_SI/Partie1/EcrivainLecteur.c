#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>

//si un writer est prêt, on empêche un reader de lire MAIS 
//-on les laisse terminer 
//-si un writer est occupé, ne pas liberer la db
// 2 sémaphores -> bloquent et 2 mutex -> protègent les values partagées


pthread_mutex_t mutex_readcount; //Protège readcount
pthread_mutex_t mutex_writecount; //Protège write count
pthread_mutex_t z;

sem_t wsem;//Accès exclusif à la db
sem_t rsem;//Pour bloquer des readers 

int readcount=0;
int writecount=0;

//premier ecrivain arrive, on incrémente readCount
void writer(void){
    while (true){
        prepare_data();
        pthread_mutex_lock(&mutex_writecount);//incremente la valeur partager
        //section critique : + writecount
        writecount=writecount+1;
        if(writecount==1){
            //premier writer arrive
            sem_wait(&rsem);//attends plus de readers
        }
        pthread_mutex_unlock(&mutex_writecount);//pour que d'autre puisse incrémenter la valeurs

        //partie 2
         sem_wait(&wsem);
         //section critique, un seul writer à la fois
         write_database();
         sem_post(&wsem);

         //partie3
         pthread_mutex_lock(&mutex_writecount);
         //section critique: -writecount
         writecount=writecount-1;
         if(writecount==0){
             sem_post(&rsem);//autorise les readers
         }
    }
}

void reader(void)
    {while(true)
 {
     pthread_mutex_lock(&z);
     //exclusion mutuelle, un seul reader en attente sur rsem
     sem_wait(&rsem);

     pthread_mutex_lock(&mutex_readcount);
     //section critique:+readcount
     readcount=readcount+1;
     if(readcount==1){
         //premier reader arrive
         sem_wait(&wsem);
     }
     pthread_mutex_unlock(&mutex_readcount);
     semp_post(&rsem);
     pthread_mutex_unlock(&z);
     read_database();
     //partie2

     pthread_mutex_lock(&mutex_readcount);
     //section critique:-readcount
     readcount=readcount-1;
     if(readcount==0){
         //depart du derner reader
         sem_post(&wsem);//les écrivent peuvent ecrire
     }
     pthread_mutex_unlock(&mutex_readcount);
    }
}

//mais un dernier problème 
//si un reader 1 arrive,la valeur de rsem est à 1 et est donc autorisé à passer, 
//puis writer 1, il exécute son code,.. et il attend que reader 1 soit fini pour qu'il puisse écirre jusqu'à ce que reader 1 face sem_post
//et reader2 bloqué à sem_wait(&rsem) pdt que le reader 1 s'exécute
//donc 2 dans la file d'attente, et on ne sait pas le quel va être choisi pour être exécuter après
//donc le writer n'a pas priorité
//utiliser 3 mutex 

void main(int argc, void * argv[]){

    sem_init(&wsem, 0, 1);
    sem_init(&rsem, 0, 1);

    int nomWriters = argv[1];
    int nomReaders = argv[2];
}