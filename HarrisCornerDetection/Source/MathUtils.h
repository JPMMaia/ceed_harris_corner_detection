#pragma once

#include "MatrixFloat.h"

#ifdef __cplusplus
extern "C"
{
#endif

	MatrixFloat Rotate180(const MatrixFloat* matrix);
	MatrixFloat ConvolutionSame(const MatrixFloat* vector1, const MatrixFloat* vector2);
	MatrixFloat Convolution2DSame(const MatrixFloat* matrix1, const MatrixFloat* matrix2);
	MatrixFloat CreateGaussianFilter();
	void OrderStatisticFiltering(MatrixFloat* matrix);

#ifdef __cplusplus
}
#endif