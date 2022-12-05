#define TEST-AND-SET_H
#include "test-and-set.c"


void error(int err, char *msg){}
void mutex_init(void* lock){}
void mutex_lock(void* lock){}
void* test_and_set(void* nombreAcces){}