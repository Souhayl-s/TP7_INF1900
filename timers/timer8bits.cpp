#include "class_timer.hpp"

Timer8Bits::Timer8Bits(NumeroTimer numeroTimer, Unite uniteDeTemps)  
    : Timer(numeroTimer, uniteDeTemps)
{
    switch (numeroTimer_)
    {
        case NumeroTimer::TIMER0:
            compteur_ = &TCNT0;
            valeurComparaison_ = &OCR0A;
            registreControleA_ = &TCCR0A;
            registreControleB_ = &TCCR0B;
            registreInterruption_ = &TIMSK0;
            break;
        case NumeroTimer::TIMER2:
            compteur_ = &TCNT2;
            valeurComparaison_ = &OCR2A;
            registreControleA_ = &TCCR2A;
            registreControleB_ = &TCCR2B;
            registreInterruption_ = &TIMSK2;
            break;
        default:
            break;
    }
}


void Timer8Bits::initialiserTimer(void){
    cli();
    *compteur_ = cycleDepart_ ; 
    *valeurComparaison_ = nCycles_ ;
    // choix des modes d'operation 
    *registreControleA_ |= (1<<WGM01) ;
    if(numeroTimer_ == NumeroTimer::TIMER0) {*registreControleB_ |= ( (1<<CS02)  | (1 << CS00) );}
    else {*registreControleB_ |= ( (1<<CS22) | (1 << CS21) | (1 << CS20) );}
    // configuration de l'interruption
    *registreInterruption_ |= (1 <<OCIE0A) ;
    sei();
}

void Timer8Bits::arreterChronometre(){
    cycleDepart_ = *compteur_ ; // sauvegarder la derniere valeur timer
    *registreInterruption_ &= ~(1 <<OCIE1A) ; // arreter les interruptions (fonctionne pour tous les timers)
}