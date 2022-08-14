
#include "gpio.h"

/**
 * 
 * @param GPIOx
 * @param GPIO_Pins
 * @param GPIO_Mode
 */
void GPIO_Init(GPIO_t* GPIOx, uint8_t GPIO_Pins, GPIO_Mode_t GPIO_Mode)
{
    uint8_t pinpos;
    /* Go through all pins */
	for (pinpos = 0; pinpos < 0x08; pinpos++) {
		/* Check if pin available */
		if ((GPIO_Pins & (1 << pinpos)) == 0)
        {
			continue;
		}
        GPIOx->Data_Dir_Reg |= ((GPIO_Mode&0x01) << pinpos);

        if(GPIO_Mode == GPIO_Mode_IN_PU)
        {
            GPIOx->Port_Reg |= (1 << pinpos);
        }
    }
}
/**
 * 
 * @param GPIOx
 * @param GPIO_Pins
 */
void GPIO_Set_Pins(GPIO_t* GPIOx, uint8_t GPIO_Pins)
{
    GPIOx->Port_Reg |= (GPIO_Pins);
}
/**
 * 
 * @param GPIOx
 * @param GPIO_Pins
 */
void GPIO_Reset_Pins(GPIO_t* GPIOx, uint8_t GPIO_Pins)
{
    GPIOx->Port_Reg &= ~(GPIO_Pins);
}
/**
 * 
 * @param GPIOx
 * @param value
 */
void GPIO_Set_Port(GPIO_t* GPIOx, uint8_t value)
{
    GPIOx->Port_Reg = value;
}
/**
 * 
 * @param GPIOx
 */
void GPIO_Reset_Port(GPIO_t* GPIOx)
{
    GPIOx->Port_Reg = 0x00;
}
/**
 * @brief  Gets Pin States
 * @param  *GPIOx: GPIO used to get settings for
 * @param  GPIO Pin
 * @retval uint8_t status of pin HIGHT or LOW
 */
uint8_t GPIO_Get_Pin(GPIO_t* GPIOx, uint8_t GPIO_Pin)
{
    uint8_t ret = 0x00;
    if(GPIOx->Pin_Reg & GPIO_Pin)
    {
        ret = (uint8_t)1;
    }
    else
    {
        ret = (uint8_t)0;
    }
    return ret;
}
/**
 * 
 * @param GPIOx
 * @return 
 */
uint8_t GPIO_Get_Port(GPIO_t* GPIOx)
{
    return (uint8_t)GPIOx->Pin_Reg;
}
