/* 
 * File:   IO_LCD.c
 * Author: Jack Andrews <jack.andrews@student.manchester.ac.uk>
 * Date: 10/11/2017
 *
 * Description: C source file for IO_LCD library. Contains functions to send commands and write data to a Hitachi HD44780 (or compatible) character LCD over a 4/8-bit parallel interface, write access only. 
 *
 */

#include <xc.h>
#include "global_defines.h"
#include "IO_LCD.h"

lcd_state_t lcd_state;

static void write_port(char data) {
    
#ifdef LCD_MODE_8BIT
    
    LCD_LAT_D7 = (data >> 7) & 0x01;
    LCD_LAT_D6 = (data >> 6) & 0x01;
    LCD_LAT_D5 = (data >> 5) & 0x01;
    LCD_LAT_D4 = (data >> 4) & 0x01;
    LCD_LAT_D3 = (data >> 3) & 0x01;
    LCD_LAT_D2 = (data >> 2) & 0x01;
    LCD_LAT_D1 = (data >> 1) & 0x01;
    LCD_LAT_D0 = data & 0x01;
    
#endif
    
#ifdef LCD_MODE_4BIT
    
    LCD_LAT_D7 = (data >> 3) & 0x01;
    LCD_LAT_D6 = (data >> 2) & 0x01;
    LCD_LAT_D5 = (data >> 1) & 0x01;
    LCD_LAT_D4 = data & 0x01;
    
#endif 
    
}

static void write_cmd(char cmd) {
    
    LCD_LAT_RS = 0;
    
#ifdef LCD_MODE_8BIT

    LCD_LAT_D7 = (cmd >> 7) & 0x01;
    LCD_LAT_D6 = (cmd >> 6) & 0x01;
    LCD_LAT_D5 = (cmd >> 5) & 0x01;
    LCD_LAT_D4 = (cmd >> 4) & 0x01;
    LCD_LAT_D3 = (cmd >> 3) & 0x01;
    LCD_LAT_D2 = (cmd >> 2) & 0x01;
    LCD_LAT_D1 = (cmd >> 1) & 0x01;
    LCD_LAT_D0 = cmd & 0x01;
    
    LCD_LAT_EN = 1;
    
    __delay_us(20);
    
    LCD_LAT_EN = 0;
    
    __delay_us(20);   
    
#endif
    
#ifdef LCD_MODE_4BIT
    
    LCD_LAT_D7 = (cmd >> 7) & 0x01;
    LCD_LAT_D6 = (cmd >> 6) & 0x01;
    LCD_LAT_D5 = (cmd >> 5) & 0x01;
    LCD_LAT_D4 = (cmd >> 4) & 0x01;
    
    LCD_LAT_EN = 1;
    __delay_us(20);
    LCD_LAT_EN = 0;
    __delay_us(20); 
    
    LCD_LAT_D7 = (cmd >> 3) & 0x01;
    LCD_LAT_D6 = (cmd >> 2) & 0x01;
    LCD_LAT_D5 = (cmd >> 1) & 0x01;
    LCD_LAT_D4 = cmd & 0x01;
    
    LCD_LAT_EN = 1;
    __delay_us(20);
    LCD_LAT_EN = 0;
    __delay_us(20); 
    
#endif
   
}

static void write_data(char data) {
    
    LCD_LAT_RS = 1;
    
#ifdef LCD_MODE_8BIT
    
    LCD_LAT_D7 = (data >> 7) & 0x01;
    LCD_LAT_D6 = (data >> 6) & 0x01;
    LCD_LAT_D5 = (data >> 5) & 0x01;
    LCD_LAT_D4 = (data >> 4) & 0x01;
    LCD_LAT_D3 = (data >> 3) & 0x01;
    LCD_LAT_D2 = (data >> 2) & 0x01;
    LCD_LAT_D1 = (data >> 1) & 0x01;
    LCD_LAT_D0 = data & 0x01;
    
    LCD_LAT_EN = 1;
    
    __delay_us(20);
    
    LCD_LAT_EN = 0;
    
    __delay_us(20);   
    
#endif
    
#ifdef LCD_MODE_4BIT
    
    LCD_LAT_D7 = (data >> 7) & 0x01;
    LCD_LAT_D6 = (data >> 6) & 0x01;
    LCD_LAT_D5 = (data >> 5) & 0x01;
    LCD_LAT_D4 = (data >> 4) & 0x01;
    
    LCD_LAT_EN = 1;
    __delay_us(20);
    LCD_LAT_EN = 0;
    
    __delay_us(20); 
    
    LCD_LAT_D7 = (data >> 3) & 0x01;
    LCD_LAT_D6 = (data >> 2) & 0x01;
    LCD_LAT_D5 = (data >> 1) & 0x01;
    LCD_LAT_D4 = data & 0x01;
    
    LCD_LAT_EN = 1;
    __delay_us(20);
    LCD_LAT_EN = 0;
    
    __delay_us(20); 
    
#endif
    
    __delay_us(60);
    
    LCD_LAT_RS = 0;
    
}

void IO_LCD_configureIO(void) {
    
#ifdef LCD_MODE_8BIT
    
    LCD_TRIS_D7 = 0;
    LCD_TRIS_D6 = 0;
    LCD_TRIS_D5 = 0;
    LCD_TRIS_D4 = 0;
    LCD_TRIS_D3 = 0;
    LCD_TRIS_D2 = 0;
    LCD_TRIS_D1 = 0;
    LCD_TRIS_D0 = 0;
    
#endif
    
#ifdef LCD_MODE_4BIT
    
    LCD_TRIS_D7 = 0;
    LCD_TRIS_D6 = 0;
    LCD_TRIS_D5 = 0;
    LCD_TRIS_D4 = 0;
    
#endif
    
    LCD_TRIS_EN = 0;
    LCD_TRIS_RS = 0;
    
    LCD_LAT_EN = 0;
    LCD_LAT_RS = 0;
    
    write_port(0x00);
    
    
}

void IO_LCD_Init(void) {
    
    __delay_ms(10);
    __delay_ms(10);
    __delay_ms(10);
    __delay_ms(10);
    
    write_cmd(0x30);
    __delay_ms(5);
    write_cmd(0x30);
    __delay_us(150);
    write_cmd(0x30);
    __delay_us(150);
    
#ifdef LCD_MODE_8BIT

    write_cmd(0x38);
   
#endif
    
#ifdef LCD_MODE_4BIT
    
    write_cmd(0x20);    
    
#endif
    
    __delay_us(60);
    write_cmd(0x08);    //Display off
    __delay_us(60);
    write_cmd(0x01);    //Clear display, cursor home
    __delay_ms(4);
    write_cmd(0x06);    //Entry mode set (increment DDRAM address, no scroll)
    __delay_us(60);
    write_cmd(0x0C);    //Display on
    __delay_us(60);
    
    lcd_state.blink_on = FALSE;
    lcd_state.cursor_on = FALSE;
    lcd_state.display_on = TRUE;
    lcd_state.DDRAM_addr = 0x00;
    lcd_state.CGRAM_addr = 0x00;
    
}

void IO_LCD_CursorHome(void) {
    
    write_cmd(0x02);
    __delay_ms(2);
    
}

void IO_LCD_ClearDisplay(void) {
    
    write_cmd(0x01);
    __delay_ms(2);
    
}

void IO_LCD_putc(char character) {
    
    write_data(character);
    
}

void IO_LCD_putrc(const char character) {
    
    write_data(character);
    
}

void IO_LCD_puts(char * str) {
    
    char i =0;
    
    while(str[i] != NULL) {
        
        write_data(str[i]);
        i++;
        
    }  
    
}

void IO_LCD_putrs(const char * str) {
    
    char i = 0;
    
    while(str[i] != NULL) {
        
        write_data(str[i]);
        i++;
        
    }  
    
}

void IO_LCD_SetCursor(char row, char col) {
    
    switch(row) {
        case(1):
            write_cmd(0x80 | col - 1);
            break;
        case(2):
            write_cmd(0x80 | col + 39);
            break;
        case(3):
            write_cmd(0x80 | col + 19);
            break;
        case(4):
            write_cmd(0x80 | col + 83);
            break;
        default:
            break;
    }
    
    __delay_us(60);
    
}

void IO_LCD_EnableCursor(void) {
    
    write_cmd(0x08 | (lcd_state.display_on << 2) | (1 << 1) | (lcd_state.blink_on));
    
    lcd_state.cursor_on = TRUE;
    
    __delay_us(60);
    
}

void IO_LCD_DisableCursor(void) {
    
    write_cmd(0x08 | (lcd_state.display_on << 2) | (0 << 1) | (lcd_state.blink_on));
    
    lcd_state.cursor_on = FALSE;
    
    __delay_us(60);
    
}

void IO_LCD_EnableDisplay(void) {
    
    write_cmd(0x08 | (1 << 2) | (lcd_state.cursor_on << 1) | (lcd_state.blink_on));
    
    lcd_state.display_on = TRUE;
    
    __delay_us(60);
    
}

void IO_LCD_DisableDisplay(void) {
    
    write_cmd(0x08 | (0 << 2) | (lcd_state.cursor_on << 1) | (lcd_state.blink_on));
    
    lcd_state.display_on = FALSE;
    
    __delay_us(60);
    
}

void IO_LCD_EnableBlink(void) {
    
    write_cmd(0x08 | (lcd_state.display_on << 2) | (lcd_state.cursor_on << 1) | (1));
    
    lcd_state.blink_on = TRUE; 
    
    __delay_us(60);
    
}

void IO_LCD_DisableBlink(void) {
    
    write_cmd(0x08 | (lcd_state.display_on << 2) | (lcd_state.cursor_on << 1) | (0));
    
    lcd_state.blink_on = FALSE;
    
    __delay_us(60);
    
}

void IO_LCD_SetEntryMode(bool inc_dec, bool disp_shift) {
    
    write_cmd(0x04 | (inc_dec << 1) | disp_shift);
    __delay_us(60);
    
}

void IO_LCD_ShiftCursor(char direction) {
    
    write_cmd(0x10 | (0 << 3) | (direction << 2));   
    __delay_us(60);
    
}

void IO_LCD_ShiftDisplay(char direction) {
    
    write_cmd(0x10 | (1 << 3) | (direction << 2));
    __delay_us(60);
    
}
