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

    int duree = 10 ; // en secondes

    minuterie1.demarrerTimer() ; 
    allumer() ;

    while (minuterie1.obtenirTemps() < duree){
        if (minuterie1.obtenirTemps() == 5){
            minuterie1.arreterTimer() ; 
            // eteindreLed();
            break ; 
        }
    }

    minuterie1.demarrerTimer();
    eteindreLed() ;        

    while(minuterie1.obtenirTemps() < duree){
        // eteinte pendant 10 secondes
    }

    allumer();

    // minuterie1.reprendreTimer() ; // reprendre a la 5e seconde
    // while (minuterie1.obtenirTemps() < duree){
    //     // rester eteinte pendant les 5s restantes       
    // }

    // allumer() ; 
    
}






