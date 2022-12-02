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



int main(int argc, char * argv[]){


}
