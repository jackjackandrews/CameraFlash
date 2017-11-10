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
    
#ifdef LCD_MODE_8BIT
    
    LCD_LAT_RS = 0;
    
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
    
#ifdef MODE_4BIT
    
    LCD_LAT_RS = 0;
    
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
    
#ifdef LCD_MODE_8BIT
    
    LCD_LAT_RS = 1;
    
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
    
#ifdef MODE_4BIT
    
    LCD_LAT_RS = 1;
    
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
    
}

void IO_LCD_Init(void) {
    
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
    
    __delay_ms(40);
    
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
    
    write_cmd(0x28);    
    
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
    lcd_state.scroll_on = FALSE;
    lcd_state.DDRAM_addr = 0x00;
    lcd_state.CGRAM_addr = 0x00;
    
}

void IO_LCD_CursorHome(void) {
    
    
}

void IO_LCD_WriteChar(char character) {
    
    write_data(character);
    __delay_us(60);
    
}

void IO_LCD_SetCursor(char x, char y) {
    
    
}

void IO_LCD_EnableCursor(void) {
    
    
}

void IO_LCD_DisableCursor(void) {
    
    
}

void IO_LCD_EnableDisplay(void) {
    
    
}

void IO_LCD_DisableDisplay(void) {
    
    
}

void IO_LCD_EnableBlink(void) {
    
    
}

void IO_LCD_DisableBlink(void) {
    
    
}

void IO_LCD_EnableScroll(void) {
    
    
}

void IO_LCD_DisableScroll(void) {
    
    
}

void IO_LCD_SetCursorShift(char direction) {
    
    
}

void IO_LCD_SetDisplayShift(char direction) {
    
    
}