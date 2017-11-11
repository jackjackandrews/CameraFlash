/* 
 * File:   IO_Encoder.h
 * Author: Jack
 *
 * Created on 11 November 2017, 20:38
 */

#ifndef IO_ENCODER_H
#define	IO_ENCODER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define CCW 0
#define CW 1
    
#define DEC 0
#define INC 1
    
    typedef struct {
        
        unsigned int count;
        bool direction  :1;
        
    } encoder_state_t;
    
    inline void IO_Encoder_ISR(void);

    void IO_Encoder_configureIO(void);
    
    unsigned int IO_Encoder_getCount(void);
    



#ifdef	__cplusplus
}
#endif

#endif	/* IO_ENCODER_H */

