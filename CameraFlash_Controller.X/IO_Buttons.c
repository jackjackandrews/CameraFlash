#include <xc.h>
#include "global_defines.h"
#include "IO_Buttons.h"

volatile static bool buttons_use_interrupts, buttons_interrupt_priority;
volatile static buttons_state_t button_state_bits;

inline static void scan_buttons(void);
inline static void disable_interrupt(void);
inline static void enable_interrupt(void);

inline void IO_Buttons_ISR(void) {
        
    disable_interrupt();

    scan_buttons();

    enable_interrupt();
    
}

inline static void disable_interrupt(void) {
    
    if(PORTB) {
        asm("nop");
    }
    
    INTCONbits.RBIE = 0;
    INTCONbits.RBIF = 0;
    
}

inline static void enable_interrupt(void) {
    
    if(PORTB) {
        asm("nop");
    }
    
    if(buttons_interrupt_priority == LP_INTERRUPT) {
        INTCON2bits.RBIP = 0;
    }
    
    else if(buttons_interrupt_priority == HP_INTERRUPT) {
        INTCON2bits.RBIP = 1;        
    }
    
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;    
    
}

inline static void scan_buttons(void) {
    
    if(PORTB) {
        asm("nop");
    }
    
    LATDbits.LATD0 = 1;
    LATDbits.LATD1 = 1;
    LATDbits.LATD2 = 1;
    
    LATDbits.LATD0 = 0;
    button_state_bits.PB_1 = !PORTBbits.RB4;
    button_state_bits.PB_2 = !PORTBbits.RB5;
    LATDbits.LATD0 = 1;
    
    LATDbits.LATD1 = 0;
    button_state_bits.PB_3 = !PORTBbits.RB4;
    button_state_bits.PB_4 = !PORTBbits.RB5;
    LATDbits.LATD1 = 1;
    
    LATDbits.LATD2 = 0;
    button_state_bits.PB_5 = !PORTBbits.RB4;
    button_state_bits.PB_6 = !PORTBbits.RB5;
    LATDbits.LATD2 = 1;
    
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
    
}

void IO_Buttons_disableInterrupt(void) {
    
    buttons_use_interrupts = FALSE;
    
    disable_interrupt();
    
}

void IO_Buttons_enableInterrupt(void) {
    
    buttons_use_interrupts = TRUE;
    
    enable_interrupt();
    
}

void IO_Buttons_switchInterruptPriority(bool interrupt_priority) {
    
    buttons_interrupt_priority = interrupt_priority;
    
    disable_interrupt();
    
    enable_interrupt();
    
}

void IO_Buttons_configure(bool use_interrupts, bool interrupt_priority) {
    
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB5 = 1;
    
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
    
    INTCON2bits.nRBPU = 0;
    
    if(use_interrupts == TRUE) {
       enable_interrupt();
    }
    
    else if(use_interrupts == FALSE) {
        disable_interrupt();
    }
    
    buttons_use_interrupts = use_interrupts;
    buttons_interrupt_priority = interrupt_priority;
    
    
}

bool IO_Buttons_getButton(buttons_t button) {
    
    if(buttons_use_interrupts == FALSE) {
        scan_buttons();
    }
    
    switch(button) {
        case PB_1:
            return(button_state_bits.PB_1);
        case PB_2:
            return(button_state_bits.PB_2);
        case PB_3:
            return(button_state_bits.PB_3);
        case PB_4:
            return(button_state_bits.PB_4);
        case PB_5:
            return(button_state_bits.PB_5);
        case PB_6:
            return(button_state_bits.PB_6);
        default:
            break;       
    }
    
}

volatile buttons_state_t * IO_Buttons_getAllButtons(void) {
    
    if(buttons_use_interrupts == FALSE) {
        scan_buttons();
    }
    
    return(&button_state_bits);
    
}