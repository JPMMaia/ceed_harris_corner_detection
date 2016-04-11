#pragma once

#include "MatrixFloat.h"

#ifdef __cplusplus
extern "C"
{
#endif

	MatrixFloat Convolution2DSame(const MatrixFloat* matrix1, const MatrixFloat* matrix2);
	MatrixFloat CreateGaussianFilter();
	void OrderStatisticFiltering(MatrixFloat* matrix);

#ifdef __cplusplus
}
#endif