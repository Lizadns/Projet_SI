#include "semaphore.c"
#include "test_and_set.h"

//si un writer est prêt, on empêche un reader de lire MAIS 
//-on les laisse terminer 
//-si un writer est occupé, ne pas liberer la db
// 2 sémaphores -> bloquent et 2 mutex -> protègent les values partagées
//test liza

int* mutex_readcount; //Protège readcount
int* mutex_writecount; //Protège write count
int* z;

my_sem_t wsem;//Accès exclusif à la db
my_sem_t rsem;//Pour bloquer des readers 

int readcount=0;
int writecount=0;

int countr =0;
int countw = 0;

void error(int err, char *msg){
    fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n", msg,err,strerror(errno));
    exit(EXIT_FAILURE);
}

//premier ecrivain arrive, on incrémente readCount
void* writer(){
    while (countw<640){
        //prepare_data();
        for(int i =0; i<10000; i++);
        mutex_lock(mutex_writecount);//incremente la valeur partager
        //printf("j ecris");
        //section critique : + writecount
        writecount=writecount+1;
        if(writecount==1){
            //premier writer arrive
            my_sem_wait(&rsem);//attends plus de readers
        }
        mutex_unlock(mutex_writecount);//pour que d'autre puisse incrémenter la valeurs

        //partie 2
        my_sem_wait(&wsem);
         //section critique, un seul writer à la fois
         //write_database();
        for(int i =0; i<10000; i++);
        my_sem_post(&wsem);

         //partie3
        mutex_lock(mutex_writecount);
         //section critique: -writecount
        writecount=writecount-1;
        if(writecount==0){
            my_sem_post(&rsem);//autorise les readers
        }
        mutex_unlock(mutex_writecount);
        countw++;
    }
}

void* reader(){
    while(countr<2560){
        mutex_lock(z);
        //exclusion mutuelle, un seul reader en attente sur rsem
        my_sem_wait(&rsem);
        mutex_lock(mutex_readcount);
        //section critique:+readcount
        //printf("je lis");
        readcount=readcount+1;
        if(readcount==1){
            //premier reader arrive
            my_sem_wait(&wsem);
        }
        mutex_unlock(mutex_readcount);
        my_sem_post(&rsem);
        mutex_unlock(z);
        //read_database();
        for(int i =0; i<10000; i++);
        //partie2
        mutex_lock(mutex_readcount);
        //section critique:-readcount
        readcount=readcount-1;
        if(readcount==0){
            //depart du derner reader
            my_sem_post(&wsem);//les écrivent peuvent ecrire
        }
        mutex_unlock(mutex_readcount);
        countr++;
    }
}

//mais un dernier problème 
//si un reader 1 arrive,la valeur de rsem est à 1 et est donc autorisé à passer, 
//puis writer 1, il exécute son code,.. et il attend que reader 1 soit fini pour qu'il puisse écirre jusqu'à ce que reader 1 face my_sem_post
//et reader2 bloqué à      my_sem_wait(&rsem) pdt que le reader 1 s'exécute
//donc 2 dans la file d'attente, et on ne sait pas le quel va être choisi pour être exécuter après
//donc le writer n'a pas priorité
//utiliser 3 mutex 

int main(int argc, char * argv[]){

    int err;

    err = my_sem_init(&wsem, 1);
    if (err!=0){
        error(err,"my_sem_init");
    }

    err = my_sem_init(&rsem, 1);
    if (err!=0){
        error(err,"my_sem_init");
    }

    err = mutex_init(mutex_readcount);
    if (err!=0){
        error(err,"pthread_mutex_init");
    }
    
    err= mutex_init(mutex_writecount);
    if (err!=0){
        error(err,"pthread_mutex_init");
    }

    err= mutex_init(z);
    if (err!=0){
        error(err,"pthread_mutex_init");
    }

    int nomWriters = atoi(argv[1]);
    int nomReaders = atoi(argv[2]);

    pthread_t writers[nomWriters];
    pthread_t readers[nomReaders];

    for (int i =0; i<nomWriters;i ++){
        err = pthread_create(&writers[i],NULL, &writer, NULL);
        if(err!=0){
            error(err,"pthread_create");
        }
    }
    for (int i =0; i<nomReaders;i ++){
        err = pthread_create(&readers[i],NULL, &reader, NULL);
        if(err!=0){
            error(err,"pthread_create");
        }
    }

    for(int i = nomWriters-1; i>=0; i--){
        err=pthread_join(writers[i],NULL);
        if(err!=0){
            error(err,"pthread_join_writers");
        }
    }

    for(int i = nomReaders-1; i>=0; i--){
        err=pthread_join(readers[i],NULL);
        if(err!=0){
            error(err,"pthread_join_readers");
        }
    }
    mutex_destroy(mutex_readcount);
    //if(err!=0){
    //    error(err,"pthread_mutex_readcount_destroy");
    //}
    mutex_destroy(mutex_writecount);
    //if(err!=0){
    //    error(err,"pthread_mutex_writecount_destroy");
    //}
    mutex_destroy(z);
    //if(err!=0){
    //    error(err,"pthread_mutex_z_destroy");
    //}

    err=my_sem_destroy(&wsem);
    if(err!=0){
        error(err,"semw_destroy");
    }

    err=my_sem_destroy(&rsem);
    if(err!=0){
        error(err,"semr_destroy");
    }
    return(EXIT_SUCCESS);
}