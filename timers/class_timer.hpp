#define F_CPU 8000000UL // 8 MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum class Unite
{
    SECS,
    MS
};

// objet qui compte en secondes par defaut
class Timer
{
    public:
        Timer(Unite uniteDeTemps = Unite::SECS); // constructeur
        int obtenirTemps(void);
        void demarrerTimer(void); 
        void reprendreTimer(void);
        void arreterTimer(void);        
    private:
        Unite uniteDeTemps_ ;
        uint16_t nCycles_ ; // frequence de variation du timer
        uint16_t cycleDepart_ ;
        void initialiserTimer(void); // lancer le timer a partir de cycleDepart_ 

};

