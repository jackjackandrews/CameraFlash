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
    
    
}

void main(void) {
    
    unsigned int count = 0;
    char buff[20];
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 0;
    INTCONbits.GIE = 1;
    
    TMR_SysTick_configure(LP_INTERRUPT);
    IO_LED_configureIO();
    IO_LCD_configureIO();
    IO_Encoder_configureIO();
    
    IO_LCD_Init();
    
    IO_LCD_putrs("George has ");
    IO_LCD_SetCursor(2, 1);
    IO_LCD_putrs("friends");
    IO_LCD_SetCursor(1, 12);
    
    while(1){
        
        count += IO_Encoder_getCount();
        sprintf(buff, "%-5d", count);
        IO_LCD_puts(buff);
        
        Delay10KTCYx(10);
        
        IO_LCD_SetCursor(1, 12);       
   
    }
    
    
}