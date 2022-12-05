#ifndef TEST_AND_SET_H
#define TEST_AND_SET_H

void mutex_init(void* lock);
void mutex_lock(void* lock);
void mutex_unlock(void* lock);
void* test_and_set(void* nombreAcces);

#endif /* TEST_AND_SET_H */