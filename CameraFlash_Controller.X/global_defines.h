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

#define _XTAL_FREQ 10000000


typedef char bool;

#define LCD_TRIS_D7 TRISJbits.TRISJ7
#define LCD_TRIS_D6 TRISJbits.TRISJ6
#define LCD_TRIS_D5 TRISJbits.TRISJ5
#define LCD_TRIS_D4 TRISJbits.TRISJ4
#define LCD_TRIS_D3 TRISJbits.TRISJ3
#define LCD_TRIS_D2 TRISJbits.TRISJ2
#define LCD_TRIS_D1 TRISJbits.TRISJ1
#define LCD_TRIS_D0 TRISJbits.TRISJ0

#define LCD_TRIS_EN TRISHbits.TRISH6
#define LCD_TRIS_RS TRISHbits.TRISH7

#define LCD_LAT_D7 LATJbits.LATJ7
#define LCD_LAT_D6 LATJbits.LATJ6
#define LCD_LAT_D5 LATJbits.LATJ5
#define LCD_LAT_D4 LATJbits.LATJ4
#define LCD_LAT_D3 LATJbits.LATJ3
#define LCD_LAT_D2 LATJbits.LATJ2
#define LCD_LAT_D1 LATJbits.LATJ1
#define LCD_LAT_D0 LATJbits.LATJ0

#define LCD_LAT_EN LATHbits.LATH6
#define LCD_LAT_RS LATHbits.LATH7

#define LCD_MODE_4BIT

#define ENCODER_TRIS_A  TRISGbits.TRISG3
#define ENCODER_TRIS_B  TRISGbits.TRISG4

#define ENCODER_PORT_A  PORTGbits.RG3
#define ENCODER_PORT_B  PORTGbits.RG4


    


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_DEFINES_H */

