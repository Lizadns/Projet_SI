#ifndef TEST_AND_SET_H
#define TEST_AND_SET_H

/**
 * @param lock verrou à initialiser
 * @return 0 si pas d'erreurs, -1 sinon
*/
int mutex_init(int** lock);

/**
 * @param lock verrou
 * @param val valeur à laquelle on veut mettre le verrou (0 ou 1)
 * @return 1 si le verrou n'a pas pu être mis à jour, 0 si la valeur du verrou à été mis à jour
*/
int test_and_set(int* lock, int val);

/**
 * @param lock le verrou à lock
 * @return void
*/
void mutex_lock(int* lock);

/**
 * @param lock le verrou à unlock
 * @return void
*/
void mutex_unlock(int* lock);

/**
 * @param lock le verrou à libérer
 * @return void
*/
void mutex_destroy(int* lock);

#endif /* TEST_AND_SET_H */