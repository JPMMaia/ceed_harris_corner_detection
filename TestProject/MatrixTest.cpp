#include "stdafx.h"
#include "CppUnitTest.h"
#include "MatrixFloat.h"
#include "MatrixTestUtils.h"

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

			MatrixFloat_Shutdown(&image);
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

			MatrixFloat_Shutdown(&image);
		}

		TEST_METHOD(MatrixTestCopy)
		{
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, L"Resources/TestMatrixFloat.txt");

			MatrixFloat actualMatrix;
			MatrixFloat_Copy(&actualMatrix, &expectedMatrix);

			TestUtils::AreEqual(expectedMatrix, actualMatrix, 0.001f);

			MatrixFloat_Shutdown(&actualMatrix);
			MatrixFloat_Shutdown(&expectedMatrix);
		}

		TEST_METHOD(MatrixTestForEach)
		{
			MatrixFloat inputMatrix;
			{
				MatrixFloat_Initialize(&inputMatrix, 2, 2);

				inputMatrix.Data[0] = 0;
				inputMatrix.Data[1] = 1;
				inputMatrix.Data[2] = 2;
				inputMatrix.Data[3] = 3;
			}

			MatrixFloat expectedMatrix;
			{
				MatrixFloat_Initialize(&expectedMatrix, 2, 2);

				expectedMatrix.Data[0] = 0;
				expectedMatrix.Data[1] = 1;
				expectedMatrix.Data[2] = 4;
				expectedMatrix.Data[3] = 9;
			}

			MatrixFloat_ForEach(
				&inputMatrix,
				&inputMatrix,
				[](float value)
				{
					return value * value;
				}
			);

			TestUtils::AreEqual(expectedMatrix, inputMatrix, 0.001f);

			MatrixFloat_Shutdown(&expectedMatrix);
			MatrixFloat_Shutdown(&inputMatrix);
		}

		TEST_METHOD(MatrixTestExecuteElementByElement)
		{
			MatrixFloat inputMatrix1;
			{
				MatrixFloat_Initialize(&inputMatrix1, 2, 2);

				inputMatrix1.Data[0] = 0;
				inputMatrix1.Data[1] = 1;
				inputMatrix1.Data[2] = 2;
				inputMatrix1.Data[3] = 3;
			}
			MatrixFloat inputMatrix2;
			{
				MatrixFloat_Initialize(&inputMatrix2, 2, 2);

				inputMatrix2.Data[0] = 4;
				inputMatrix2.Data[1] = 5;
				inputMatrix2.Data[2] = 6;
				inputMatrix2.Data[3] = 7;
			}
			MatrixFloat expectedMatrix;
			{
				MatrixFloat_Initialize(&expectedMatrix, 2, 2);

				expectedMatrix.Data[0] = 0;
				expectedMatrix.Data[1] = 5;
				expectedMatrix.Data[2] = 12;
				expectedMatrix.Data[3] = 21;
			}

			MatrixFloat_ExecuteElementByElement(
				&inputMatrix1,
				&inputMatrix1, 
				&inputMatrix2,
				[](float value1, float value2)
				{
					return value1 * value2;
				}
			);

			TestUtils::AreEqual(expectedMatrix, inputMatrix1, 0.0001f);
		}

		TEST_METHOD(MatrixTestFill)
		{
			MatrixFloat matrix;
			MatrixFloat_Initialize(&matrix, 5, 5);

			const auto value = 2.5313f;
			MatrixFloat_Fill(&matrix, value);

			for (size_t i = 0; i < matrix.Height; ++i)
			{
				for (size_t j = 0; j < matrix.Width; ++j)
				{
					Assert::AreEqual(value, MatrixFloat_Get(&matrix, i, j), 0.00000005f, TestUtils::MakeString(L"[i, j]: ", i, " , ", j).c_str());
				}
			}
		}
	};
}