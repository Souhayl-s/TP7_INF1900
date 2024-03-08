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

// objet qui compte en secondes par defaut
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
        uint8_t nCycles_ ; // frequence de variation du timer // template
        uint8_t cycleDepart_ ; // template

        volatile uint8_t* compteur_ ;  // template
        volatile uint8_t* valeurComparaison_ ; ; // template

        volatile uint8_t* registreControleA_  ; 
        volatile uint8_t* registreControleB_  ; 
        volatile uint8_t* registreInterruption_  ;        

        void initialiserTimer(void); // lancer le timer a partir de cycleDepart_ 
        void convertirTempsEnCycles(double duree); // convertir la duree et l'unite de temps -> en nombre de cycles (voir frequence prescaler)
};

