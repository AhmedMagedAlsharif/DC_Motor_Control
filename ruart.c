#include "ruart.h"

static volatile unsigned char TX_Buffer[UART_TX_BUFFER_SIZE];
static volatile unsigned char RX_Buffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t TX_Head;
static volatile uint8_t TX_Tail;
static volatile uint8_t RX_Head;
static volatile uint8_t RX_Tail;

void UART_Init(uint32_t BaudRate)
{
    cli();
    TX_Head = 0;
    TX_Tail = 0;
    RX_Head = 0;
    RX_Tail = 0;
    
    uint16_t UBRR_Value =( (F_CPU / (16L * BaudRate) ) -1);
    UBRRH = (uint8_t)(UBRR_Value>>8);
    UBRRL = (uint8_t) UBRR_Value;
    
    UCSRB |= (1<<TXEN) | (1<<RXEN) | (1<<TXCIE) | (1<<RXCIE);
    UCSRC = (1<<URSEL)|(3<<UCSZ0);
    sei();
}
void UART_Send_Char(unsigned char ch)
{
    TX_Buffer[TX_Head] = ch;
    TX_Head++;
    if(TX_Head >= UART_TX_BUFFER_SIZE)
    {
        TX_Head = 0;
    }
}
void UART_Send_String(const char *s)
{
    while(*s)
    {
        UART_Send_Char(*s++);
    }
    UART_Refresh();
}
void UART_Refresh(void)
{
    if(UCSRA & (1<<UDRE))
    {
        UDR = 0;
    }
}

void UART_Send_uint32(uint32_t n)
{ 
    if (n == 0)
    {
      UART_Send_Char('0');
      return;
    }

    char buf[10] = {'\0'}; 
    uint8_t i = 0;  

    while (n > 0)
    {
      buf[i++] = n % 10;
      n /= 10;
    }

    for (; i > 0; i--)
    {
        UART_Send_Char('0' + buf[i-1]);
    }
    UART_Refresh();
}


void UART_Send_Integer(long n)
{
    if (n < 0)
    {
      UART_Send_Char('-');
      UART_Send_uint32(-n);
    } 
    else
    {
      UART_Send_uint32(n);
    }
}

void UART_Send_Float(float n, uint8_t decimal_places)
{
    if (n < 0)
    {
    UART_Send_Char('-');
    n = -n;
    }

    uint8_t decimals = decimal_places;
    while (decimals >= 2)
    { // Quickly convert values expected to be E0 to E-4.
        n *= 100;
        decimals -= 2;
    }
    if (decimals)
    {
        n *= 10;
    }
    n += 0.5; // Add rounding factor. Ensures carryover through entire value.

    // Generate digits backwards and store in string.
    unsigned char buf[10] = {'\0'}; 
    uint8_t i = 0;
    uint32_t a = (long)n;  
    buf[decimal_places] = '.'; // Place decimal point, even if decimal places are zero.
    while(a > 0)
    {
        if (i == decimal_places) { i++; } // Skip decimal point location
        buf[i++] = (a % 10) + '0'; // Get digit
        a /= 10;
    }
    while (i < decimal_places)
    { 
        buf[i++] = '0'; // Fill in zeros to decimal point for (n < 1)
    }
    if (i == decimal_places)
    { // Fill in leading zero, if needed.
        i++;
        buf[i++] = '0'; 
    }   

    // Print the generated string.
    for (; i > 0; i--)
    {
        UART_Send_Char(buf[i-1]);
    }
    UART_Refresh();
}

ISR (USART_TXC_vect)
{
    if(TX_Tail != TX_Head)
    {
        UDR = TX_Buffer[TX_Tail];
        TX_Tail++;
    }
    if(TX_Tail >= UART_TX_BUFFER_SIZE)
    {
        TX_Tail = 0;
    }
}

unsigned char UART_Get_Char(void)
{
    char ch = '\0';
    if(RX_Tail != RX_Head)
    {
        ch = RX_Buffer[RX_Tail];
        RX_Tail++;
    }
    if(RX_Tail >= UART_RX_BUFFER_SIZE)
    {
        RX_Tail = 0;
    }
    return ch;
}

uint8_t UART_Available(void)
{
    uint8_t ret = 0;
    if(RX_Head > RX_Tail)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

ISR (USART_RXC_vect)
{
    RX_Buffer[RX_Head] = UDR;
    RX_Head++;
    if(RX_Head >= UART_RX_BUFFER_SIZE)
    {
        RX_Head = 0;
    }
}
