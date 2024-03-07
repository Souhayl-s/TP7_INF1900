#include "class_timer.hpp"

volatile int gTempsActuel = 0 ; 

const unsigned long int freqCPU = 8'000'000 ;
const unsigned  int prescaler = 1024 ;
const unsigned long int freqAvecPrescaler = freqCPU / prescaler ; // = frequence du timer
const uint16_t SECTOMS = 1000 ; 



Timer::Timer(Unite uniteDeTemps):
    uniteDeTemps_ (uniteDeTemps), // nombre de cycles equivalent a 1 seconde
    nCycles_(freqAvecPrescaler),
    cycleDepart_(0)
{
    switch (uniteDeTemps_)
    {
        case Unite::SECS :
            nCycles_ = freqAvecPrescaler ; // nombre de cycles equivalent a 1 ms
            break;
        case Unite::MS :
            nCycles_ = freqAvecPrescaler/SECTOMS ; // nombre de cycles equivalent a 1 ms
            break;            
        default:
            break;
    }
}

// timer 1 en mode CTC 
// prescaler a 1024 

void Timer::initialiserTimer(void){ 
    cli();
    // initialiser le timer
    TCNT1 = cycleDepart_ ; // le timer commence a compter a partir de ce cycle
    // initialiser le TOP
    OCR1A = nCycles_ ; // valeur de comparaison 
    //2 - Configure WGM et Clock source
    TCCR1B |= (1 << WGM12 |1 << CS12 | 1 << CS10) ; 
    TCCR1B &= ~(1 << WGM13 | 1 << CS11) ; 
    // Activation des interruptions lors du compare match event
    TIMSK1 |= (1 <<OCIE1A) ; 
    sei();
}


int Timer::obtenirTemps(void){
    return gTempsActuel;
}


void Timer::demarrerTimer(void){
    cycleDepart_ = 0 ; // commencer au cycle 0 
    gTempsActuel = 0 ; // remettre le temps a 0
    initialiserTimer() ;  
}

void Timer::reprendreTimer(void){
    initialiserTimer(); // relance le timer en commencant par le cycle atteint au dernier arret
}

void Timer::arreterTimer(){
    cycleDepart_ = TCNT1 ; // sauvegarder la derniere valeur timer
    TIMSK1 &= ~(1 <<OCIE1A) ; // arreter les interruptions du timer1 -> le temps ne s'incremente plus
}

ISR(TIMER1_COMPA_vect)
{
    ++gTempsActuel ; // ajouter 1 seconde
}