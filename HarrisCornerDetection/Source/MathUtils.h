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

#if defined(_OPTIMIZATION_ORDER_STATISTIC_FILTERING_SPECIALIZED)
	MatrixFloat OrderStatisticFilteringSpecialized(MatrixFloat* matrix, MatrixFloat* domain);
#else
	MatrixFloat OrderStatisticFiltering(MatrixFloat* matrix, size_t order, MatrixFloat* domain);
#endif

	float Convolution2DSameAuxiliary(size_t i, size_t j, size_t width, size_t height, float* __restrict matrix1, size_t matrix1Width, float* __restrict matrix2, size_t matrix2Width);

#ifdef __cplusplus
}
#endif
