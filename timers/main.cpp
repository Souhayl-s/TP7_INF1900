#include "class_timer.hpp"

volatile int gTempsEcoule = 0 ; // variable globale non volatile (utilise par la methode timer dans tous les cas)
volatile bool gestAllume = false ;

void allumer(){
    PORTA |= (1 << PORTA0) ;

}

void eteindreLed(void){
    PORTA &= ~(1 << PORTA0) ;
}


int main(){

    DDRA= (1 << DDA0 | 1 << DDA1) ; // A0 et A1 en sortie pour les DELS

    // Timer16Bits minuterie (NumeroTimer::TIMER1 , Unite::SECS) ; 
    // minuterie.setUniteTemps(Unite::MS);

    Timer16Bits minuterie (NumeroTimer::TIMER1, Unite::SECS) ; 

    minuterie.demarrerChronometre() ;
    eteindreLed();
    while (gTempsEcoule < 2){
        // rester eteint 2s
    }
    allumer();
    minuterie.arreterChronometre();
    minuterie.reprendreChronometre();
    allumer();
    while (gTempsEcoule < 6){
        // rester allume 4s
    }
    gTempsEcoule = 0 ;
    minuterie.demarrerChronometre();
    eteindreLed();
    while (gTempsEcoule < 3){
        // rester eteint 3s
    }
    gTempsEcoule = 0 ;
    minuterie.demarrerChronometre();
    allumer();
    while(gTempsEcoule < 3){
        // rester allume 3s
    }
    eteindreLed();
    
}

ISR(TIMER0_COMPA_vect){
    ++gTempsEcoule ;
}

ISR(TIMER1_COMPA_vect){
    ++gTempsEcoule ;
}

ISR(TIMER2_COMPA_vect){
    ++gTempsEcoule ;
}



/*test evenement intervalle*/

// if (gestAllume){
//     eteindreLed();
//     gestAllume = false;
// }
// else{
//     allumer();
//     gestAllume = true ;
// }
