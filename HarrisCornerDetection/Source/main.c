//#include <arm_neon.h>
#include "MatrixFloat.h"
#include "Harris.h"
#include "Flags.h"

#define ROWS 1024 //168
#define COLUMNS 768 //300

#define _Version0
#define NUMBER_OF_TESTS 1

unsigned long long c_totalRunTime = 0;
unsigned int c_numberOfCalls = 0;
unsigned long long c_countValue = 0;

int main()
{
	{
		xil_printf("Begin\n");

		MatrixFloat inputImage;
		MatrixFloat_Initialize(&inputImage, COLUMNS, ROWS);
		xil_printf("Initialized\n");


#ifdef CLOCK_GLOBAL

		// Start clock:
		start_time();

 #endif

		// Harris function:
		MatrixFloat outputImage = Harris(&inputImage, 3);

#ifdef CLOCK_GLOBAL

		// Stop clock:
		stop_time();

		// Ticks elapsed:
		CORE_TICKS ticksElapsed = get_core_ticks();
        xil_printf("==== Number of ticks elapsed for Harris: %d\n", ticksElapsed);

        // Time elapsed:
        timerepr timeElapsed = time_in_secs(ticksElapsed);
        printf("Elapsed time (s): %f\n", (float) timeElapsed);
        timeElapsed = time_in_msecs(ticksElapsed);
        printf("Elapsed time (ms): %f\n", (float) timeElapsed);
        timeElapsed = time_in_usecs(ticksElapsed);
        printf("Elapsed time (us): %f\n", (float) timeElapsed);

#endif

        MatrixFloat_Shutdown(&outputImage);
		MatrixFloat_Shutdown(&inputImage);

		xil_printf("End\n");
	}

	return 0;
}
