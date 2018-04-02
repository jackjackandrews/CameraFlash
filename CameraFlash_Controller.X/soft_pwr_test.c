#include <xc.h>
#include <stdio.h>
#include "global_defines.h"
//#include "18f87k22_config_bits.h"
#include "18f8722_config_bits.h"
#include "IO_Buttons.h"
#include "IO_LED.h"
#include "IO_LCD.h"
#include "TMR_SysTick.h"
#include "IO_Encoder.h"
#include "plib/delays.h"

#pragma warning disable 520

void interrupt ISR(void) {
    
    if(TMR_SYSTICK_IF == 1) {
        TMR_SysTick_ISR();
        
        IO_Encoder_ISR();
    }
    
    if(IO_BUTTONS_IF == 1) {
        
        IO_Buttons_ISR();
    }

    
}

void main(void) {
 
    unsigned char count;
    char buff[21];
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 0;
    INTCONbits.GIE = 0;
    
    TMR_SysTick_configure(LP_INTERRUPT);
    IO_Buttons_configureIO(USE_POLLING, LP_INTERRUPT);
    IO_LED_configureIO();
    IO_LCD_configureIO();
    IO_Encoder_configureIO();
    
    TRISBbits.RB0 = 1;
    
    IO_LCD_Init();
    IO_LCD_putrs("<- Shutdown");
    
    Delay10KTCYx(250);
    
    while(1) {
        
        if(PORTBbits.RB0 == 0) {
            
            Delay1KTCYx(25);
            
            if(PORTBbits.RB0 == 0) {
                break;
            }
            
        }
        
        
    }
    
    IO_LCD_ClearDisplay();
    
    for(count = 5; count > 0; count--) {
        sprintf(buff, "Power off in: %ds", count);
        IO_LCD_puts(buff);
        Delay10KTCYx(250);
        
        IO_LCD_SetCursor(1,1);
    }
    
    LATBbits.LATB0 = 0;
    
    TRISBbits.RB0 = 0;
    
    while(1);
    
}
