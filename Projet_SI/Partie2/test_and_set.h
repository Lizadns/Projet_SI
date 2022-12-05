#ifndef TEST_AND_SET_H
#define TEST_AND_SET_H

void mutex_init(void* lock);
int test_and_set(void* lock, int val);
void mutex_lock(void* lock);
void mutex_unlock(void* lock);

#endif /* TEST_AND_SET_H */