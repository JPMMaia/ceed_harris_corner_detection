#ifndef MATLAB_UTILS_H_
#define MATLAB_UTILS_H_

#include <stdio.h>
#include <math.h>

void rotateVerticalHorizontal(double ** matrix, double ** matrixResult, unsigned int rows, unsigned int columns);
void convolve(double ** matrixA, double ** matrixK, double ** matrixB, unsigned int sizeA[2], unsigned int sizeK[2]);
int fix(double value);
double ** fspecial(double length, unsigned int sigma, unsigned int & rows, unsigned int & columns);
#endif

