/* 
 * File:   IO_LED.h
 * Author: Jack Andrews <jack.andrews@student.manchester.ac.uk>
 * Date: 6/11/2017
 *
 * Description: Header file for IO_LED library. Contains function prototypes and defines required for library functions.
 *
 */

#ifndef IO_LED_H
#define	IO_LED_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum {
        
        D_1, D_2, D_3, D_4
        
    } leds_t;
    
    void IO_LED_configureIO(void);
    
    bool IO_LED_getLED(leds_t led);
    
    void IO_LED_setLED(leds_t led, bool state);
    
#ifdef	__cplusplus
}
#endif

#endif	/* IO_LED_H */

