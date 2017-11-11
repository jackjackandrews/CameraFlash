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
    
#define SHIFT_CURSOR 0
#define SHIFT_DISPLAY 1
    
#define DECREMENT 0
#define INCREMENT 1
    
    typedef struct {
        
        char DDRAM_addr;
        char CGRAM_addr;
        bool display_on :1;
        bool cursor_on  :1;
        bool blink_on   :1;
        
    } lcd_state_t;
    
    void IO_LCD_configureIO(void);
    
    void IO_LCD_Init(void);
    
    void IO_LCD_ClearDisplay(void);
    
    void IO_LCD_putc(char character);
    
    void IO_LCD_putrc(const char character);
    
    void IO_LCD_puts(char *str);
    
    void IO_LCD_putrs(const char *str);
    
    void IO_LCD_SetCursor(char row, char col);
    
    void IO_LCD_EnableCursor(void);
    
    void IO_LCD_DisableCursor(void);
    
    void IO_LCD_EnableDisplay(void);
    
    void IO_LCD_DisableDisplay(void);
    
    void IO_LCD_EnableBlink(void);
    
    void IO_LCD_DisableBlink(void);
    
    void IO_LCD_SetEntryMode(bool inc_dec, bool disp_shift);
    
    void IO_LCD_ShiftCursor(bool direction);
    
    void IO_LCD_ShiftDisplay(bool direction);




#ifdef	__cplusplus
}
#endif

#endif	/* IO_LCD_H */

