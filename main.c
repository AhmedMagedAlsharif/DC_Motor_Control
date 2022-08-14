/*
 * File:   main.c
 * Author: ENG-Ahmed Maged
 *
 * Created on 19 sept, 2021
 */

#include "main.h"

/* Controller parameters */
#define PID_KP  0.2479176f
#define PID_KI  13.172459f
#define PID_KD  0.0f

#define PID_TAU 0.0f

#define PID_LIM_MIN -12.0f
#define PID_LIM_MAX  12.0f

#define PID_LIM_MIN_INT -12.0f
#define PID_LIM_MAX_INT  12.0f

#define SAMPLE_TIME_S 0.01f

/* Initialize PID controller */
PID_t pid = { PID_KP, PID_KI, PID_KD,
                      PID_TAU,
                      PID_LIM_MIN, PID_LIM_MAX,
                      PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                      SAMPLE_TIME_S };

void Serial(void);
void Control_Routine(void);

//char Buffer[64] = {'\0'};
float setpoint = -1;
float motor_speed = 0;

int main(void) {
    Encoder_Init();
    UART_Init(9600);
    PIDController_Init(&pid);
    GPIO_Init(GPIOD, GPIO_PIN5|GPIO_PIN6, GPIO_Mode_OUT);
    Timer1_init(Fast_PWM_ICR_Mode, TIMER_Prescaler_64);
    Timer1_Set_InputCapture_Value(255);
    
    SCH_Init_T0();
	SCH_Add_Task(Encoder_Update, 0, 1, 1);
    SCH_Add_Task(Control_Routine, 0, 1, 10);
	SCH_Add_Task(Serial, 0, 1, 100);

	SCH_Start();
    
    while (1) 
    {
        SCH_Dispatch_Tasks();
    }
    return 0;
}
void Serial(void)
{
    UART_Send_String("\nMotor_Speed");
    UART_Send_Float(motor_speed, 2);
    UART_Send_String("\tset_point");
    UART_Send_Float(setpoint, 2);
}
void Control_Routine(void)
{
    int16_t measurment;
    static int16_t prev_measurment = 0;
    int16_t PWM_Value;
    
    measurment = Encoder_Get_Value();
    motor_speed = ((measurment - prev_measurment)/0.01f)*(1/120.0f);
    PWM_Value = (int16_t)(21.25f * PIDController_Update(&pid, setpoint, motor_speed));
    
    if(PWM_Value >= 0)
    {
        GPIO_Set_Pins(GPIOD, GPIO_PIN6);
        Timer1_Set_OutputCompareA_Value(PWM_Value);
    }
    else
    {
        GPIO_Reset_Pins(GPIOD, GPIO_PIN6);
        Timer1_Set_OutputCompareA_Value(-PWM_Value);
    }
    prev_measurment = measurment;
}
