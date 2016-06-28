#include "MathUtils.h"

#include <math.h>
#include <stdlib.h>
#include "Vector.h"
#include <float.h>
#include <string.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#ifdef CLOCK_CONVOLUTION2D
CORE_TICKS c_convolution2DTotalTicksElapsed = 0;
#endif

#ifdef CLOCK_ORDER_STATISTIC_FILTERING
CORE_TICKS c_orderStatisticsTotalTicksElapsed = 0;
#endif

MatrixFloat Rotate180(const MatrixFloat* matrix)
{
	MatrixFloat output;
	MatrixFloat_Initialize(&output, matrix->Width, matrix->Height);

	for (size_t i = 0; i < matrix->Height; ++i)
	{
		for (size_t j = 0; j < matrix->Width; ++j)
		{
			MatrixFloat_Set(&output, i, j, MatrixFloat_Get(matrix, (int)matrix->Height - 1 - (int)i, (int)matrix->Width - 1 - (int)j));
		}
	}

	return output;
}

MatrixFloat ConvolutionSame(const MatrixFloat* vector1, const MatrixFloat* vector2)
{
	// u = [1 0 1]
	// v = [2 7]
	// w = conv(u, v) = [2 7 2 7]

	// m = l(u)
	// n = l(v)
	// len(w) = m + n - 1
	// w(k) = sum(j, max(1, k+1-n):1:min(k,m), u(j) * v(k - j + 1)

	MatrixFloat output;
	MatrixFloat_Initialize(&output, vector1->Width + vector2->Height, 1);

	for (size_t k = 1; k <= output.Width; ++k)
	{
		float sum = 0.0f;

		size_t limit = min((int)k, (int)vector1->Width);
		for (size_t j = max(1, (int)k + 1 - (int)vector2->Width); j <= limit; ++j)
		{
			sum += vector1->Data[j - 1] * vector2->Data[k - j + 1 - 1];
		}

		output.Data[k - 1] = sum;
	}

	return output;
}

MatrixFloat Convolution2DSame(const MatrixFloat* matrix1, const MatrixFloat* matrix2)
{
#ifdef CLOCK_CONVOLUTION2D
	// Start clock:
	start_time();
#endif

	MatrixFloat matrix2Rotated = Rotate180(matrix2);
	size_t centerX = (size_t)floorf(((float)matrix2Rotated.Width + 1.0f) / 2.0f);
	size_t centerY = (size_t)floorf(((float)matrix2Rotated.Height + 1.0f) / 2.0f);
	size_t left = (size_t)roundf((float)centerX - 1.0f);
	size_t right = (size_t)roundf((float)matrix2Rotated.Width - (float)centerX);
	size_t top = (size_t)roundf((float)centerY - 1.0f);
	size_t bottom = (size_t)roundf((float)matrix2Rotated.Height - (float)centerY);

	MatrixFloat matrixC;
	{
		// Reserve memory and initialize width and height:
		MatrixFloat_Initialize(&matrixC, matrix1->Width + left + right, matrix1->Height + top + bottom);

		// Initialize all elements to 0:
#if defined(_OPTIMIZATION_CONVOLUTION_000)
		memset(matrixC.Data, 0, matrixC.Width * matrixC.Height * sizeof(float));
#elif defined(_OPTIMIZATION_CONVOLUTION_001)
		// TODO try loop coalescing
#else
		for (size_t i = 0; i < matrixC.Height; ++i)
			for (size_t j = 0; j < matrixC.Width; ++j)
				MatrixFloat_Set(&matrixC, i, j, 0.0f);
#endif

#if defined(_OPTIMIZATION_CONVOLUTION_010)
		// Loop normalization:
		float* matrixCArray = matrixC.Data;
		size_t matrixCWidth = matrixC.Width;
		float* matrix1Array = matrix1->Data;
		size_t matrix1Width = matrix1->Width;
		for (size_t i = 0; i < matrix1->Height; ++i)
		{
			size_t index0 = (i + top) * matrixCWidth + left;
			size_t index1 = i * matrix1Width;
			for (size_t j = 0; j < matrix1->Width; ++j)
			{
				matrixCArray[index0 + j] = matrix1Array[index1 + j];
			}
		}
#elif defined(_OPTIMIZATION_CONVOLUTION_011)
		// Loop coalescing:
		float* matrixCArray = matrixC.Data;
		size_t matrixCWidth = matrixC.Width;
		float* matrix1Array = matrix1->Data;
		size_t matrix1Width = matrix1->Width;
		size_t matrix1Height = matrix1->Height;
		for (size_t t = 0; t < matrix1Height * matrix1Width; ++t)
		{
			size_t i = t / matrix1Width;
			size_t j = t % matrix1Width;

			size_t index0 = (i + top) * matrixCWidth + left;
			size_t index1 = i * matrix1Width;
			matrixCArray[index0 + j] = matrix1Array[index1 + j];
		}

#elif defined(_OPTIMIZATION_CONVOLUTION_012)
		float* matrixCArray = matrixC.Data;
		size_t matrixCWidth = matrixC.Width;
		float* matrix1Array = matrix1->Data;
		size_t matrix1Width = matrix1->Width;
		size_t matrix1Height = matrix1->Height;
		for (size_t i = 0; i < matrix1Height; ++i)
		{
			size_t index0 = (i + top) * matrixCWidth + left;
			size_t index1 = i * matrix1Width;
			memcpy(&matrixCArray[index0], &matrix1Array[index1], matrix1Width * sizeof(float));
		}
#else
		for (size_t i = 1 + top; i <= matrix1->Height + top; ++i)
		{
			for (size_t j = 1 + left; j <= matrix1->Width + left; ++j)
			{
				float value = MatrixFloat_Get(matrix1, (int)i - (int)top - 1, (int)j - (int)left - 1);
				MatrixFloat_Set(&matrixC, (int)i - 1, (int)j - 1, value);
			}
		}
#endif
	}

	// Allocate memory and initialize width and height of matrix:
	MatrixFloat output;
	MatrixFloat_Initialize(&output, matrix1->Width, matrix1->Height);

#if defined(_OPTIMIZATION_CONVOLUTION_020)
	{
		float* outputArray = matrixC.Data;
		size_t outputArrayWidth = matrixC.Width;
		float* matrix2RotatedArray = matrix2Rotated.Data;
		size_t matrix2RotatedWidth = matrix2Rotated.Width;
		for (size_t i = 0; i < matrix1->Height; ++i)
		{
			for (size_t j = 0; j < matrix1->Width; ++j)
			{
				float sum = 0.0f;

				for (size_t k = 0; k < matrix2->Height; ++k)
				{
					size_t index0 = (k + i) * outputArrayWidth + j;
					size_t index1 = k * matrix2RotatedWidth;

					for (size_t l = 0; l < matrix2->Width; ++l)
					{
						float c = outputArray[index0 + l];
						float r = matrix2RotatedArray[index1 + l];

						sum += c * r;
					}
				}

				MatrixFloat_Set(&output, i, j, sum);
			}
		}
	}
#elif defined(_OPTIMIZATION_CONVOLUTION_021)
	{
		float* outputArray = output.Data;
		size_t outputArrayWidth = output.Width;
		float* matrixCArray = matrixC.Data;
		size_t matrixCWidth = matrixC.Width;
		float* matrix2RotatedArray = matrix2Rotated.Data;
		size_t matrix2RotatedWidth = matrix2Rotated.Width;
		for (size_t i = 0; i < matrix1->Height; ++i)
		{
			for (size_t j = 0; j < matrix1->Width; ++j)
			{
				float sum = 0.0f;

				for (size_t k = 0; k < matrix2->Height; ++k)
				{
					size_t index0 = (k + i) * matrixCWidth + j;
					size_t index1 = k * matrix2RotatedWidth;

					for (size_t l = 0; l < matrix2->Width; ++l)
					{
						float c = matrixCArray[index0 + l];
						float r = matrix2RotatedArray[index1 + l];

						sum += c * r;
					}
				}

				outputArray[i * outputArrayWidth + j] = sum;
			}
		}
	}
#elif defined(_OPTIMIZATION_CONVOLUTION_022)
	{
		float* outputArray = output.Data;
		size_t outputArrayWidth = output.Width;
		float* matrixCArray = matrixC.Data;
		size_t matrixCWidth = matrixC.Width;
		float* matrix2RotatedArray = matrix2Rotated.Data;
		size_t matrix2RotatedWidth = matrix2Rotated.Width;
		for (size_t i = 0; i < matrix1->Height; ++i)
		{
			for (size_t j = 0; j < matrix1->Width; ++j)
			{
				outputArray[i * outputArrayWidth + j] = Convolution2DSameAuxiliary(i, j, matrix2->Width, matrix2->Height, matrixCArray, matrixCWidth, matrix2RotatedArray, matrix2RotatedWidth);
			}
		}
	}
#else
	MatrixFloat* pMatrixC = &matrixC;
	MatrixFloat* pMatrix2Rotated = &matrix2Rotated;
	// i -> [1, rowsA]
	for (size_t i = 1; i <= matrix1->Height; ++i)
	{
		// q -> [0, rowsA]
		size_t q = i - 1;

		// j -> [1, columnsA]
		for (size_t j = 1; j <= matrix1->Width; ++j)
		{
			// w -> [0, columnsA]
			size_t w = j - 1;

			float sum = 0.0f;

			// k -> [1, rowsB]
			for (size_t k = 1; k <= matrix2->Height; ++k)
			{
				// l -> [1, columnsB]
				for (size_t l = 1; l <= matrix2->Width; ++l)
				{
					// k + q -> [1, rowsA + rowsB]
					// l + w -> [1, columnsA + columnsB]
					// k - 1 -> [0, rowsB - 1]
					// l - 1 -> [0, columnsB - 1]

					float c = MatrixFloat_Get(pMatrixC, (int)k + (int)q - 1, (int)l + (int)w - 1);
					float r = MatrixFloat_Get(pMatrix2Rotated, (int)k - 1, (int)l - 1);

					sum += c * r;
				}
			}

			MatrixFloat_Set(&output, i - 1, j - 1, sum);
		}
}
#endif

#ifdef CLOCK_CONVOLUTION2D
	// Stop clock:
	stop_time();

	// Ticks elapsed:
	CORE_TICKS ticksElapsed = get_core_ticks();
	printf("==== Number of ticks elapsed for Convolution2D: %d\n", ticksElapsed);
	c_convolution2DTotalTicksElapsed += ticksElapsed;
	printf("==== Number of total ticks elapsed for Convolution2D: %d\n", c_convolution2DTotalTicksElapsed);

	// Time elapsed:
	timerepr timeElapsed = time_in_secs(ticksElapsed);
	printf("Elapsed time (s): %f\n", (float)timeElapsed);
	timeElapsed = time_in_msecs(ticksElapsed);
	printf("Elapsed time (ms): %f\n", (float)timeElapsed);
	timeElapsed = time_in_usecs(ticksElapsed);
	printf("Elapsed time (us): %f\n", (float)timeElapsed);
	timeElapsed = time_in_usecs(c_convolution2DTotalTicksElapsed);
	printf("Total elapsed time (us): %f\n", (float)timeElapsed);
#endif

	return output;
}
float Convolution2DSameAuxiliary(size_t i, size_t j, size_t width, size_t height, float* __restrict matrix1, size_t matrix1Width, float* __restrict matrix2, size_t matrix2Width)
{
	float sum = 0.0f;

	for (size_t k = 0; k < height; ++k)
	{
		size_t index0 = (k + i) * matrix1Width + j;
		size_t index1 = k * matrix2Width;

		for (size_t l = 0; l < width; ++l)
		{
			float c = matrix1[index0 + l];
			float r = matrix2[index1 + l];

			sum += c * r;
		}
	}

	return sum;
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

#if defined(_OPTIMIZATION_ORDER_STATISTIC_FILTERING_SPECIALIZED)
MatrixFloat OrderStatisticFilteringSpecialized(MatrixFloat* matrix, MatrixFloat* domain)
{
#ifdef CLOCK_ORDER_STATISTIC_FILTERING

	// Start clock:
	start_time();

#endif

	MatrixFloat output;
	MatrixFloat_Initialize(&output, matrix->Width, matrix->Height);

	for (size_t i = 0; i < matrix->Height; ++i)
	{
		for (size_t j = 0; j < matrix->Width; ++j)
		{
			// Find maximum value:
			float maximumValue = FLT_MIN;
			{
				for (int32_t bi = (int32_t)i - ((int32_t)domain->Height - 1) / 2; bi <= (int32_t)i + (int32_t)domain->Height / 2; ++bi)
				{
					for (int32_t bj = (int32_t)j - ((int32_t)domain->Width - 1) / 2; bj <= (int32_t)j + (int32_t)domain->Width / 2; ++bj)
					{
						if (bi < 0 || bi >= matrix->Height || bj < 0 || bj >= matrix->Width)
							continue;

						float value = matrix->Data[bi * matrix->Width + bj];
						if (value > maximumValue)
							maximumValue = value;
					}
				}
			}

			// Set matrix element:
			MatrixFloat_Set(&output, i, j, maximumValue);
		}
	}

#ifdef CLOCK_ORDER_STATISTIC_FILTERING

	// Stop clock:
	stop_time();

	// Ticks elapsed:
	CORE_TICKS ticksElapsed = get_core_ticks();
	printf("==== Number of ticks elapsed for OrderStatisticFilteringSpecialized: %d\n", ticksElapsed);
	c_orderStatisticsTotalTicksElapsed += ticksElapsed;
	printf("==== Number of total ticks elapsed for OrderStatisticFilteringSpecialized: %d\n", c_orderStatisticsTotalTicksElapsed);

	// Time elapsed:
	timerepr timeElapsed = time_in_secs(ticksElapsed);
	printf("Elapsed time (s): %f\n", (float)timeElapsed);
	timeElapsed = time_in_msecs(ticksElapsed);
	printf("Elapsed time (ms): %f\n", (float)timeElapsed);
	timeElapsed = time_in_usecs(ticksElapsed);
	printf("Elapsed time (us): %f\n", (float)timeElapsed);
	timeElapsed = time_in_usecs(c_orderStatisticsTotalTicksElapsed);
	printf("Total elapsed time (us): %f\n", (float)timeElapsed);

#endif

	return output;
}
#else
MatrixFloat OrderStatisticFiltering(MatrixFloat* matrix, size_t order, MatrixFloat* domain)
{
#ifdef CLOCK_ORDER_STATISTIC_FILTERING

	// Start clock:
	start_time();

#endif

	MatrixFloat output;
	MatrixFloat_Initialize(&output, matrix->Width, matrix->Height);

	Vector blockVector;

	Vector_Initialize(&blockVector, domain->Width * domain->Height);

	// 2 -> [0, 1], [1, 2]
	// 3 -> [-1, 1], [0, 2],
	// 4 -> [-1, 2], [0, 3],
	// 5 -> [-2, 2], [-1, 3]
	// center -> 0, right -> floor(size / 2), left -> -(size - 1) / 2
	// center -> 1, right -> center + floor(size / 2), left -> center - (size - 1) / 2

	for (size_t i = 0; i < matrix->Height; ++i)
	{
		for (size_t j = 0; j < matrix->Width; ++j)
		{
			// Add elements of matrix to a vector and order them:
			{
				for (int32_t bi = (int32_t)i - ((int32_t)domain->Height - 1) / 2; bi <= (int32_t)i + (int32_t)domain->Height / 2; ++bi)
				{
					for (int32_t bj = (int32_t)j - ((int32_t)domain->Width - 1) / 2; bj <= (int32_t)j + (int32_t)domain->Width / 2; ++bj)
					{
						float value;
						{
							if (bi < 0 || bi >= matrix->Height || bj < 0 || bj >= matrix->Width)
								value = 0.0f;
							else
								value = MatrixFloat_Get(matrix, bi, bj);
						}

						Vector_AddElement(&blockVector, value);
					}
				}

				//Vector_OrderAscendent(&blockVector);
				Vector_OrderQuicksort(&blockVector);
			}

			MatrixFloat_Set(&output, i, j, Vector_GetElement(&blockVector, order - 1));
			Vector_Clear(&blockVector);
		}
	}

	Vector_Shutdown(&blockVector);

#ifdef CLOCK_ORDER_STATISTIC_FILTERING

	// Stop clock:
	stop_time();

	// Ticks elapsed:
	CORE_TICKS ticksElapsed = get_core_ticks();
	printf("==== Number of ticks elapsed for OrderStatisticFiltering: %d\n", ticksElapsed);
	c_orderStatisticsTotalTicksElapsed += ticksElapsed;
	printf("==== Number of total ticks elapsed for OrderStatisticFiltering: %d\n", c_orderStatisticsTotalTicksElapsed);

	// Time elapsed:
	timerepr timeElapsed = time_in_secs(ticksElapsed);
	printf("Elapsed time (s): %f\n", (float)timeElapsed);
	timeElapsed = time_in_msecs(ticksElapsed);
	printf("Elapsed time (ms): %f\n", (float)timeElapsed);
	timeElapsed = time_in_usecs(ticksElapsed);
	printf("Elapsed time (us): %f\n", (float)timeElapsed);
	timeElapsed = time_in_usecs(c_orderStatisticsTotalTicksElapsed);
	printf("Total elapsed time (us): %f\n", (float)timeElapsed);

#endif

	return output;
}
#endif
