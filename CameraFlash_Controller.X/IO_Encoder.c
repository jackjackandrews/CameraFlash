/* 
 * File:   IO_Encoder.c
 * Author: Jack Andrews <jack.andrews@student.manchester.ac.uk>
 * Date: 11/11/2017
 *
 * Description: C source file for IO_Encoder library. Library to interface with rotary encoder on User Interface Board.
 *              Updates encoder count in a timer interrupt, which must be configured/provided, and IO_Encoder_ISR() must be planted in ISR for it to work.
 */

#include <xc.h>
#include "global_defines.h"
#include "IO_Encoder.h"

volatile static char enc_A, enc_B, enc_A_prev;
volatile static encoder_state_t enc_state;

inline void IO_Encoder_ISR(void) {
    
    enc_A = ENCODER_PORT_A;
    enc_B = ENCODER_PORT_B;

    if(!enc_A && enc_A_prev){

        // A has gone from high to low
        if(enc_B) {
            // B is high so clockwise
                enc_state.count++;
                enc_state.direction = INC;
        }
        else {
            // B is low so counter-clockwise            
                enc_state.count--;
                enc_state.direction = DEC;
        }    
    }  
    
    enc_A_prev = enc_A;
    
}

void IO_Encoder_configureIO(void) {
    
    enc_A = 0;
    enc_B = 0;
    enc_A_prev = 0;
    enc_state.count = 0;
    enc_state.direction = INC;
    
    ENCODER_TRIS_A = 1;
    ENCODER_TRIS_B = 1;
    
}

unsigned int IO_Encoder_getCount(void) {
    
    unsigned int count = enc_state.count;
    
    enc_state.count = 0;
    return(count);
    
}

bool IO_Encoder_getDirection(void) {
    
    return(enc_state.direction);
    
}

volatile static encoder_state_t * IO_Encoder_getState(void) {
    
    return(&enc_state);
    
}
