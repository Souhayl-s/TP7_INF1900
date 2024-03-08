#define F_CPU 8000000UL // 8 MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum class Unite
{
    SECS,
    MS
};


enum class NumeroTimer
{
    TIMER0,
    TIMER1,
    TIMER2
};

const unsigned long int freqCPU = 8'000'000 ;
const unsigned  int prescaler = 1024 ;
const unsigned long int freqAvecPrescaler = freqCPU / prescaler ; // = frequence du timer
const uint16_t SECTOMS = 1000 ; 
const int DUREE_1_UNITE = 1 ; 


// TIMER 1 : secondes et millisecondes possibles
// TIMER 0 / TIMER 2 : millisecondes possibles uniquement

class Timer
{
    public:
        Timer(NumeroTimer numeroTimer, Unite uniteDeTemps);         
        Unite getUniteTemps(){return uniteDeTemps_ ;}        
        void setUniteTemps(Unite nouvelleUniteTemps){ uniteDeTemps_ = nouvelleUniteTemps ; }
        

        void demarrerChronometre(void); 
        virtual void arreterChronometre(void); 
        void reprendreChronometre(void);

        // timer 16 bits : max 8s / max 8000ms
        // timers 8 bits : max 36 ms
        void lancerEvenementIntervalle(double intervalle);  

        friend class Timer8Bits ;
        friend class Timer16Bits ;

    private:
        Unite uniteDeTemps_ ;
        NumeroTimer numeroTimer_ ; 
        int nCycles_ ; 
        int cycleDepart_ ; 
        volatile uint8_t* registreControleA_  ; 
        volatile uint8_t* registreControleB_  ; 
        volatile uint8_t* registreInterruption_  ;   

        virtual void initialiserTimer(void); // lancer le timer a partir de cycleDepart_         
        void convertirTempsEnCycles(double duree); // convertir la duree et l'unite de temps -> en nombre de cycles (voir frequence prescaler)
};

class Timer8Bits : public Timer {
    public :
        Timer8Bits(NumeroTimer numeroTimer , Unite uniteDeTemps) ;
        void arreterChronometre(void);         
    private : 
        void initialiserTimer(void); // lancer le timer a partir de cycleDepart_ 
        volatile uint8_t* compteur_ ;  
        volatile uint8_t* valeurComparaison_ ; 
} ;



class Timer16Bits : public Timer {
    public :
        Timer16Bits(NumeroTimer numeroTimer , Unite uniteDeTemps) ;
        void arreterChronometre(void);         
    private : 
        void initialiserTimer(void); // lancer le timer a partir de cycleDepart_ 
        volatile uint16_t* compteur_ ;  
        volatile uint16_t* valeurComparaison_ ;
} ;