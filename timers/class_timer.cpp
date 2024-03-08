#include "class_timer.hpp"

volatile int gTempsActuel = 0 ; 

const unsigned long int freqCPU = 8'000'000 ;
const unsigned  int prescaler = 1024 ;
const unsigned long int freqAvecPrescaler = freqCPU / prescaler ; // = frequence du timer
const uint16_t SECTOMS = 1000 ; 

// constructeur surcharge


Timer::Timer(NumeroTimer numeroTimer , Unite uniteDeTemps):
    uniteDeTemps_(uniteDeTemps),
    numeroTimer_ (numeroTimer),
    cycleDepart_(0) // compte a partir de 0 par defaut
{
    switch (numeroTimer_)
    {
        case NumeroTimer::TIMER0 :
            compteur8bits_ = &TCNT0 ;
            valeurComparaison8bits_ = &OCR0A ;
            registreControleA_ = &TCCR0A;          
            registreControleB_ = &TCCR0B; 
            registreInterruption_ = &TIMSK0 ;        
            break;
        
        case NumeroTimer::TIMER1 :
            registreControleB_= &TCCR1B; 
            registreInterruption_ = &TIMSK1 ;        
            break;
        
        case NumeroTimer::TIMER2 :
            compteur8bits_ = &TCNT2 ;
            valeurComparaison8bits_ = &OCR2A ; 
            registreControleA_ = &TCCR2A;          
            registreControleB_ = &TCCR2B;          
            registreInterruption_ = &TIMSK2 ;        
            break;
        

        default:
            break;
    }
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

    else{ // timer0 ou timer2
        *compteur8bits_ = cycleDepart_ ; 
        *valeurComparaison8bits_ = nCycles_ ; // valeur de comparaison 
        *registreControleA_ |= (1<<WGM01) ;

        if(numeroTimer_ == NumeroTimer::TIMER0){
            *registreControleB_ |= ( (1<<CS02)  | (1 << CS00) ) ;
        }
        else{
            *registreControleB_ |= ( (1<<CS22) | (1 << CS21) | (1 << CS20) ) ;
        }
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
    
    if (numeroTimer_ == NumeroTimer::TIMER1){
        cycleDepart_ = TCNT1; // sauvegarder la derniere valeur timer
    }
    else{ // Timer 0 ou Timer 2
        cycleDepart_ = *compteur8bits_ ;
    }
    

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