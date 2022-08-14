#include "encoder.h"

static int16_t Encoder_Value;

void Encoder_Init(void)
{
    GPIO_Init(ENCODER_PORT, ENCODER_CHA_PIN|ENCODER_CHB_PIN, GPIO_Mode_IN_PU);
    Encoder_Value = 0;
}

void Encoder_Update(void)
{
    uint8_t Cur_State = 0;
    static uint8_t Prev_State = 255;
    Cur_State = ((!(ENCODER_PIN&ENCODER_CHA_PIN))|((!(ENCODER_PIN&ENCODER_CHB_PIN))<<1));
    switch(Cur_State)
    {
        case 0x00:
            if(Prev_State == 0x02)
            {
                Encoder_Value++;
            }
            else if(Prev_State == 0x01)
            {
                Encoder_Value--;
            }
        break;
        case 0x01:
            if(Prev_State == 0x00)
            {
                Encoder_Value++;
            }
            else if(Prev_State == 0x03)
            {
                Encoder_Value--;
            }
        break;
        case 0x03:
            if(Prev_State == 0x01)
            {
                Encoder_Value++;
            }
            else if(Prev_State == 0x02)
            {
                Encoder_Value--;
            }
        break;
        case 0x02:
            if(Prev_State == 0x03)
            {
                Encoder_Value++;
            }
            else if(Prev_State == 0x00)
            {
                Encoder_Value--;
            }
        break;
    }
    Prev_State = Cur_State;
}
int16_t Encoder_Get_Value(void)
{
    return Encoder_Value;
}
