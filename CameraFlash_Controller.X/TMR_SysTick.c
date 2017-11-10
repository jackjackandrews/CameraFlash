#include <xc.h>
#include "plib/timers.h"
#include "global_defines.h"
#include "TMR_SysTick.h"

volatile static bool systick_interrupt_priority;
volatile unsigned int counter, systick_tmr_reload;

static inline void reload_timer(void);

inline void TMR_SysTick_ISR(void) {
    
    INTCONbits.TMR0IF = 0;

    counter++;

    reload_timer();
    
}

static inline void start_timer(void) {
    
    T0CONbits.TMR0ON = 1;
    
}

static inline void stop_timer(void) {
    
    T0CONbits.TMR0ON = 0;
    
}

static inline void reload_timer(void) {
    
    WriteTimer0(systick_tmr_reload);
    
}

static void disable_interrupt(void) {
    
    INTCONbits.TMR0IE = 0;
    INTCONbits.TMR0IF = 0;
    
}

static void enable_interrupt(void) {
    
    if(systick_interrupt_priority == LP_INTERRUPT) {
        INTCON2bits.TMR0IP = 0;
    }
    
    else if(systick_interrupt_priority == HP_INTERRUPT) {
        INTCON2bits.TMR0IP = 1;        
    }
    
    reload_timer();
    
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    
    
}

void TMR_SysTick_disableInterrupt(void) {
    
    disable_interrupt();    
    
}

void TMR_SysTick_enableInterrupt(void) {
    
    enable_interrupt();   
    
}

void TMR_SysTick_switchInterruptPriority(bool interrupt_priority) {
    
    systick_interrupt_priority = interrupt_priority;
    
    disable_interrupt();
    
    enable_interrupt();
    
}

void TMR_SysTick_configure(bool interrupt_priority) {
    
    T0CON = 0x08;   //Configure Timer0 as 16-bit, internal clock source, prescaler disabled, but don't turn it on yet
    TMR0H = 0;      //Clear timer registers
    TMR0L = 0;
    
    systick_tmr_reload = 65535 - (FOSC_KHZ / 4);
    
    reload_timer();
    
    systick_interrupt_priority = interrupt_priority;
    
    enable_interrupt();       
    
    start_timer();
    
}

void TMR_SysTick_stopTimer(void) {
    
    stop_timer();
    
}

void TMR_SysTick_startTimer(void) {
    
    start_timer();
    
}

void TMR_SysTick_resetCounter(void) {
    
    counter = 0;
    
    reload_timer();
    
}

unsigned int TMR_SysTick_getCounter(void) {
    
    return(counter);
    
}

void TMR_SysTick_setCounter(unsigned int value) {
    
    counter = value;
    
    reload_timer();
    
}
