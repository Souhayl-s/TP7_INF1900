#include "class_timer.hpp"


void allumer(){
    PORTA |= (1 << PORTA0) ;

}

void eteindreLed(void){
    PORTA &= ~(1 << PORTA0) ;
}




int main(){
    DDRA |= (1 << DDA0 | 1 << DDA1) ; // A0 et A1 en sortie pour les DELS

    Timer minuterie1  = Timer(Unite::SECS) ; 


    minuterie1.demarrerTimer() ; 

    _delay_ms(5000) ; 
    if (minuterie1.obtenirTemps() >= 4){ // est-ce que les interruptions fonctionnenent ?
        allumer() ;
    } 
    
}






