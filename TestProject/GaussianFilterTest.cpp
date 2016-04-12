#include "stdafx.h"
#include "CppUnitTest.h"
#include "MathUtils.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(GaussianFilterTest)
	{
	public:

		TEST_METHOD(Gaussian1Test)
		{
			// Load expected image:
			MatrixFloat expectedImage;
			MatrixFloat_Load(&expectedImage, L"Resources/CreateGaussianFilterOutputMatrix1.txt");

			// Compute actual image:
			MatrixFloat actualImage = CreateGaussianFilter();

			// Compare images:
			TestUtils::AreEqual(expectedImage, actualImage, 0.001f);

			// Free resources:
			MatrixFloat_Shutdown(&actualImage);
			MatrixFloat_Shutdown(&expectedImage);
		}
	};
}