#include "class_timer.hpp"

volatile int gTempsEcoule = 0 ; // variable globale non volatile (utilise par la methode timer dans tous les cas)

void allumer(){
    PORTA |= (1 << PORTA0) ;

}

void eteindreLed(void){
    PORTA &= ~(1 << PORTA0) ;
}




int main(){

    auto& DR = DDRA ; 

    DR |= (1 << DDA0 | 1 << DDA1) ; // A0 et A1 en sortie pour les DELS

    Timer minuterie1  = Timer(NumeroTimer::TIMER2 , Unite::MS) ; 

    gTempsEcoule = 0 ; 
    minuterie1.demarrerChronometre() ; 
    eteindreLed();

    while(gTempsEcoule < 5000){
        // rester eteint
    }
    allumer();
    minuterie1.arreterChronometre();
    minuterie1.reprendreChronometre();
    while(gTempsEcoule < 10000){
        // reste allume 5s restantes
    }
    eteindreLed() ;
    gTempsEcoule = 0 ;
    minuterie1.demarrerChronometre();
    while(gTempsEcoule < 3000){
        // reste eteint 3s
    }
    allumer();

    // minuterie1.reprendreChronometre();
    // allumer();

    // while(gTempsEcoule < duree ){
    //     // rester allumer 5 secondes
    // }
    
    // gTempsEcoule = 0 ;
    // minuterie1.demarrerChronometre();
    // eteindreLed();

    // duree = 5000 ; 
    // while (gTempsEcoule < duree)
    // {
    //     // rester eteint pendant 5 secondes
    // }
    // allumer();
    
}

ISR(TIMER0_COMPA_vect){
    ++gTempsEcoule ;
}

// ISR(TIMER1_COMPA_vect){
//     ++gTempsEcoule ;
// }




