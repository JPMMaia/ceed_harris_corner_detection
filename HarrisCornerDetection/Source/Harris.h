#pragma once

#include "MatrixFloat.h"

#ifdef __cplusplus
extern "C"
{
#endif

		MatrixFloat Harris(const MatrixFloat* image, size_t radius);
		static void RaiseToPower2(float* pValue);
		static float Plus(float value1, float value2);
		static float Minus(float value1, float value2);
		static float Multiply(float value1, float value2);
		static float Divide(float value1, float value2);
		static float FindMaxima(float value1, float value2);
		

#ifdef __cplusplus
}
#endif