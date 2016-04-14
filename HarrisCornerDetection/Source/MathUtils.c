#include "MathUtils.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Vector.h"

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
	MatrixFloat matrix2Rotated = Rotate180(matrix2);
	size_t centerX = (size_t)floorf(((float)matrix2Rotated.Width + 1.0f) / 2.0f);
	size_t centerY = (size_t)floorf(((float)matrix2Rotated.Height + 1.0f) / 2.0f);
	size_t left = (size_t)roundf((float)centerX - 1.0f);
	size_t right = (size_t)roundf((float)matrix2Rotated.Width - (float)centerX);
	size_t top = (size_t)roundf((float)centerY - 1.0f);
	size_t bottom = (size_t)roundf((float)matrix2Rotated.Height - (float)centerY);

	MatrixFloat matrixC;
	{
		MatrixFloat_Initialize(&matrixC, matrix1->Width + left + right, matrix1->Height + top + bottom);
		for (size_t i = 0; i < matrixC.Height; ++i)
		{
			for (size_t j = 0; j < matrixC.Width; ++j)
			{
				MatrixFloat_Set(&matrixC, i, j, 0.0f);
			}
		}

		for (size_t i = 1 + top; i <= matrix1->Height + top; ++i)
		{
			for (size_t j = 1 + left; j <= matrix1->Width + left; ++j)
			{
				float value = MatrixFloat_Get(matrix1,(int) i - (int) top - 1, (int) j - (int) left - 1);
				MatrixFloat_Set(&matrixC, (int) i - 1, (int) j - 1, value);
			}
		}
	}

	MatrixFloat output;
	MatrixFloat_Initialize(&output, matrix1->Width, matrix1->Height);
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

					float c  = MatrixFloat_Get(&matrixC, (int)k + (int)q - 1, (int)l + (int)w - 1);
					float r = MatrixFloat_Get(&matrix2Rotated, (int)k - 1, (int)l - 1);

					sum += c * r;
				}
			}

			MatrixFloat_Set(&output, i - 1, j - 1, sum);
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

MatrixFloat OrderStatisticFiltering(MatrixFloat* matrix, size_t order, MatrixFloat* domain)
{
	MatrixFloat output;
	MatrixFloat_Initialize(&output, matrix->Width, matrix->Height);
	
	Vector blockVector;
	Vector_Initialize(&blockVector, domain->Width * domain->Height);

	for (size_t i = 0; i < matrix->Height; ++i)
	{
		for (size_t j = 0; j < matrix->Width; ++j)
		{
			// Add elements of matrix to a vector and order them:
			{
				for (size_t bi = 0; bi < domain->Height; ++bi)
				{
					for (size_t bj = 0; bj < domain->Width; ++bj)
					{
						float value;
						{
							if (i + bi >= matrix->Height || j + bj >= matrix->Width)
								value = 0.0f;
							else
								value = MatrixFloat_Get(matrix, i + bi, j + bj);
						}

						Vector_SetElement(&blockVector, bi * domain->Width + bj, value);
					}
				}

				Vector_OrderAscendent(&blockVector);
			}

			MatrixFloat_Set(&output, i, j, Vector_GetElement(&blockVector, order - 1));
		}
	}

	Vector_Shutdown(&blockVector);

	return output;
}
