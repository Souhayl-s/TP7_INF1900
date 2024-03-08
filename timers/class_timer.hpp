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


// TIMER 1 : secondes et millisecondes possibles
// TIMER 0 / TIMER 2 : millisecondes possibles uniquement


class Timer
{
    public:
        // Timer(NumeroTimer numeroTimer); 
        Timer(NumeroTimer numeroTimer, Unite uniteDeTemps);         
        // getters / setters 
        Unite getUniteTemps(){return uniteDeTemps_ ;}        
        void setUniteTemps(Unite nouvelleUniteTemps){ uniteDeTemps_ = nouvelleUniteTemps ; }

        void lancerEvenementIntervalle(double intervalle);
        void demarrerChronometre(void); 
        void reprendreChronometre(void);
        void arreterChronometre(void); 

    private:
        Unite uniteDeTemps_ ;
        NumeroTimer numeroTimer_ ; 
        int nCycles_ ; // frequence de variation du timer /
        int cycleDepart_ ; 

        volatile uint8_t* compteur8bits_ ;  
        volatile uint8_t* valeurComparaison8bits_ ; ; 

        volatile uint8_t* registreControleA_  ; 
        volatile uint8_t* registreControleB_  ; 
        volatile uint8_t* registreInterruption_  ;        

        void initialiserTimer(void); // lancer le timer a partir de cycleDepart_ 
        void convertirTempsEnCycles(double duree); // convertir la duree et l'unite de temps -> en nombre de cycles (voir frequence prescaler)
};

