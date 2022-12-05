#ifndef TEST_AND_SET_H
#define TEST_AND_SET_H

int mutex_init(int** lock);
int test_and_set(int* lock, int val);
void mutex_lock(int* lock);
void mutex_unlock(int* lock);
void mutex_destroy(int* lock);

#endif /* TEST_AND_SET_H */