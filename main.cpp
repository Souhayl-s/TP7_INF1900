#include "interruptions.hpp"

volatile bool gBoutonPresse = false ;

bool estBoutonPresse(){
    return (PIND & (1<<PIND2)) ;
}

void allumer(){
    PORTA |= (1 << PORTA0) ;

}

void eteindreLed(void){
    PORTA &= ~(1 << PORTA0) ;
}

int main(){
    DDRA |= ((1<<DDA0) | (1<<DDA1)) ; // A0 et A1 en sortie

    InterruptionExterne bouton (Broche::D2 , ConditionInterruption::FRONT) ; // bouton relie a D2
    bouton.activerInterruptionExterne() ; 

    while (true){
        while(gBoutonPresse){
            allumer() ; 
        }
        eteindreLed();
    }
}

const int8_t DELAI_DEBOUNCE {30} ; 

ISR(INT0_vect)
{
    _delay_ms(DELAI_DEBOUNCE);
    if (estBoutonPresse()){
        gBoutonPresse = true ;
    }
    else{
        gBoutonPresse= false ;
    }
    // Set le interrupt flag de D2
    EIFR |= (1 << INTF0);
}

