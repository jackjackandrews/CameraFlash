#include <xc.h>
#include <stdio.h>
#include "global_defines.h"
//#include "18f87k22_config_bits.h"
#include "18f8722_config_bits.h"
#include "IO_Buttons.h"
#include "IO_LED.h"
#include "IO_LCD.h"
#include "TMR_SysTick.h"
#include "IO_Encoder.h"
#include "plib/delays.h"

#pragma warning disable 520

struct sig {
    
    unsigned char DISCHARGE :1;
    unsigned char CHARGE :1;
    unsigned char ENA :1;
    
} sig_statuses;

void interrupt ISR(void) {
    
    if(TMR_SYSTICK_IF == 1) {
        TMR_SysTick_ISR();
        
        IO_Encoder_ISR();
    }
    
    if(IO_BUTTONS_IF == 1) {
        
        IO_Buttons_ISR();
    }

    
}

void main(void) {
 
    unsigned char count;
    char buff[21];
    unsigned int adc_value;
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 0;
    INTCONbits.GIE = 0;
    
    DISCHARGE_FET_LAT = 0;
    CHARGE_FET_LAT = 0;
    COBLED_EN_LAT = 0;
    
    DISCHARGE_FET_TRIS = 0;
    CHARGE_FET_TRIS = 0;
    COBLED_EN_TRIS = 0;
    
    LED_MOD_DETECT_TRIS = 1;
    VMON_LED_TRIS = 1;
    VMON_CAP_TRIS = 1;
    
    sig_statuses.CHARGE = 0;
    sig_statuses.DISCHARGE = 0;
    sig_statuses.ENA = 0;
    
    OpenADC(ADC_FOSC_16 &
            ADC_RIGHT_JUST &
            ADC_2_TAD,
            ADC_CH0 &
            ADC_INT_OFF &
            ADC_VREFPLUS_VDD &
            ADC_VREFMINUS_VSS,
            8);
    
    SetChanADC(ADC_CH5);
    
    TMR_SysTick_configure(LP_INTERRUPT);
    IO_Buttons_configureIO(USE_POLLING, LP_INTERRUPT);
    IO_LED_configureIO();
    IO_LCD_configureIO();
    
    IO_LCD_Init();
    
    IO_LCD_putrs("LED Driver Module");
    IO_LCD_SetCursor(2,1);
    IO_LCD_putrs("Signal Test");
    
    Delay10KTCYx(250);
    
    IO_LCD_ClearDisplay();
    
    if(LED_MOD_DETECT_PORT != 1) {
        
        IO_LCD_putrs("Connect LED module");
        
        while(LED_MOD_DETECT_PORT != 1);
        
    }
    
    IO_LCD_ClearDisplay();
    
    while(1) {
        
        IO_LCD_SetCursor(1,12);
        IO_LCD_putrs("CHARGE: 0");
        
        IO_LCD_SetCursor(2,9);
        IO_LCD_putrs("DISCHARGE: 0");
        
        IO_LCD_SetCursor(3,11);
        IO_LCD_putrs("LED ENA: 0");
        
        
        while(LED_MOD_DETECT_PORT == 1) {
            
            SetChanADC(ADC_CH5);
            
            ConvertADC();
            while(BusyADC());
            adc_value = ReadADC();
            
            sprintf(buff, "LED:%4u", adc_value);
            IO_LCD_SetCursor(4,1);
            IO_LCD_puts(buff);
            
            SetChanADC(ADC_CH6);
            
            ConvertADC();
            while(BusyADC());
            adc_value = ReadADC();
            
            sprintf(buff, "CAP:%4u", adc_value);
            IO_LCD_SetCursor(4,10);
            IO_LCD_puts(buff);
            
            if(IO_Buttons_getButton(PB_1) == TRUE) {
                
                if(sig_statuses.DISCHARGE != 1) {
                    CHARGE_FET_LAT ^= 1;
                    sig_statuses.CHARGE ^= 1;
                    sprintf(buff, "%d", sig_statuses.CHARGE);

                    IO_LCD_SetCursor(1,20);
                    IO_LCD_puts(buff);
                }
                          
                
                
            }
            
            else if(IO_Buttons_getButton(PB_2) == TRUE) {
                
                if(sig_statuses.CHARGE != 1) {
                    DISCHARGE_FET_LAT ^= 1;
                    sig_statuses.DISCHARGE ^= 1;
                    sprintf(buff, "%d", sig_statuses.DISCHARGE);

                    IO_LCD_SetCursor(2,20);
                    IO_LCD_puts(buff); 
                }
                
                
                
            }
            
            else if(IO_Buttons_getButton(PB_3) == TRUE) {
                
                COBLED_EN_LAT ^= 1;
                sig_statuses.ENA ^= 1;
                sprintf(buff, "%d", sig_statuses.ENA);
                
                IO_LCD_SetCursor(3,20);
                IO_LCD_puts(buff);
                
            }
            
            
            Delay10KTCYx(10);
            
        }
        
        IO_LCD_ClearDisplay();
        IO_LCD_putrs("Connect LED module");
        
        while(LED_MOD_DETECT_PORT != 1);
        
        
        
    }
    
    
    
    
}
