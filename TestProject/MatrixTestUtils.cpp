#include "stdafx.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void TestUtils::AreEqual(const MatrixFloat& matrix1, const MatrixFloat& matrix2, float tolerance)
{
	Assert::IsFalse(matrix1.Width != matrix2.Width || matrix1.Height != matrix2.Height);

	for (size_t i = 0; i < matrix1.Height; ++i)
	{
		for (size_t j = 0; j < matrix1.Width; ++j)
		{
			Assert::AreEqual(MatrixFloat_Get(&matrix1, i, j), MatrixFloat_Get(&matrix2, i, j), tolerance);
		}
	}
}
