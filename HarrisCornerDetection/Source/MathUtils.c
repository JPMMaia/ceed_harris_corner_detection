#include "MathUtils.h"

#include <float.h>

MatrixFloat Convolution2DSame(const MatrixFloat* matrix1, const MatrixFloat* matrix2)
{
	MatrixFloat output;
	MatrixFloat_Initialize(&output, matrix1->Width, matrix2->Height);
	
	// k -> [-inf, inf]
	// k -> [FLT_MIN, FLT_MAX]
	// range -> (FLT_MAX - FLT_MIN) / NumIterations
	

	// Input values: matrix a, matrix b
	// Output values: matrix c
	// c(n1, n2) := sum(k1, -inf, inf, sum(k2, -inf, inf, f(n1, n2, k1, k2)))
	// f(n1, n2, k1, k2) := a(k1, k2) * b(n1 - k1, n2 - k2)
	for (size_t n1 = 0; n1 < output.Height; ++n1)
	{
		for (size_t n2 = 0; n2 < output.Width; ++n2)
		{
			float sum = 0.0f;

			// for (size_t k1 = -MIN; k1 < inf; ++k1)
			{
				// for(size_t k2 = -inf; k2 < inf; ++k2)	
				{
					sum += MatrixFloat_Get(matrix1, k1, k2) * MatrixFloat_Get(matrix2, n1 - k1, n2 - k2);
				}
			}

			MatrixFloat_Set(&output, n1, n2, sum);
		}
	}


	return output;
}

MatrixFloat CreateGaussianFilter()
{
	MatrixFloat output;
	MatrixFloat_Initialize(&output, 6, 6);

	output.Data[0] = 0.0003083365136427076f;
	output.Data[1] = 0.002278315796654662f;
	output.Data[2] = 0.00619310442953756f;
	output.Data[3] = 0.00619310442953756f;
	output.Data[4] = 0.002278315796654662f;
	output.Data[5] = 0.0003083365136427076f;
	output.Data[6] = 0.002278315796654662f;
	output.Data[7] = 0.01683460323256117f;
	output.Data[8] = 0.04576119605638893f;
	output.Data[9] = 0.04576119605638893f;
	output.Data[10] = 0.01683460323256117f;
	output.Data[11] = 0.002278315796654662f;
	output.Data[12] = 0.00619310442953756f;
	output.Data[13] = 0.04576119605638893f;
	output.Data[14] = 0.1243918276886338f;
	output.Data[15] = 0.1243918276886338f;
	output.Data[16] = 0.04576119605638893f;
	output.Data[17] = 0.00619310442953756f;
	output.Data[18] = 0.00619310442953756f;
	output.Data[19] = 0.04576119605638893f;
	output.Data[20] = 0.1243918276886338f;
	output.Data[21] = 0.1243918276886338f;
	output.Data[22] = 0.04576119605638893f;
	output.Data[23] = 0.00619310442953756f;
	output.Data[24] = 0.002278315796654662f;
	output.Data[25] = 0.01683460323256117f;
	output.Data[26] = 0.04576119605638893f;
	output.Data[27] = 0.04576119605638893f;
	output.Data[28] = 0.01683460323256117f;
	output.Data[29] = 0.002278315796654662f;
	output.Data[30] = 0.0003083365136427076f;
	output.Data[31] = 0.002278315796654662f;
	output.Data[32] = 0.00619310442953756f;
	output.Data[33] = 0.00619310442953756f;
	output.Data[34] = 0.002278315796654662f;
	output.Data[35] = 0.0003083365136427076f;

	return output;
}
