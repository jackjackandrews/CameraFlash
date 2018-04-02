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
#include "plib/adc.h"
#include "plib/delays.h"
#include "plib/pwm.h"
#include "plib/timers.h"

#pragma warning disable 520

#define PS_1_1 0x00
#define PS_1_4 0x01
#define PS_1_16 0x02

#define PWM_FREQ    10000
#define PR2_VALUE   249
#define TMR2_PS PS_1_1     
#define DC_REG_FULL 1000

#define PID_Kp 1

#define VREF_MV    5000
#define xH_MV 30.00
#define xL_MV 10.00
#define INPUT_DIV   10

float calGain_ADC;
float calOffset_ADC;

void interrupt ISR(void) {
    
    if(TMR_SYSTICK_IF == 1) {
        TMR_SysTick_ISR();
        
        IO_Encoder_ISR();
    }
    
    if(IO_BUTTONS_IF == 1) {
        
        IO_Buttons_ISR();
    }    
    
}

float convertADCtoVolt(unsigned int adc) {
    
    return(((float)adc - calOffset_ADC) / calGain_ADC);
    
}

unsigned int convertVolttoADC(float volt) {
    
    return((calGain_ADC * volt) + calOffset_ADC);
    
}

void chargeSequence(unsigned int set_voltage_adc) {
    
    bool done = FALSE;
    bool discharge_flag = FALSE;
    int error = 0;
    unsigned int curr_voltage_adc = 0;
    float set_voltage = 0;
    char buff[21];
    
    //IO_LCD_ClearDisplay();
    
    
    //while(IO_Buttons_getButton(PB_4) == FALSE);
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Charge & maintain...");
    
    IO_LCD_SetCursor(2,1);
    set_voltage = convertADCtoVolt(set_voltage_adc);
    
    sprintf(buff, "%-3.3f V", set_voltage);
    IO_LCD_puts(buff);
    
    IO_LCD_SetCursor(4, 15);
    IO_LCD_putrs("Stop >");
    
    //Configure PWM on charge/discharge pin
    //Configure ADC for cap bank voltage
    
    //Show set voltage on LCD, use renc to change
    //Press button to charge to set voltage
    
    Delay10KTCYx(50);
    
    error = 0;
    discharge_flag = FALSE;
    
    while(IO_Buttons_getButton(PB_4) == FALSE) {
        
        ConvertADC();
        while(BusyADC());
        
        curr_voltage_adc = ReadADC();
        error = set_voltage_adc - curr_voltage_adc;
        
        if (error < 0) {
           SetDCPWM5((unsigned int)error * - PID_Kp);
           SetDCPWM4(0);
        }
        
        else if(error > 0) {
           SetDCPWM4((unsigned int)error * PID_Kp);
           SetDCPWM5(0);
            
        }
        else if (error == 0) {
           SetDCPWM4(0);
           SetDCPWM5(0);
           done = TRUE;
            
        }
        
        
    }
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Done!");
    
    SetDCPWM4(0);
    SetDCPWM5(0);
    
    Delay10KTCYx(250);
    
    
    
}

void dischargeSequence(void) {
    
    bool done = FALSE;
    int error = 0;
    unsigned int curr_voltage_adc = 0;
    
    IO_LCD_ClearDisplay();
    IO_LCD_SetCursor(4, 10);
    IO_LCD_putrs("Discharge >");
    
    while(IO_Buttons_getButton(PB_4) == FALSE);
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Discharging...");
    
    error = 0;
    
    while(!done) {
        
        ConvertADC();
        while(BusyADC());
        
        curr_voltage_adc = ReadADC();
        
        if (curr_voltage_adc == 0) {
            
            done = TRUE;
        }
        else {
            
            SetDCPWM5(1023);
            
        }
        
        
    }
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Done!");
    
    Delay10KTCYx(250);
    
    
}

void calibrationSequenceADC(void) {
    
    char buff[21];
    
    unsigned int yL, yH;
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Apply 10.00V");
    
    while(IO_Buttons_getButton(PB_1) == FALSE) {
        
        ConvertADC();
        while(BusyADC());
        yL = ReadADC();
        
        IO_LCD_SetCursor(3,1);
        sprintf(buff, "ADC: %-4d", yL);
        IO_LCD_puts(buff);
        
        Delay10KTCYx(50);
        
    }
    
    Delay10KTCYx(150);
    
    IO_LCD_ClearDisplay();
    IO_LCD_putrs("Apply 30.00V");
    
    while(IO_Buttons_getButton(PB_1) == FALSE) {
        
        ConvertADC();
        while(BusyADC());
        yH = ReadADC();
        
        IO_LCD_SetCursor(3,1);
        sprintf(buff, "ADC: %-4d", yH);
        IO_LCD_puts(buff);
        
        Delay10KTCYx(50);
        
    }
    
    calGain_ADC =  (yH - yL)/(xH_MV - xL_MV);
    calOffset_ADC = yL - (calGain_ADC * xL_MV);
    
    IO_LCD_ClearDisplay();
    
    IO_LCD_SetCursor(1,1);
    sprintf(buff, "Gain: %-3.3f", calGain_ADC);
    IO_LCD_puts(buff);
    
    IO_LCD_SetCursor(2,1);
    sprintf(buff, "Offset: %-3.3f", calOffset_ADC);
    IO_LCD_puts(buff);
    
    IO_LCD_SetCursor(4,11);
    IO_LCD_putrs("Continue >");
    
    while(IO_Buttons_getButton(PB_4) == FALSE);
    
    
    
}

void main(void) {
    
    int set_voltage_adc = 512, encoder_count;
    unsigned int set_voltage_adc_scaled;
    float set_voltage = 0;
    char buff[20];
    
    RCONbits.IPEN = 0;
    
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    PIE3bits.CCP3IE = 1;
    IPR3bits.CCP3IP = 0;
    
    TMR_SysTick_configure(LP_INTERRUPT);
    IO_Buttons_configureIO(USE_INTERRUPTS, LP_INTERRUPT);
    IO_LED_configureIO();
    IO_LCD_configureIO();
    IO_Encoder_configureIO();
    
    IO_LCD_Init();
    
    //Configure charge/discharge control pins
    TRISGbits.TRISG3 = 0;
    TRISGbits.TRISG4 = 0;
    
    LATGbits.LATG3 = 0;
    LATGbits.LATG4 = 0;
    
    T3CONbits.T3CCP1 = 0;   //Timer1 used for all capture/compare units,
    T3CONbits.T3CCP2 = 0;   //Timer2 used for all PWM units
    
    
    OpenTimer2(TIMER_INT_OFF //Interrupts disabled
            & T2_PS_1_16 //Prescaler 1:1
            & T2_POST_1_1 //Postscaler 1:1
            & T12_SOURCE_CCP);
    
    
//    T2CON = 0x00 | TMR2_PS; //Configure Timer2 for PWM - don't turn it on yet
//    PR2 = PR2_VALUE;
    
    OpenPWM4(PR2_VALUE); //Set up CCP4 in PWM mode
    OpenPWM5(PR2_VALUE); //Set up CCP5 in PWM mode
    
//    CCP4CON = 0x0A;     //Configure capture and compare modules for PWM
//    CCP5CON = 0x0A;
    
    SetDCPWM4(0);
    SetDCPWM5(0);
    
    
    T2CONbits.TMR2ON = 1;   //Turn on timer
    
    TRISFbits.TRISF2 = 1;   //Set as input to ADC converter (V_CAP_BANK)
    
    OpenADC(ADC_FOSC_16 &
            ADC_RIGHT_JUST &
            ADC_2_TAD,
            ADC_CH0 &
            ADC_INT_OFF &
            ADC_VREFPLUS_VDD &
            ADC_VREFMINUS_VSS,
            7);
    
    SetChanADC(ADC_CH7);
    
    calibrationSequenceADC();
    
    //calibrationSequenceCapInput();
    
    IO_LCD_ClearDisplay();
    
    Delay10KTCYx(50);
    
    while(1) {
         
        IO_LCD_SetCursor(4, 13);
        IO_LCD_putrs("Charge >");
        
        while(IO_Buttons_getButton(PB_4) == FALSE) {
            
            set_voltage_adc += IO_Encoder_getCount();

            if (set_voltage_adc > 1023) {
            set_voltage_adc = 0;
            }
            else if (set_voltage_adc < 0) {
                set_voltage_adc = 1023;
            }

            set_voltage = convertADCtoVolt(set_voltage_adc);
            
            sprintf(buff, "%-4d", set_voltage_adc);
            IO_LCD_puts(buff);
            
            IO_LCD_SetCursor(2,1);
            sprintf(buff, "%-2.3fV", set_voltage);
            IO_LCD_puts(buff);
            
            __delay_ms(50);
            
            IO_LCD_SetCursor(1,1);
            
        }
        
        chargeSequence(set_voltage_adc);
        
        dischargeSequence();
        
        IO_LCD_ClearDisplay();
        
        
    }
    
//    sprintf(buff, "PWM Freq: %.1fkHz", PWM_FREQ / 1000);
//    IO_LCD_putrs(buff);
//    
//    IO_LCD_SetCursor(2,1);
//    IO_LCD_putrs("Set Volt: ");
//    
//    IO_LCD_SetCursor(3, 1);
//    IO_LCD_putrs("Curr Volt: ");
//    
    
    
    //P(ID) control using current_voltage vs target_voltage which adjusts output on PWM pin until setpoint is achieved
    //If error is positive (ie. overshoot), PWM discharge pin 
    //Press another button to discharge and start again
    
}
