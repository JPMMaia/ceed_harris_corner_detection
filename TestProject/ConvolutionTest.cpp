#include "stdafx.h"
#include "CppUnitTest.h"
#include "MathUtils.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestProject
{
	TEST_CLASS(ConvolutionTest)
	{
	private:
		static MatrixFloat s_matrixA;
		static MatrixFloat s_matrixB;
		static MatrixFloat s_matrixC;

	public:
		TEST_CLASS_INITIALIZE(InitializeConvolutionTest)
		{
			// Matrix A:
			{
				MatrixFloat_Initialize(&s_matrixA, 5, 4);

				for (size_t i = 0; i < 4; ++i)
				{
					for (size_t j = 0; j < 5; ++j)
					{
						MatrixFloat_Set(&s_matrixA, i, j, (float)(i * s_matrixA.Width + j));
					}
				}
			}

			// Matrix B:
			{
				MatrixFloat_Initialize(&s_matrixB, 5, 4);

				for (size_t i = 0; i < 4; ++i)
				{
					for (size_t j = 0; j < 5; ++j)
					{
						MatrixFloat_Set(&s_matrixB, i, j, 20.0f + i * s_matrixB.Width + j);
					}
				}
			}

			// Matrix C:
			{
				MatrixFloat_Initialize(&s_matrixC, 3, 3);

				s_matrixC.Data[0] = -1;
				s_matrixC.Data[1] = 0;
				s_matrixC.Data[2] = 1;

				s_matrixC.Data[3] = -1;
				s_matrixC.Data[4] = 0;
				s_matrixC.Data[5] = 1;

				s_matrixC.Data[6] = -1;
				s_matrixC.Data[7] = 0;
				s_matrixC.Data[8] = 1;
			}
		}
		TEST_CLASS_CLEANUP(ShutdownConvolutionTest)
		{
			MatrixFloat_Shutdown(&s_matrixC);
			MatrixFloat_Shutdown(&s_matrixB);
			MatrixFloat_Shutdown(&s_matrixA);
		}

		static void TestConvolve(const MatrixFloat& inputVector1, const MatrixFloat& inputVector2, const MatrixFloat& expectedVector)
		{
			// Compute actual vector:
			MatrixFloat actualVector = ConvolutionSame(&inputVector1, &inputVector2);

			// Compare vectors:
			TestUtils::AreEqual(expectedVector, actualVector, 0.001f);

			MatrixFloat_Shutdown(&actualVector);
		}

		static void TestConvolve2D(const MatrixFloat& inputMatrix1, const MatrixFloat& inputMatrix2, const MatrixFloat& expectedMatrix)
		{
			// Compute actual matrix:
			MatrixFloat actualMatrix = Convolution2DSame(&inputMatrix1, &inputMatrix2);

			// Compare matrices:
			TestUtils::AreEqual(expectedMatrix, actualMatrix, 0.001f);

			MatrixFloat_Shutdown(&actualMatrix);
		}

		TEST_METHOD(ConvolutionSameTest)
		{
			MatrixFloat vector1;
			MatrixFloat_Initialize(&vector1, 3, 1);
			vector1.Data[0] = 1;
			vector1.Data[1] = 0;
			vector1.Data[2] = 1;

			MatrixFloat vector2;
			MatrixFloat_Initialize(&vector2, 2, 1);
			vector2.Data[0] = 2;
			vector2.Data[1] = 7;

			MatrixFloat expectedVector;
			MatrixFloat_Initialize(&expectedVector, 4, 1);
			expectedVector.Data[0] = 2;
			expectedVector.Data[1] = 7;
			expectedVector.Data[2] = 2;
			expectedVector.Data[3] = 7;

			TestConvolve(vector1, vector2, expectedVector);

			MatrixFloat_Shutdown(&vector2);
			MatrixFloat_Shutdown(&vector1);
		}

		TEST_METHOD(Convolution2DSameImageTest)
		{
			// Load expected image:
			MatrixFloat expectedImage;
			MatrixFloat_Load(&expectedImage, L"Resources/Convolve2DSameOutputImage.txt");

			// Compute actual image:
			MatrixFloat actualImage;
			{
				MatrixFloat inputImage;
				MatrixFloat_Load(&inputImage, L"Resources/Convolve2DSameInputImage.txt");
				actualImage = Convolution2DSame(&inputImage, &s_matrixC);
				MatrixFloat_Shutdown(&inputImage);
			}

			// Compare images:
			TestUtils::AreEqual(expectedImage, actualImage, 0.001f);

			// Free resources:
			MatrixFloat_Shutdown(&actualImage);
			MatrixFloat_Shutdown(&expectedImage);
		}

		TEST_METHOD(Convolution2DSameAConvATest)
		{
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, L"Resources/Convolve2DSameAConvA.txt");

			TestConvolve2D(s_matrixA, s_matrixA, expectedMatrix);
		}

		TEST_METHOD(Convolution2DSameAConvBTest)
		{
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, L"Resources/Convolve2DSameAConvB.txt");

			TestConvolve2D(s_matrixA, s_matrixB, expectedMatrix);
		}

		TEST_METHOD(Convolution2DSameAConvCTest)
		{
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, L"Resources/Convolve2DSameAConvC.txt");

			TestConvolve2D(s_matrixA, s_matrixC, expectedMatrix);
		}

		TEST_METHOD(Convolution2DSameBConvATest)
		{
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, L"Resources/Convolve2DSameBConvA.txt");

			TestConvolve2D(s_matrixB, s_matrixA, expectedMatrix);
		}

		TEST_METHOD(Convolution2DSameCConvATest)
		{
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, L"Resources/Convolve2DSameCConvA.txt");

			TestConvolve2D(s_matrixC, s_matrixA, expectedMatrix);
		}
	};
	MatrixFloat ConvolutionTest::s_matrixA = {};
	MatrixFloat ConvolutionTest::s_matrixB = {};
	MatrixFloat ConvolutionTest::s_matrixC = {};
}