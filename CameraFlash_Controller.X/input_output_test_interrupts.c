#include <xc.h>
#include <stdio.h>
#include "global_defines.h"
#include "18f8722_config_bits_HSPLL.h"
#include "IO_Buttons.h"
#include "IO_LED.h"
#include "IO_LCD.h"
#include "IO_Encoder.h"
#include "plib/delays.h"

#pragma warning disable 520

volatile unsigned char count;
extern void trigloop(void);

void interrupt ISR(void) {
    
#asm
    BANKSEL(LATG)
    BCF     LATG,0
            BCF     PIR1,2      //PIR1 and LATG are in same bank (handliy)
#endasm
    
    __delay_us(50);
    
    LATGbits.LATG0 = 1;
    
    __delay_ms(15);     //Post trigger delay for 5Hz, 20% duty cycle input
    __delay_ms(15);
    __delay_ms(15);
    
    
}

void main(void) {
    
    unsigned char count = 0;
    char buff[21];
    unsigned int cap_bank = 0;
    unsigned int led_supply = 0;
    
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 0;
    RCONbits.IPEN = 0;
    
    PIE1bits.CCP1IE = 1;
    PIR1bits.CCP1IF = 0;
    
    CCP1CON = 0b00000101;   //Capture every rising edge
    
    DISCHARGE_FET_LAT = 0;
    CHARGE_FET_LAT = 0;
    COBLED_EN_LAT = 0;
    COBLED_IN_LAT = 1;
    
    DISCHARGE_FET_TRIS = 0;
    CHARGE_FET_TRIS = 0;
    COBLED_EN_TRIS = 0;
    COBLED_IN_TRIS = 0;
    
    VMON_LED_TRIS = 1;
    VMON_CAP_TRIS = 1;
    
    TRIG_OUT_LAT = 1;
    TRIG_OUT_TRIS = 0;
    
    IO_LCD_configureIO();
    IO_Buttons_configureIO(USE_POLLING, LP_INTERRUPT);
    
    OpenADC(ADC_FOSC_16 &
            ADC_RIGHT_JUST &
            ADC_2_TAD,
            ADC_CH0 &
            ADC_INT_OFF &
            ADC_VREFPLUS_VDD &
            ADC_VREFMINUS_VSS,
            8);
    
    SetChanADC(ADC_CH5);
    
    IO_LCD_Init();
    
    IO_LCD_putrs("Input/Output");
    IO_LCD_SetCursor(2,1);
    IO_LCD_putrs("Speed Test");
            
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Press to charge   ->");
    IO_LCD_SetCursor(2,1);
    IO_LCD_putrs("and enable LED");
    
    while(IO_Buttons_getButton(PB_1) != 1);
    
    IO_LCD_ClearDisplay();
    
    ConvertADC();
    while(BusyADC());
    led_supply = ReadADC();

    SetChanADC(ADC_CH6);

    ConvertADC();
    while(BusyADC());
    cap_bank = ReadADC();
    
    CHARGE_FET_LAT = 1;    
    
    while(cap_bank != led_supply) {
        
        SetChanADC(ADC_CH5);
            
            ConvertADC();
            while(BusyADC());
            led_supply = ReadADC();
            
            sprintf(buff, "LED:%4u", led_supply);
            IO_LCD_SetCursor(1,1);
            IO_LCD_puts(buff);
            
            SetChanADC(ADC_CH6);
            
            ConvertADC();
            while(BusyADC());
            cap_bank = ReadADC();
            
            sprintf(buff, "CAP:%4u", cap_bank);
            IO_LCD_SetCursor(2,1);
            IO_LCD_puts(buff);
            
            Delay10KTCYx(40);
        

    }
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Done!");
    
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    
    COBLED_EN_LAT = 1;
    
    IO_LCD_SetCursor(2,1);
    IO_LCD_putrs("LED driver enabled");
    
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    Delay10KTCYx(250);
    
    IO_LCD_ClearDisplay();
    
    IO_LCD_putrs("Responding to trig");
    IO_LCD_SetCursor(2,1);
    IO_LCD_putrs("INTERRUPTS");
    
    PIR1bits.CCP1IF = 0;
    INTCONbits.GIE = 1;
        
    while(1);
          
    
    
    
    
}

