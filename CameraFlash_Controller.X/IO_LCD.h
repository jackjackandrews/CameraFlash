/* 
 * File:   IO_LCD.h
 * Author: Jack
 *
 * Created on 10 November 2017, 22:55
 */

#ifndef IO_LCD_H
#define	IO_LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define SHIFT_LEFT 0
#define SHIFT_RIGHT 1
    
    typedef struct {
        
        char DDRAM_addr;
        char CGRAM_addr;
        bool display_on :1;
        bool cursor_on  :1;
        bool blink_on   :1;
        bool scroll_on  :1;
        
    } lcd_state_t;
    
    void IO_LCD_Init(void);
    
    void IO_LCD_WriteChar(char character);




#ifdef	__cplusplus
}
#endif

#endif	/* IO_LCD_H */

