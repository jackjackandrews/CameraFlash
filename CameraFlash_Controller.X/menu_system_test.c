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
unsigned int timer_reg_value = 1;

typedef enum {
        PULSE, 
        PWM,
        NONE
    } modes_t;

    modes_t current_mode;
    
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



void mode_PULSE(void) {
    
    char buff[20];
    
    float duration_us;
    
    IO_LCD_ClearDisplay();
    
    IO_LCD_SetCursor(4, 1);
    IO_LCD_putrs("< Exit");
    
    IO_LCD_SetCursor(1, 1);
    IO_LCD_putrs("CCP register: ");
    
    IO_LCD_SetCursor(2,1);
    IO_LCD_putrs("Length, us: ");
    
    IO_LCD_SetCursor(3,1);
    IO_LCD_putrs("DISARMED");
    
    IO_LCD_SetCursor(4, 16);
    IO_LCD_putrs("Arm >");
    
    T3CON = 0b11001000;
    WriteTimer3(0x0000);
    
    CCP3CON = 0x00;
    
    TRISGbits.TRISG0 = 0; 
    LATGbits.LATG0 = 0;
    
    while(IO_Buttons_getButton(PB_5) == 0) {
        
       
            
        if(IO_Buttons_getButton(PB_6)) {

            timer_reg_value += IO_Encoder_getCount() * 200;

        }
        else {
            timer_reg_value += IO_Encoder_getCount();
        }


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
            
        
        if(IO_Buttons_getButton(PB_4) == 1) {
            
            done = FALSE;

            IO_LCD_SetCursor(3,1);
            IO_LCD_putrs("ARMED   ");

            CCPR3L = timer_reg_value & 0x00FF;
            CCPR3H = (timer_reg_value >> 8) & 0x00FF;

            IO_LCD_SetCursor(4, 15);
            IO_LCD_putrs("Fire >");

            Delay10KTCYx(50);

            while(!IO_Buttons_getButton(PB_4));                

                CCP3CON = 0b00001001;
                T3CONbits.TMR3ON = 1;    

            while(done == FALSE);

            CCP3CON = 0b00000000;

            T3CONbits.TMR3ON = 0;
            WriteTimer3(0x0000);

            Delay10KTCYx(200);

            IO_LCD_SetCursor(3,1);
            IO_LCD_putrs("DISARMED");

            IO_LCD_SetCursor(4, 15);
            IO_LCD_putrs(" Arm >");
        }
        
        
    }
    
}

void mode_PWM(void) {
    
    IO_LCD_ClearDisplay();
    
    IO_LCD_SetCursor(4, 1);
    IO_LCD_putrs("< Exit");
    
    while(IO_Buttons_getButton(PB_5) == 0) {
        
        
    }
    
}

modes_t modeSelector(void) {
    
    IO_LCD_ClearDisplay();
    
    IO_LCD_putrs("Select Mode:");
    
    IO_LCD_SetCursor(2, 4);
    IO_LCD_putrs("Pulse Generator >");
    
    IO_LCD_SetCursor(3, 6);
    IO_LCD_putrs("PWM Generator >");
    
    while(1) {
        
        if(IO_Buttons_getButton(PB_2)) {
            current_mode = PULSE;
            break;
        }
        
        if(IO_Buttons_getButton(PB_3)) {
            current_mode = PWM;
            break;
        }      
        
    }
    
}

void modeSwitcher(modes_t mode) {
    
    switch(mode) {
        case PULSE:
            mode_PULSE();
            break;
        case PWM:
            mode_PWM();
            break;            
    }
    
}

void main(void) {
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    PIE3bits.CCP3IE = 1;
    IPR3bits.CCP3IP = 0;
    
    TMR_SysTick_configure(LP_INTERRUPT);
    IO_Buttons_configureIO(USE_INTERRUPTS, LP_INTERRUPT);
    IO_LED_configureIO();
    IO_LCD_configureIO();
    IO_Encoder_configureIO();
    
    IO_LCD_Init();
    
    IO_LCD_putrs("uFlash Exerciser");
    Delay10KTCYx(250);
    
    while(1) {
        modeSwitcher(modeSelector());
    }
    
    
    
}
