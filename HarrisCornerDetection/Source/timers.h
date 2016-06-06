
/*******************************************************************************/
/*                                H E A D E R                                  */
/*******************************************************************************/

// File Name		: timers.h
// File Type		: Header file
// Author		: Shay Gal-On, EEMBC
// Modified by		: Sven Andersson ZooCad Consulting
// Processor		: ARM Cortex-A9
// Evaluation Board	: ZedBoard
// Date			: 2014-02-25

// version adapted by João Cardoso


#ifndef TIMERS_H
#define TIMERS_H

/*******************************************************************************/
/*                            I N C L U D E S                                  */
/*******************************************************************************/
//#include <time.h>


/*******************************************************************************/
/*                             T Y P E D E F S                                 */
/*******************************************************************************/

typedef signed short 	int16;
typedef unsigned short 	uint16;
typedef signed int 	int32;
typedef unsigned int 	uint32;
typedef float timerepr;


/*******************************************************************************/
/*                             D E F I N E S                                   */
/*******************************************************************************/

// These defines are used for the ARM Cortex-A9 CPU
// Define type of return from the timing functions.

typedef uint32 CORE_TICKS;



/*******************************************************************************/
/*                             FUNCTIONS                             */
/*******************************************************************************/
timerepr time_in_secs(CORE_TICKS ticks);
timerepr time_in_msecs(CORE_TICKS ticks);
timerepr time_in_usecs(CORE_TICKS ticks);

CORE_TICKS get_core_ticks(void);

void start_time(void);
void stop_time(void);

#endif /* TIMERS_H */
