int main(int argc, char * argv[]){

    int x,y;

    //première section instructions des assembleurs entre ""
    //deuxième section : spécification des des opérandes de sortie ds instructions
    //troisième section : contient les opérandes d'entrée
    //quatrième section : déclare les modifications apportées par les instructions
    //les sections sont séparées par :
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
            "ret"
            :"=r"(y)
            :"r"(x));
}
