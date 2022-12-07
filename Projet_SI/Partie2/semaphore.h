#ifndef SEMAPHORE
#define SEMAPHORE

typedef struct my_sem {
    int* lock; //verrou du sémaphore
    int val; //valeur du sémaphore
}my_sem_t;

/**
 * @param sem sémaphore à initialiser
 * @param value valeur initiale à donner au sémaphore
 * @return 0 si pas d'erreurs, -1 sinon
*/
int my_sem_init(my_sem_t** sem, int value);

/**
 * @param sem sémaphore 
 * @return 0 si pas d'erreurs, -1 sinon
*/
int my_sem_wait(my_sem_t* sem);

/**
 * @param sem sémaphore
 * @return 0 si pas d'erreurs, -1 sinon
*/
int my_sem_post(my_sem_t* sem);

/**
 * @param sem sémaphore à libérer
 * @return 0 si pas d'erreurs, -1 sinon
*/
int my_sem_destroy(my_sem_t* sem);

#endif /* SEMAPHORE */