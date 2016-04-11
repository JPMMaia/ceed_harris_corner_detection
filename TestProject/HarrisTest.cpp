#include "stdafx.h"
#include "CppUnitTest.h"
#include "Harris.h"
#include "ImageTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(HarrisTest)
	{
	public:

		TEST_METHOD(HarrisTestFunction)
		{
			// Load expected image:
			Image expectedImage;
			Image_Load(&expectedImage, L"Resources/OutputImage.txt");

			// Compute actual image:
			Image actualImage;
			{
				Image inputImage;
				Image_Load(&inputImage, L"Resources/InputImage.txt");
				actualImage = Harris(&inputImage);
				Image_Shutdown(&inputImage);
			}

			// Compare images:
			Assert::IsTrue(expectedImage == actualImage);

			// Free resources:
			Image_Shutdown(&actualImage);
			Image_Shutdown(&expectedImage);
		}
	};
}