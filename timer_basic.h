/* 
 * File:   timer_basic.h
 * Author: ENG-Ahmed Maged
 *
 * Created on 20 Jun, 2021, 02:38 AM
 */

#ifndef TIMER_BASIC_H
#define	TIMER_BASIC_H

#include "main.h"

#ifdef	__cplusplus
extern "C" {
#endif
    

    typedef enum
    {
        TIMER_Stop_CLK = 0x00,
        TIMER_NO_Prescaler = 0x01,
        TIMER_Prescaler_8 = 0x02,
        TIMER_Prescaler_64 = 0x03,
        TIMER_Prescaler_256 = 0x04,
        TIMER_Prescaler_1024 = 0x05
    }Timer_Prescaler_t;
    
    typedef enum
    {
        Normal_Mode,
        PWM_PhaseCorrect_Mode,
        CTC_Mode,
        Fast_PWM_Mode
    }Timer0_Mode_t;
    
    typedef enum
    {
        Normal_Mode1,                               //Top->0xFFFF
        PWM_PhaseCorrect_8Bit_Mode,                 //Top->0x00FF
        PWM_PhaseCorrect_9Bit_Mode,                 //Top->0x01FF
        PWM_PhaseCorrect_10Bit_Mode,                //Top->0x03FF
        CTC_OCRA_Mode,                              //Top->OCR1A
        Fast_PWM_8Bit_Mode,                         //Top->0x00FF
        Fast_PWM_9Bit_Mode,                         //Top->0x01FF
        Fast_PWM_10Bit_Mode,                        //Top->0x03FF
        PWM_PhaseandFrequancyCorrect_ICR_Mode,      //Top->ICR1
        PWM_PhaseandFrequancyCorrect_OCRA_Mode,     //Top->OCR1A
        PWM_PhaseCorrect_ICR_Mode,                  //Top->ICR1
        PWM_PhaseCorrect_OCRA_Mode,                 //Top->OCR1A
        CTC_ICR_Mode,                               //Top->ICR1
        _Reserved,
        Fast_PWM_ICR_Mode,                          //Top->ICR1
        Fast_PWM_OCRA_Mode,                         //Top->OCR1A
        InputCapture_Rissing_Edge_Mode,
        InputCapture_Falling_Edge_Mode
    }Timer1_Mode_t;
    
    /*Timer0*/
    
    void Timer0_init(Timer0_Mode_t, Timer_Prescaler_t);
    void Timer0_Set_Preload_Value(uint8_t);
    void Timer0_Set_OutputCompare_Value(uint8_t);
    uint8_t Timer0_Get_TimerCounter_Value(void);
    uint8_t Timer0_Get_Overflow_Flag(void);
    uint8_t Timer0_Get_OutputCompare_Flag(void);
    
    void Timer0_Enable_OutputCompare_Interrupt(void);
    void Timer0_Disable_OutputCompare_Interrupt(void);
    void Timer0_Enable_Overflow_Interrupt(void);
    void Timer0_Disable_Overflow_Interrupt(void);
    
    void Timer0_OverFlow_INT_Callback(void (*funPtr)(void));
    void Timer0_OutputCompare_INT_Callback(void (*funPtr)(void));
   
    /*Timer1*/
    
    void Timer1_init(Timer1_Mode_t, Timer_Prescaler_t);
    void Timer1_Set_Preload_Value(uint16_t);
    void Timer1_Set_OutputCompareA_Value(uint16_t);
    void Timer1_Set_OutputCompareB_Value(uint16_t);
    void Timer1_Set_InputCapture_Value(uint16_t);
    uint16_t Timer1_Get_TimerCounter_Value(void);
    uint8_t Timer1_Get_Overflow_Flag(void);
    uint8_t Timer1_Get_OutputCompareA_Flag(void);
    uint8_t Timer1_Get_OutputCompareB_Flag(void);
    uint8_t Timer1_Get_InputCapture_Flag(void);
    
    void Timer1_Enable_Overflow_Interrupt(void);
    void Timer1_Disable_Overflow_Interrupt(void);
    void Timer1_Enable_OutputCompareA_Interrupt(void);
    void Timer1_Disable_OutputCompareA_Interrupt(void);
    void Timer1_Enable_OutputCompareB_Interrupt(void);
    void Timer1_Disable_OutputCompareB_Interrupt(void);
    void Timer1_Enable_InputCapture_Interrupt(void);
    void Timer1_Disable_InputCapture_Interrupt(void);

    void Timer1_OverFlow_INT_Callback(void (*funPtr)(void));
    void Timer1_OutputCompareA_INT_Callback(void (*funPtr)(void));
    void Timer1_OutputCompareB_INT_Callback(void (*funPtr)(void));
    void Timer1_InputCapture_INT_Callback(void (*funPtr)(void));
    
#endif	/* TIMER_BASIC_H */

