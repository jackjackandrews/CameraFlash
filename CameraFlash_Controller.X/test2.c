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

volatile bool done;

void interrupt ISR(void) {
    
    if(TMR_SYSTICK_IF == 1) {
        TMR_SysTick_ISR();
        
        IO_Encoder_ISR();
    }
    
    if(IO_BUTTONS_IF == 1) {
        
        IO_Buttons_ISR();
    }
    
    if(PIR3bits.CCP3IF) {
        
        PIR3bits.CCP3IF = 0;
        done = TRUE;
    }
    
    
}

void main(void) {
    
    char buff[20];
    unsigned int timer_reg_value = 0;
    float duration_us;
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    PIE3bits.CCP3IE = 1;
    IPR3bits.CCP3IP = 0;
    
    TMR_SysTick_configure(LP_INTERRUPT);
    IO_Buttons_configureIO(USE_POLLING, LP_INTERRUPT);
    IO_LED_configureIO();
    IO_LCD_configureIO();
    IO_Encoder_configureIO();
    
    T3CON = 0b11001000;
    WriteTimer3(0x0000);
    
    CCP3CON = 0b00000000;
    
    IO_LCD_Init();
    IO_LCD_putrs("CCP register: ");
    IO_LCD_SetCursor(2,1);
    IO_LCD_putrs("Length, us: ");
    
    TRISGbits.TRISG0 = 0;
    LATGbits.LATG0 = 1;
    
    IO_LCD_SetCursor(4,1);
    IO_LCD_putrs("UNARMED");
    
    while(1) {
        
        if(IO_Buttons_getButton(PB_1)) {
            
            done = FALSE;
            
            IO_LCD_SetCursor(4,1);
            IO_LCD_putrs("ARMED  ");
            
            CCPR3L = timer_reg_value & 0x00FF;
            CCPR3H = (timer_reg_value >> 8) & 0x00FF;
            
//            CCPR3L = 0xFF;
//            CCPR3H = 0xFF;
            
            while(!IO_Buttons_getButton(PB_4));                
                
                CCP3CON = 0b00001001;
                T3CONbits.TMR3ON = 1;    
            
            while(done == FALSE);
            
            CCP3CON = 0b00000000;
            
            T3CONbits.TMR3ON = 0;
            WriteTimer3(0x0000);
            
            Delay10KTCYx(200);
            
            IO_LCD_SetCursor(4,1);
            IO_LCD_putrs("UNARMED");                     
            
            
        }
        else {
            
            LATGbits.LATG0 = 0;
            
            timer_reg_value += IO_Encoder_getCount();
            
            if(timer_reg_value == 0) {
                timer_reg_value = 65535;
            }
            else if(timer_reg_value > 65535) {
                timer_reg_value = 1;
            }
            
            sprintf(buff, "%-5u", timer_reg_value);
            IO_LCD_SetCursor(1, 15);
            IO_LCD_puts(buff);
            
            duration_us = _TCY * timer_reg_value;
            
            
            sprintf(buff, "%-8.1f", duration_us);
            IO_LCD_SetCursor(2, 13);
            IO_LCD_puts(buff);
            
            Delay10KTCYx(10);

            
        }
        
        
        
        
    }
    
    //stop timer
    //wait for event
    //drive pin high
    //start timer
    //timer match, pin driven low
    //stop timer
    //reload timer
    
    
}
