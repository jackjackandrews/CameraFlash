#include <xc.h>
#include "global_defines.h"
#include "IO_LED.h"

void IO_LED_configureIO(void) {
    
    TRISHbits.TRISH0 = 0;
    TRISHbits.TRISH1 = 0;
    TRISHbits.TRISH2 = 0;
    TRISHbits.TRISH3 = 0;
    
    LATHbits.LATH0 = 1;
    LATHbits.LATH1 = 1;
    LATHbits.LATH2 = 1;
    LATHbits.LATH3 = 1;
    
}

bool IO_LED_getLED(leds_t led) {
    
    switch(led) {
        case D_1:
            return(!LATHbits.LATH0);
            break;
        case D_2:
            return(!LATHbits.LATH1);
            break;
        case D_3:
            return(!LATHbits.LATH2);
            break;
        case D_4:
            return(!LATHbits.LATH3);
            break;
        default:
            break;
        
    }
    
}

void IO_LED_setLED(leds_t led, bool state) {
    
    switch(led) {
        case D_1:
            LATHbits.LATH0 = !state;
            break;
        case D_2:
            LATHbits.LATH1 = !state;
            break;
        case D_3:
            LATHbits.LATH2 = !state;
            break;
        case D_4:
            LATHbits.LATH3 = !state;
            break;
        default:
            break;
        
    } 
    
}