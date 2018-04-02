/* 
 * File:   IO_LED.c
 * Author: Jack Andrews <jack.andrews@student.manchester.ac.uk>
 * Date: 6/11/2017
 *
 * Description: C source file for IO_LED library. Library to interface with the LEDs on the User Interface Board, to set and get their states.
 *
 */

#include <xc.h>
#include "global_defines.h"
#include "IO_LED.h"

void IO_LED_configureIO(void) {
    
    LED_TRIS_D_1 = 0;
    LED_TRIS_D_2 = 0;
    LED_TRIS_D_3 = 0;
    LED_TRIS_D_4 = 0;
    
    LED_LAT_D_1 = 1;
    LED_LAT_D_2 = 1;
    LED_LAT_D_3 = 1;
    LED_LAT_D_4 = 1;
    
}

bool IO_LED_getLED(leds_t led) {
    
    switch(led) {
        case D_1:
            return(!LED_LAT_D_1);
            break;
        case D_2:
            return(!LED_LAT_D_2);
            break;
        case D_3:
            return(!LED_LAT_D_3);
            break;
        case D_4:
            return(!LED_LAT_D_4);
            break;
        default:
            break;
        
    }
    
}

void IO_LED_setLED(leds_t led, bool state) {
    
    switch(led) {
        case D_1:
            LED_LAT_D_1 = !state;
            break;
        case D_2:
            LED_LAT_D_2 = !state;
            break;
        case D_3:
            LED_LAT_D_3 = !state;
            break;
        case D_4:
            LED_LAT_D_4 = !state;
            break;
        default:
            break;
        
    } 
    
}