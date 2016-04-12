#include "stdafx.h"
#include "CppUnitTest.h"
#include "MathUtils.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(ConvolutionTest)
	{
	private:
		static MatrixFloat s_dx;

	public:
		TEST_CLASS_INITIALIZE(InitializeConvolutionTest)
		{
			MatrixFloat_Initialize(&s_dx, 3, 3);

			s_dx.Data[0] = -1;
			s_dx.Data[1] = 0;
			s_dx.Data[2] = 1;

			s_dx.Data[3] = -1;
			s_dx.Data[4] = 0;
			s_dx.Data[5] = 1;

			s_dx.Data[6] = -1;
			s_dx.Data[7] = 0;
			s_dx.Data[8] = 1;
		}
		TEST_CLASS_CLEANUP(ShutdownConvolutionTest)
		{
			MatrixFloat_Shutdown(&s_dx);
		}

		TEST_METHOD(Convolution2DSameTest)
		{
			// Load expected image:
			MatrixFloat expectedImage;
			MatrixFloat_Load(&expectedImage, L"Resources/Convolve2DSameOutputImage.txt");

			// Compute actual image:
			MatrixFloat actualImage;
			{
				MatrixFloat inputImage;
				MatrixFloat_Load(&inputImage, L"Resources/Convolve2DSameInputImage.txt");
				actualImage = Convolution2DSame(&inputImage, &s_dx);
				MatrixFloat_Shutdown(&inputImage);
			}

			// Compare images:
			TestUtils::AreEqual(expectedImage, actualImage, 0.001f);

			// Free resources:
			MatrixFloat_Shutdown(&actualImage);
			MatrixFloat_Shutdown(&expectedImage);
		}
	};
	MatrixFloat ConvolutionTest::s_dx = {};

}