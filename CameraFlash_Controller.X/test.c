#include <xc.h>
#include "global_defines.h"
//#include "18f87k22_config_bits.h"
#include "18f8722_config_bits.h"
#include "IO_Buttons.h"
#include "IO_LED.h"
#include "IO_LCD.h"
#include "TMR_SysTick.h"



void interrupt ISR(void) {
    
    if(TMR_SYSTICK_IF == 1) {
        TMR_SysTick_ISR();
    }
    
    
}

void main(void) {
    
    unsigned int count;
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 0;
    INTCONbits.GIE = 1;
    
    TMR_SysTick_configure(LP_INTERRUPT);
    IO_LED_configure();
    
    TRISJ = 0x0F;
    TRISHbits.TRISH6 = 0;
    TRISHbits.TRISH7 = 0;
    
    IO_LCD_Init();
    
    IO_LCD_WriteChar('h');
    
    while(1) {
        
        
        
    }
    
    
}