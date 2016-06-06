#include "Harris.h"
#include "MathUtils.h"

MatrixFloat Harris(const MatrixFloat* input, size_t radius)
{
	MatrixFloat cim;
	{
		MatrixFloat gaussian = CreateGaussianFilter();
		MatrixFloat ix2;
		MatrixFloat iy2;
		MatrixFloat ixy;
		{
			MatrixFloat ix;
			{
				MatrixFloat dx;
				{
					MatrixFloat_Initialize(&dx, 3, 3);

					dx.Data[0] = -1.0f;
					dx.Data[1] = 0.0f;
					dx.Data[2] = 1.0f;

					dx.Data[3] = -1.0f;
					dx.Data[4] = 0.0f;
					dx.Data[5] = 1.0f;

					dx.Data[6] = -1.0f;
					dx.Data[7] = 0.0f;
					dx.Data[8] = 1.0f;
				}

				ix = Convolution2DSame(input, &dx);

				MatrixFloat_Shutdown(&dx);
			}

			MatrixFloat iy;
			{
				MatrixFloat dy;
				{
					MatrixFloat_Initialize(&dy, 3, 3);

					dy.Data[0] = -1.0f;
					dy.Data[1] = -1.0f;
					dy.Data[2] = -1.0f;

					dy.Data[3] = 0.0f;
					dy.Data[4] = 0.0f;
					dy.Data[5] = 0.0f;

					dy.Data[6] = 1.0f;
					dy.Data[7] = 1.0f;
					dy.Data[8] = 1.0f;
				}

				iy = Convolution2DSame(input, &dy);

				MatrixFloat_Shutdown(&dy);
			}

			// ixy:
			{
				MatrixFloat ixiy;
				MatrixFloat_Initialize(&ixiy, ix.Width, ix.Height);
				MatrixFloat_ExecuteElementByElement(&ixiy, &ix, &iy, Multiply);
				ixy = Convolution2DSame(&ixiy, &gaussian);
				MatrixFloat_ForEach(&ixy, &ixy, RaiseToPower2);
				MatrixFloat_Shutdown(&ixiy);
			}

			// ix2:
			{
				MatrixFloat_ForEach(&ix, &ix, RaiseToPower2);
				ix2 = Convolution2DSame(&ix, &gaussian);
			}

			// iy2:
			{
				MatrixFloat_ForEach(&iy, &iy, RaiseToPower2);
				iy2 = Convolution2DSame(&iy, &gaussian);
			}

			MatrixFloat_Shutdown(&iy);
			MatrixFloat_Shutdown(&ix);
		}

		// cim
		{
			// cim:
			{
				MatrixFloat_Initialize(&cim, ix2.Width, ix2.Height);

				// Numerator:
				{
					MatrixFloat_ExecuteElementByElement(&cim, &ix2, &iy2, Multiply);
					MatrixFloat_ExecuteElementByElement(&cim, &cim, &ixy, Minus);
				}

				MatrixFloat denominator;
				{
					MatrixFloat_Initialize(&denominator, ix2.Width, ix2.Height);
					MatrixFloat_ExecuteElementByElement(&denominator, &ix2, &iy2, Plus); // TODO add epsilon?
				}

				MatrixFloat_ExecuteElementByElement(&cim, &cim, &denominator, Divide);
				
				MatrixFloat_Shutdown(&denominator);
			}

			MatrixFloat mx;
			{
				size_t size = 2 * radius + 1;
				MatrixFloat ones;
				{
					MatrixFloat_Initialize(&ones, size, size);
					MatrixFloat_Fill(&ones, 1.0f);
				}
				mx = OrderStatisticFilteringSpecialized(&cim, &ones);
				MatrixFloat_Shutdown(&ones);
			}

			MatrixFloat_ExecuteElementByElement(&cim, &cim, &mx, FindMaxima);

			MatrixFloat_Shutdown(&mx);
		}

		MatrixFloat_Shutdown(&ixy);
		MatrixFloat_Shutdown(&iy2);
		MatrixFloat_Shutdown(&ix2);
		MatrixFloat_Shutdown(&gaussian);
	}

	return cim;
}

float RaiseToPower2(float value)
{
	return value * value;
}

float Plus(float value1, float value2)
{
	return value1 + value2;
}
float Minus(float value1, float value2)
{
	return value1 - value2;
}
float Multiply(float value1, float value2)
{
	return value1 * value2;
}
float Divide(float value1, float value2)
{
	return value1 / value2;
}

float FindMaxima(float value1, float value2)
{
	return (float)((value1 == value2) && (value1 > 1000.0f));
}
