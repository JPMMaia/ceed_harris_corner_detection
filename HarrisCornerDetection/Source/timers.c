/*
 * timers.c
 *
 *  Created on: 12 de Mai de 2014
 *      Author: jmpc
 */
/*******************************************************************************/
/*                                H E A D E R                                  */
/*******************************************************************************/

// File Name		: timers.c
// Author		: Shay Gal-On, EEMBC
// Modified by		: Sven Andersson ZooCad Consulting
// Processor		: ARM Cortex-A9
// Evaluation Board	: ZedBoard
// Date			: 2014-02-25

// version adapted by João Cardoso

/*******************************************************************************/
/*                             I N C L U D E S                                 */
/*******************************************************************************/

//#include <stdio.h>
//#include <stdlib.h>
#include "xparameters.h"
#include "xscutimer.h"
#include "timers.h"

/*******************************************************************************/
/*                             D E F I N E S                                   */
/*******************************************************************************/
#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID
#define TIMER_LOAD_VALUE	0xFFFFFFE
#define START_COUNTER		0
#define STOP_COUNTER		1

#define NSECS_PER_SEC 		667000000/2
#define CORETIMETYPE 		uint32
#define TIMER_RES_DIVIDER 	40
#define EE_TICKS_PER_SEC 	(NSECS_PER_SEC / TIMER_RES_DIVIDER)


/*******************************************************************************/
/*                        G L O B A L   V A R I A B L E S                      */
/*******************************************************************************/
static CORETIMETYPE start_time_val, stop_time_val;

/*******************************************************************************/
/*                             I N S T A N C E S                               */
/*******************************************************************************/
// Cortex A9 SCU Private Timer Instance
XScuTimer		Timer;


/*******************************************************************************/
/*                      F U N C T I O N A L   P R O T O T Y P E S              */
/*******************************************************************************/

uint32 GetTimerValue(uint32 TimerIntrId, uint16 Mode);


/*******************************************************************************/
/*                         G E T  S T A R T  T I M E                           */
/*******************************************************************************/

// Get start time by reading the ARM CPU private timer counter

void start_time(void) {
	start_time_val = GetTimerValue(TIMER_DEVICE_ID,START_COUNTER);
}

/*******************************************************************************/
/*                           G E T  S T O P  T I M E                           */
/*******************************************************************************/

// Get stop time by reading the ARM CPU private timer counter

void stop_time(void) {
	stop_time_val = GetTimerValue(TIMER_DEVICE_ID,STOP_COUNTER);
}


/*******************************************************************************/
/*                       G E T  E L A P S E D  T I M E                         */
/*******************************************************************************/


CORE_TICKS get_core_ticks(void) {
	CORE_TICKS elapsed = start_time_val-stop_time_val;
	return elapsed;
}

/*******************************************************************************/
/*                    C O N V E R T  T O  T I M E  U N I T S                       */
/*******************************************************************************/

timerepr time_in_secs(CORE_TICKS ticks) {
	timerepr retval = ((timerepr) ticks) / (timerepr) EE_TICKS_PER_SEC;

	//printf("ticks %d, sec %f, EE_TICKS_PER_SEC %d \n", ticks, retval, EE_TICKS_PER_SEC);
	//printf("sec %f\n", retval);

	return retval;
}

timerepr time_in_msecs(CORE_TICKS ticks) {
	timerepr retval = 1000*((timerepr) ticks) / (timerepr) EE_TICKS_PER_SEC;

	//printf("ticks %d, sec %f, EE_TICKS_PER_SEC %d \n", ticks, retval, EE_TICKS_PER_SEC);
	//printf("sec %f\n", retval);

	return retval;
}

timerepr time_in_usecs(CORE_TICKS ticks) {
	timerepr retval = 1E6*((timerepr) ticks) / (timerepr) EE_TICKS_PER_SEC;

	//printf("ticks %d, sec %f, EE_TICKS_PER_SEC %d \n", ticks, retval, EE_TICKS_PER_SEC);
	//printf("sec %f\n", retval);

	return retval;
}

/*******************************************************************************/
/*                          G E T  T I M E R  V A L U E                        */
/*******************************************************************************/

// This routine is specific for the ARM Cortex-A9 processor

uint32 GetTimerValue(uint32 TimerIntrId, uint16 Mode)
{

	int 			Status;
	XScuTimer_Config 	*ConfigPtr;
	volatile uint32		CntValue  = 0;
	XScuTimer *TimerInstancePtr = &Timer;


	if (Mode == 0) {

	  // Initialize the Private Timer so that it is ready to use
	  ConfigPtr = XScuTimer_LookupConfig(TimerIntrId);

	  Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr,
					 ConfigPtr->BaseAddr);

	   if (Status != XST_SUCCESS) {
		  return XST_FAILURE; }

	   // Load the timer prescaler register.
	   XScuTimer_SetPrescaler(TimerInstancePtr, TIMER_RES_DIVIDER);

	   // Load the timer counter register.
	  XScuTimer_LoadTimer(TimerInstancePtr, TIMER_LOAD_VALUE);

	  // Start the timer counter and read start value
	  XScuTimer_Start(TimerInstancePtr);
	  CntValue = XScuTimer_GetCounterValue(TimerInstancePtr);

	}

	else {

	   // Read stop value and stop the timer counter
	   CntValue = XScuTimer_GetCounterValue(TimerInstancePtr);
	   XScuTimer_Stop(TimerInstancePtr);


	}

	return CntValue;

}


