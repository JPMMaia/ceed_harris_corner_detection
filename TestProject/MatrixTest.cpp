#include "stdafx.h"
#include "CppUnitTest.h"
#include "MatrixFloat.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{		
	TEST_CLASS(MatrixTest)
	{
	public:
		
		TEST_METHOD(MatrixTestLoadInt)
		{
			MatrixFloat image = {};
			MatrixFloat_Load(&image, L"Resources/TestMatrixInt.txt");

			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t j = 0; j < 5; ++j)
				{
					Assert::IsTrue(i * 5 + j == MatrixFloat_Get(&image, i, j));
				}
			}
		}

		TEST_METHOD(MatrixTestLoadFloat)
		{
			MatrixFloat image = {};
			MatrixFloat_Load(&image, L"Resources/TestMatrixFloat.txt");

			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t j = 0; j < 5; ++j)
				{
					Assert::AreEqual(0.1f * (i * 5 + j), MatrixFloat_Get(&image, i, j), 0.005f);
				}
			}
		}
	};
}