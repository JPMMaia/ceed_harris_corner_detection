#include "stdafx.h"
#include "CppUnitTest.h"
#include "Harris.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(HarrisTest)
	{
	public:

		TEST_METHOD(HarrisTestMatrixA)
		{
			// Load expected image:
			MatrixFloat expectedImage;
			MatrixFloat_Load(&expectedImage, L"Resources/HarrisOutputMatrixA.txt");

			// Compute actual image:
			MatrixFloat actualImage;
			{
				MatrixFloat inputImage;
				MatrixFloat_Load(&inputImage, L"Resources/HarrisInputMatrixA.txt");
				actualImage = Harris(&inputImage, 3);
				MatrixFloat_Shutdown(&inputImage);
			}

			// Compare images:
			TestUtils::AreEqual(expectedImage, actualImage, 0.001f);

			// Free resources:
			MatrixFloat_Shutdown(&actualImage);
			MatrixFloat_Shutdown(&expectedImage);
		}

		TEST_METHOD(HarrisTestImage)
		{
			// Load expected image:
			MatrixFloat expectedImage;
			MatrixFloat_Load(&expectedImage, L"Resources/HarrisOutputImage.txt");

			// Compute actual image:
			MatrixFloat actualImage;
			{
				MatrixFloat inputImage;
				MatrixFloat_Load(&inputImage, L"Resources/HarrisInputImage.txt");
				actualImage = Harris(&inputImage, 3);
				MatrixFloat_Shutdown(&inputImage);
			}
			
			// Compare images:
			TestUtils::AreEqual(expectedImage, actualImage, 0.001f);

			// Free resources:
			MatrixFloat_Shutdown(&actualImage);
			MatrixFloat_Shutdown(&expectedImage);
		}
	};
}