/* 
 * File:   sch.h
 * Author: ahmed
 *
 * Created on May 18, 2022, 11:26 AM
 */

#ifndef SCH_H
#define	SCH_H

#include <xc.h>
#include <avr/interrupt.h>
#include<avr/sleep.h>


#define SCH_MAX_TASKS (3)

#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

#define RETURN_NORMAL (uint8_t) 0
#define RETURN_ERROR (uint8_t) 1

typedef struct
{
void (* pTask)(void);
uint16_t Delay;
uint16_t Period;
uint16_t RunMe;
uint16_t Repeat;
} sTask;

void SCH_Init_T0(void);
void SCH_Start(void);

uint8_t SCH_Add_Task(void (* pFunction)(), const uint16_t DELAY, const uint16_t PERIOD, const uint16_t Repeat);
uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX);

void SCH_Report_Status(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Go_To_Sleep();


#endif	/* SCH_H */

