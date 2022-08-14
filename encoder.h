/* 
 * File:   encoder.h
 * Author: ENG-Ahmed Maged
 *
 * Created on May 18, 2022, 2:38 PM
 */

#ifndef ENCODER_H
#define	ENCODER_H

#include "gpio.h"

    /*Port and Pins config*/
#define ENCODER_PORT            GPIOB
#define ENCODER_PIN             PINB
#define ENCODER_CHA_PIN         GPIO_PIN0
#define ENCODER_CHB_PIN         GPIO_PIN1
    
void Encoder_Init(void);
void Encoder_Update(void);
int16_t Encoder_Get_Value(void);

#endif	/* ENCODER_H */

