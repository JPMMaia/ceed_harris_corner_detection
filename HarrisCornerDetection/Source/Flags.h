#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "timers.h"

#define _ZEDBOARD

#ifdef _ZEDBOARD

// === Defines ===
//#define CLOCK_GLOBAL
//#define CLOCK_ORDER_STATISTIC_FILTERING
//#define CLOCK_CONVOLUTION2D

// === Includes ===
//#include <xil_io.h>

#endif

// === Optimization defines ===

#define _OPTIMIZATION_ORDER_STATISTIC_FILTERING_SPECIALIZED

#define _OPTIMIZATION_GET

#define _OPTIMIZATION_CONVOLUTION_000
#define _OPTIMIZATION_CONVOLUTION_010
//#define _OPTIMIZATION_CONVOLUTION_011
//#define _OPTIMIZATION_CONVOLUTION_012
//#define _OPTIMIZATION_CONVOLUTION_020
#define _OPTIMIZATION_CONVOLUTION_021
