/* 
 * File:   IO_Buttons.h
 * Author: Jack Andrews <jack.andrews@student.manchester.ac.uk>
 * Date: 5/11/2017
 *
 * Description: Header file for IO_Buttons library. Contains function prototypes and defines required for library functions.
 *
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
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
    
#define IO_BUTTONS_IF INTCONbits.RBIF
    
    typedef enum {
    
        PB_1, PB_2, PB_3, PB_4, PB_5, PB_6
    
    } buttons_t;

    typedef struct {

        char PB_1 :1;
        char PB_2 :1;
        char PB_3 :1;
        char PB_4 :1;
        char PB_5 :1;
        char PB_6 :1;       

    } buttons_state_t;
    
    inline void IO_Buttons_ISR(void);
    
    void IO_Buttons_disableInterrupt(void);
    
    void IO_Buttons_enableInterrupt(void);
    
    void IO_Buttons_switchInterruptPriority(bool interrupt_priority);
    
    void IO_Buttons_configureIO(bool use_interrupts, bool interrupt_priority);
    
    bool IO_Buttons_getButton(buttons_t button);
    
    volatile buttons_state_t * IO_Buttons_getAllButtons(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

