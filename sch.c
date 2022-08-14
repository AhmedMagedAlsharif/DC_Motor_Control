#include "sch.h"
#include "timer_basic.h"


sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t Error_code_G;

void SCH_Init_T0(void)
{

	uint8_t i;

	for (i = 0; i < SCH_MAX_TASKS; i++)
    {
		SCH_Delete_Task(i);
	}

    Timer0_init(CTC_Mode, TIMER_Prescaler_64);
    Timer0_Set_OutputCompare_Value(250);            //Tick every 1 ms
    Timer0_Enable_OutputCompare_Interrupt();
    Timer0_OutputCompare_INT_Callback(SCH_Update);
}

void SCH_Start(void)
{
	sei();
}

void SCH_Update(void)
{
	uint8_t Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++)
    {
		if (SCH_tasks_G[Index].pTask)
        {
			if (SCH_tasks_G[Index].Delay == 0)
            {
				SCH_tasks_G[Index].RunMe += 1;
				if (SCH_tasks_G[Index].Repeat)
                {
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Repeat;
				}
			} else
            {
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

void SCH_Dispatch_Tasks(void)
{
	uint8_t Index;

	for (Index = 0; Index < SCH_MAX_TASKS; Index++)
    {
		if (SCH_tasks_G[Index].RunMe > 0)
        {
			(*SCH_tasks_G[Index].pTask)();

			SCH_tasks_G[Index].RunMe -= 1;
			if (SCH_tasks_G[Index].Period == 0)
            {
				SCH_Delete_Task(Index);
			}
		}
	}
    
	SCH_Report_Status();

	SCH_Go_To_Sleep();
}

uint8_t SCH_Add_Task(void (*pFunction)(), const uint16_t DELAY, const uint16_t PERIOD,const uint16_t Repeat)
{
	uint8_t Index = 0;

	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
    {
		Index++;
	}

	if (Index == SCH_MAX_TASKS)
    {
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}

	SCH_tasks_G[Index].pTask = pFunction;

	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Repeat = Repeat;
	SCH_tasks_G[Index].Period = PERIOD;

	SCH_tasks_G[Index].RunMe = 0;

	return Index;
}

uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX)
{
	uint8_t Return_code;

	if (SCH_tasks_G[TASK_INDEX].pTask == 0)
    {
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		Return_code = RETURN_ERROR;
	}
    else
    {
		Return_code = RETURN_NORMAL;
	}

	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;

	SCH_tasks_G[TASK_INDEX].RunMe = 0;

	return Return_code;
}

void SCH_Report_Status(void)
{
#ifdef SCH_REPORT_ERRORS
	// ONLY APPLIES IF WE ARE REPORTING ERRORS
	// Check for a new error code
	if (Error_code_G != Last_error_code_G)
	{
		// Negative logic on LEDs assumed
		Error_port = 255 - Error_code_G;

		Last_error_code_G = Error_code_G;

		if (Error_code_G != 0)
		{
			Error_tick_count_G = 60000;
		}
		else
		{
			Error_tick_count_G = 0;
		}
	}
	else
	{
		if (Error_tick_count_G != 0)
		{
			if (--Error_tick_count_G == 0)
			{
				Error_code_G = 0; // Reset error code
			}
		}
	}
#endif
}

void SCH_Go_To_Sleep()
{
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sleep_cpu();                              //go to sleep
    sleep_disable();                          //wake up here
}
