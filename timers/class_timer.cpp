#include "class_timer.hpp"



Timer::Timer(NumeroTimer numeroTimer , Unite uniteDeTemps):
    uniteDeTemps_(uniteDeTemps),
    numeroTimer_ (numeroTimer)
{       
    cycleDepart_ = 0 ; 
    nCycles_ = 0 ; 
}

// prescaler toujours a  1024 
void Timer::initialiserTimer(void){ 
    cli();

    if (numeroTimer_ == NumeroTimer::TIMER1){
        TCNT1 = cycleDepart_ ; 
        OCR1A = nCycles_ ;
        *registreControleB_ |= (1 << WGM12 |1 << CS12 | 1 << CS10) ; 
        *registreControleB_ &= ~(1 << WGM13 | 1 << CS11) ;         
    }

    // Activation des interruptions lors du compare match event (meme chose pour les 2 timers)
    *registreInterruption_ |= (1 <<OCIE1A) ;
    sei();
}


void Timer::lancerEvenementIntervalle(double intervalle){
    convertirTempsEnCycles(intervalle) ; 
    cycleDepart_ = 0 ;
    initialiserTimer();
} 


void Timer::demarrerChronometre(){
    convertirTempsEnCycles(DUREE_1_UNITE) ; // conversion de 1 sec / ms en cycles 
    cycleDepart_ = 0 ; // commencer au cycle 0 
    initialiserTimer() ;  
}


void Timer::reprendreChronometre(void){
    initialiserTimer(); // relance le timer en commencant par le cycle atteint au dernier arret
}


void Timer::arreterChronometre(){
    
    cycleDepart_ = TCNT1; // sauvegarder la derniere valeur timer
    *registreInterruption_ &= ~(1 <<OCIE1A) ; // arreter les interruptions (fonctionne pour tous les timers)
}



void Timer::convertirTempsEnCycles(double duree){
    switch (uniteDeTemps_) 
    {
        case Unite::SECS :
            nCycles_ = freqAvecPrescaler ; // nombre de cycles equivalent a 1 seconde
            break;
        case Unite::MS :
            nCycles_ = freqAvecPrescaler/SECTOMS; // nombre de cycles equivalent a 1 ms
            break;            
        default:
            break;
    }  
    nCycles_ = int(nCycles_*duree); // nombre de cycles equivalent a X secondes / ms (max ~8 secondes / ~8000 ms)
}