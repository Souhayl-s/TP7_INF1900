#define F_CPU 8000000UL // 8 MHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum class Broche
{
    B2,D2,D3
};

enum class ConditionInterruption
{
    FRONT,MONTANT,DESCENDANT,BAS_NIVEAU // FRONT = lancement d'un ISR au front montant et au front descendant
};

class InterruptionExterne{
    public:
        InterruptionExterne(Broche broche, ConditionInterruption conditionclock){
            broche_ = broche ; 
            conditionClock_ = conditionclock ;
        } 
        void desactiverInterruptionExterne(void) ; // prend une broche et un mode en particulier
        void activerInterruptionExterne(void) ; // prend une broche et un mode en particulier
    private : 
        Broche broche_ ;
        ConditionInterruption conditionClock_ ;
        void configurerPort(void) ; // regler la direction du port et le rendre sensible aux interruptions
        void configurerConditionInterruption(void) ; // fixer si l'ISR est appelee au front montant, descendant ...
};
