#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>  

#define NOMBRE 6400
    
    //première section instructions des assembleurs entre ""
    //deuxième section : spécification des des opérandes de sortie ds instructions
    //troisième section : contient les opérandes d'entrée
    //quatrième section : déclare les modifications apportées par les instructions
    //les sections sont séparées par :


void init(){
    asm("lock:"                     
            ".long 0"  );
}


void lock(){
    asm("enter:"
            "movl $1, %eax"              
            "xchgl %eax, (lock)"         
                            
                            
            "testl %eax, %eax"           
            "jnz enter"                  
            "ret");
}

void unlock(){
    asm("leave:"
            "movl $0, %eax"              
            "xchgl %eax, (lock)"         
            "ret");
}

void* test_and_set(void* nombreAcces){

    while(nombreAcces>0){
        asm("lock:"                     
            ".long 0"
        "enter:"
            "movl $1, %eax"              
            "xchgl %eax, (lock)"         
                            
                            
            "testl %eax, %eax"           
            "jnz enter"                  
            "ret"
        "leave:"
            "movl $0, %eax"              
            "xchgl %eax, (lock)"         
            "ret");
        nombreAcces--;
    }
    
}



int main(int argc, char * argv[]){

    int nomThread = atoi(argv[1]);
    int err;

    int acces = NOMBRE/nomThread;

    pthread_t set[nomThread];
    for (int i =0; i<nomThread;i ++){
        err = pthread_create(&set[i],NULL, &test_and_set, (void*)&acces);
        if(err!=0){
            error(err,"pthread_create");
        }
    }

    for(int i=nomThread-1;i>=0;i--) {
        err=pthread_join(set[i],NULL);
        if(err!=0){
            error(err,"pthread_join_producteur");
        }
        
    }

    return(EXIT_SUCCESS);


}
