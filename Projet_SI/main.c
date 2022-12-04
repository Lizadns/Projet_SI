#include <stdio.h>

int main(void){
    int a = 420;
    int* ptr = &a;

    int b = 60;

    printf("%d %d\n", a, b);

    asm volatile(
        "xchgl %0, %1"
        : "+r" (b)
        : "m" (*ptr)
        : "memory"
    );

    printf("%d %d\n", a, b);

    return 0;

}