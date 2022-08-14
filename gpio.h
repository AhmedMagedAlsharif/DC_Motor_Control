/* 
 * File:   gpio.h
 * Author: ENG-Ahmed Maged
 *
 * Created on 19 Jun, 2021, 05:36 PM
 */

#ifndef GPIO_H
#define	GPIO_H

#include <xc.h> // include processor files - each processor file is guarded.  


#ifdef	__cplusplus
extern "C" {
#endif


#define GPIO_PIN0 0x01
#define GPIO_PIN1 0x02
#define GPIO_PIN2 0x04
#define GPIO_PIN3 0x08
#define GPIO_PIN4 0x10
#define GPIO_PIN5 0x20
#define GPIO_PIN6 0x40
#define GPIO_PIN7 0x80
    
#define GPIOA ((GPIO_t *)0x39)
#define GPIOB ((GPIO_t *)0x36)
#define GPIOC ((GPIO_t *)0x33)
#define GPIOD ((GPIO_t *)0x30)

typedef enum
{
    GPIO_Mode_IN = 0x00,
    GPIO_Mode_OUT = 0x01,
    GPIO_Mode_IN_PU = 0x02    
}GPIO_Mode_t;

typedef struct {
    unsigned char Pin_Reg;
    unsigned char Data_Dir_Reg;
    unsigned char Port_Reg;
}volatile GPIO_t;

void GPIO_Init(GPIO_t* GPIOx, uint8_t GPIO_Pins, GPIO_Mode_t GPIO_Mode);
void GPIO_Set_Pins(GPIO_t* GPIOx, uint8_t GPIO_Pins);
void GPIO_Reset_Pins(GPIO_t* GPIOx, uint8_t GPIO_Pins);
void GPIO_Set_Port(GPIO_t* GPIOx, uint8_t value);
void GPIO_Reset_Port(GPIO_t* GPIOx);
uint8_t GPIO_Get_Pin(GPIO_t* GPIOx, uint8_t GPIO_Pin);
uint8_t GPIO_Get_Port(GPIO_t* GPIOx);

#endif	/* GPIO_H */

