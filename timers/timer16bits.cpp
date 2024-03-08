#include "class_timer.hpp"

Timer16Bits::Timer16Bits(NumeroTimer numeroTimer, Unite uniteDeTemps)  
    : Timer(numeroTimer, uniteDeTemps)
{
        compteur_ = &TCNT1;
        valeurComparaison_ = &OCR1A;
        registreControleA_ = &TCCR1A;
        registreControleB_ = &TCCR1B;
        registreInterruption_ = &TIMSK1;   
}


void Timer16Bits::initialiserTimer(void)
{
    cli();
    *compteur_ = cycleDepart_ ; 
    *valeurComparaison_ = nCycles_ ;
    // choix des modes d'operation 
    *registreControleB_ |= (1 << WGM12 |1 << CS12 | 1 << CS10) ; 
    *registreControleB_ &= ~(1 << WGM13 | 1 << CS11) ; 
    // configuration de l'interruption
    *registreInterruption_ |= (1 <<OCIE1A) ;
    sei();
}

void Timer16Bits::arreterChronometre(){
    cycleDepart_ = *compteur_; // sauvegarder la derniere valeur timer
    *registreInterruption_ &= ~(1 <<OCIE1A) ; // arreter les interruptions (fonctionne pour tous les timers)
}

