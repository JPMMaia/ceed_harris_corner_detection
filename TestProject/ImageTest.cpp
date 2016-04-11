#include "stdafx.h"
#include "CppUnitTest.h"
#include "Image.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{		
	TEST_CLASS(ImageTest)
	{
	public:
		
		TEST_METHOD(ImageTestLoad)
		{
			Image image = {};
			Image_Load(&image, L"Resources/TestImage.txt");

			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t j = 0; j < 5; ++j)
				{
					Assert::IsTrue(i * 5 + j == Image_Get(&image, i, j));
				}
			}
		}
	};
}