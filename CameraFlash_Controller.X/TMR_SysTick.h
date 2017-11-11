/* 
 * File:   TMR_SysTick.h
 * Author: Jack
 *
 * Created on 10 November 2017, 18:56
 */

#ifndef TMR_SYSTICK_H
#define	TMR_SYSTICK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifndef TRUE
    #define TRUE    1
#endif

#ifndef FALSE
    #define FALSE   0
#endif

#ifndef USE_INTERRUPTS    
    #define USE_INTERRUPTS 1
#endif
#ifndef USE_POLLING
    #define USE_POLLING 0
#endif

#ifndef LP_INTERRUPT    
    #define LP_INTERRUPT 0
#endif
#ifndef HP_INTERRUPT
    #define HP_INTERRUPT 1
#endif

#define FOSC_KHZ _XTAL_FREQ / 1000
#define TMR_SYSTICK_IF INTCONbits.TMR0IF

    extern volatile unsigned int counter;
    
    inline void TMR_SysTick_ISR(void);
    
    void TMR_SysTick_enableInterrupt(void);
    
    void TMR_SysTick_disableInterrupt(void);
    
    void TMR_SysTick_switchInterruptPriority(bool interrupt_priority);
    
    void TMR_SysTick_configure(bool interrupt_priority);
    
    void TMR_SysTick_stopTimer(void);

    void TMR_SysTick_startTimer(void);

    void TMR_SysTick_resetCounter(void);

    unsigned int TMR_SysTick_getCounter(void);

    void TMR_SysTick_setCounter(unsigned int value);



#ifdef	__cplusplus
}
#endif

#endif	/* TMR_SYSTICK_H */

