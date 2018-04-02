/* 
 * File:   global_defines.h
 * Author: Jack
 *
 * Created on 05 November 2017, 18:41
 */

#ifndef GLOBAL_DEFINES_H
#define	GLOBAL_DEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif


#ifndef TRUE
    #define TRUE    1
#endif

#ifndef FALSE
    #define FALSE   0
#endif

#define _XTAL_FREQ 40000000     //Crystal frequency for xc8 delay routines


typedef char bool;

//LCD TRIS and LAT bits
#define LCD_TRIS_D7 TRISJbits.TRISJ7
#define LCD_TRIS_D6 TRISJbits.TRISJ6
#define LCD_TRIS_D5 TRISJbits.TRISJ5
#define LCD_TRIS_D4 TRISJbits.TRISJ4

#define LCD_TRIS_EN TRISJbits.TRISJ2
#define LCD_TRIS_RS TRISJbits.TRISJ3

#define LCD_LAT_D7 LATJbits.LATJ7
#define LCD_LAT_D6 LATJbits.LATJ6
#define LCD_LAT_D5 LATJbits.LATJ5
#define LCD_LAT_D4 LATJbits.LATJ4

#define LCD_LAT_EN LATJbits.LATJ2
#define LCD_LAT_RS LATJbits.LATJ3

#define LCD_MODE_4BIT

//Encoder TRIS and PORT bits
#define ENCODER_TRIS_A  TRISBbits.TRISB1
#define ENCODER_TRIS_B  TRISJbits.TRISJ0

#define ENCODER_PORT_A  PORTBbits.RB1
#define ENCODER_PORT_B  PORTJbits.RJ0

//User interface LED TRIS and PORT bits
#define LED_TRIS_D_1    TRISHbits.TRISH0
#define LED_TRIS_D_2    TRISHbits.TRISH1
#define LED_TRIS_D_3    TRISHbits.TRISH2
#define LED_TRIS_D_4    TRISHbits.TRISH3

#define LED_LAT_D_1    LATHbits.LATH0
#define LED_LAT_D_2    LATHbits.LATH1
#define LED_LAT_D_3    LATHbits.LATH2
#define LED_LAT_D_4    LATHbits.LATH3

#define DISCHARGE_FET_TRIS  TRISGbits.TRISG4
#define DISCHARGE_FET_LAT   LATGbits.LATG4

#define CHARGE_FET_TRIS     TRISGbits.TRISG3
#define CHARGE_FET_LAT      LATGbits.LATG3

#define COBLED_EN_TRIS     TRISDbits.TRISD3
#define COBLED_EN_LAT      LATDbits.LATD3 

#define COBLED_IN_TRIS     TRISGbits.TRISG0
#define COBLED_IN_LAT      LATGbits.LATG0 

#define VMON_LED_TRIS   TRISFbits.TRISF0

#define VMON_CAP_TRIS   TRISFbits.TRISF1

#define LED_MOD_DETECT_TRIS TRISBbits.TRISB2
#define LED_MOD_DETECT_PORT PORTBbits.RB2

#define TRIG_IN_TRIS    TRISCbits.TRISC2
#define TRIG_IN_PORT    PORTCbits.RC2

#define TRIG_OUT_TRIS   TRISEbits.TRISE7
#define TRIG_OUT_LAT    LATEbits.LATE7


  


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_DEFINES_H */

