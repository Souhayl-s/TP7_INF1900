#include "class_timer.hpp"

volatile int gTempsActuel = 0 ; 

const unsigned long int freqCPU = 8'000'000 ;
const unsigned  int prescaler = 1024 ;
const unsigned long int freqAvecPrescaler = freqCPU / prescaler ; // = frequence du timer
const uint16_t SECTOMS = 1000 ; 

Timer::Timer(NumeroTimer numeroTimer , Unite uniteDeTemps):
    uniteDeTemps_(uniteDeTemps),
    cycleDepart_(0) // compte a partir de 0 par defaut
{
    switch (numeroTimer_)
    {
    case NumeroTimer::TIMER0 :{
        compteur_ = &TCNT0 ;
        valeurComparaison_ = &OCR0A ;
        registreControleA_ = &TCCR0A;          
        registreControleB_ = &TCCR0B; 
        registreInterruption_ = &TIMSK0 ;        
        break;
    } 
    // case NumeroTimer::TIMER1 :{
    //     compteur_ = &TCNT1 ;
    //     valeurComparaison_ = &OCR1A ; 
    //     registreControle_ = &TCCR1B; 
    //     registreInterruption_ = &TIMSK1 ;        
    //     break;
    // }    
    case NumeroTimer::TIMER2 :{
        compteur_ = &TCNT2 ;
        valeurComparaison_ = &OCR2A ; 
        registreControleA_ = &TCCR2A;          
        registreControleB_ = &TCCR2B;          
        registreInterruption_ = &TIMSK2 ;        
        break;
    }  

    default:
        break;
    }
}

// timer 1 en mode CTC 
// prescaler toujours a  1024 
void Timer::initialiserTimer(void){ 
    cli();
    // initialiser le timer
    *compteur_ = cycleDepart_ ; // le timer commence a compter a partir de ce cycle
    // initialiser le TOP
    *valeurComparaison_ = nCycles_ ; // valeur de comparaison 
    
    //2 - Configure WGM et Clock source


    // timer 0 et 2
    *registreControleA_ |= (1<<WGM01) ;
    *registreControleB_ |= ( (1<<CS02) | (1 << CS00) ) ;
    *registreInterruption_|= (1 << OCIE0A) ;
    
    // timer 1 
    // *registreControle_ |= (1 << WGM12 |1 << CS12 | 1 << CS10) ; 
    // *registreControle_ &= ~(1 << WGM13 | 1 << CS11) ; 
    // // Activation des interruptions lors du compare match event
    // *registreInterruption_ |= (1 <<OCIE1A) ; 


    sei();
}



void Timer::lancerEvenementIntervalle(double intervalle){
    convertirTempsEnCycles(intervalle) ; 
    cycleDepart_ = 0 ;
    initialiserTimer();
} 

const int DUREE_1_UNITE = 1 ; 

void Timer::demarrerChronometre(){
    convertirTempsEnCycles(DUREE_1_UNITE) ; // conversion de 1 sec / ms en cycles 
    cycleDepart_ = 0 ; // commencer au cycle 0 
    initialiserTimer() ;  
}

void Timer::reprendreChronometre(void){
    initialiserTimer(); // relance le timer en commencant par le cycle atteint au dernier arret
}

void Timer::arreterChronometre(){
    cycleDepart_ = *compteur_ ; // sauvegarder la derniere valeur timer
    *registreInterruption_ &= ~(1 <<OCIE1A) ; // arreter les interruptions du timer1 -> le temps ne s'incremente plus
}

void Timer::convertirTempsEnCycles(double duree){
    switch (uniteDeTemps_) 
    {
        // case Unite::SECS :
        //     nCycles_ = freqAvecPrescaler ; // nombre de cycles equivalent a 1 seconde
        //     break;
        case Unite::MS :
            nCycles_ = 8; // nombre de cycles equivalent a 1 ms
            break;            
        default:
            break;
    }  
    nCycles_ = int(nCycles_*duree); // nombre de cycles equivalent a X secondes / ms (max ~8 secondes / ~8000 ms)
}