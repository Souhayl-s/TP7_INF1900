#include "class_timer.hpp"

volatile int gTempsEcoule = 0 ; // variable globale non volatile (utilise par la methode timer dans tous les cas)

void allumer(){
    PORTA |= (1 << PORTA0) ;

}

void eteindreLed(void){
    PORTA &= ~(1 << PORTA0) ;
}


int main(){

    DDRA= (1 << DDA0 | 1 << DDA1) ; // A0 et A1 en sortie pour les DELS
    

    Timer minuterie = Timer(NumeroTimer::TIMER2 , Unite::MS) ; 
    minuterie.demarrerChronometre() ;
    eteindreLed();
    while (gTempsEcoule < 2000){
        // rester eteint 2s
    }
    allumer();
    minuterie.arreterChronometre();
    minuterie.reprendreChronometre();
    allumer();
    while (gTempsEcoule < 6000){
        // rester allume 4s
    }
    gTempsEcoule = 0 ;
    minuterie.demarrerChronometre();
    eteindreLed();
    while (gTempsEcoule < 3000){
        // rester eteint 3s
    }
    gTempsEcoule = 0 ;
    minuterie.demarrerChronometre();
    allumer();
    while(gTempsEcoule < 3000){
        // rester allume 3s
    }
    eteindreLed();
    
}
// ISR(TIMER0_COMPA_vect){
//     ++gTempsEcoule ;
// }

ISR(TIMER2_COMPA_vect){
    ++gTempsEcoule ;
}

// ISR(TIMER1_COMPA_vect){
//     ++gTempsEcoule ;
// }



