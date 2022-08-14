/* 
 * File:   uart.h
 * Author: ENG-Ahmed Maged
 *
 * Created on May 19, 2022, 2:47 PM
 */

#ifndef UART_H
#define	UART_H
    
#include <xc.h>
    
#include <avr/interrupt.h>
    
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
    
#ifndef UART_TX_BUFFER_SIZE
#define UART_TX_BUFFER_SIZE 64
#endif
    
#ifndef UART_RX_BUFFER_SIZE
#define UART_RX_BUFFER_SIZE 32
#endif
    
void UART_Init(uint32_t BaudRate);
void UART_Send_Char(unsigned char ch);
void UART_Send_String(const char *s);
void UART_Send_uint32(uint32_t n);
void UART_Send_Integer(long n);
void UART_Send_Float(float n, uint8_t decimal_places);
void UART_Refresh(void);
unsigned char UART_Get_Char(void);
uint8_t UART_Available(void);

#endif	/* UART_H */

