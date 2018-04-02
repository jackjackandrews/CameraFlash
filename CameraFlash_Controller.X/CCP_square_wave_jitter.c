#include <xc.h>
#include <stdio.h>
#include "global_defines.h"
#include "18f8722_config_bits_HSPLL.h"
#include "plib/timers.h"

#define PERIOD  2

void interrupt ISR(void) {
    
    if(PIR3bits.CCP3IF) {
        
        PIR3bits.CCP3IF = 0;

        TMR3L = 0x00;
        TMR3H = 0x00;
       
    }
    
    
}

void main(void) {
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    PIR3bits.CCP3IF = 0;
    PIE3bits.CCP3IE = 1;
    
    COBLED_IN_LAT = 0;
    COBLED_IN_TRIS = 0;
    
    T3CON = 0b11100000;
    WriteTimer3(0x0000);
    
    CCP3CON = 0b00000010;
    
    CCPR3L = PERIOD & 0x00FF;
    CCPR3H = (PERIOD >> 8) & 0x00FF;
    
    T3CONbits.TMR3ON = 1;  
    
    while(1);
    
    
}
