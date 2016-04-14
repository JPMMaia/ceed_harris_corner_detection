#include "stdafx.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void TestUtils::AreEqual(const MatrixFloat& matrix1, const MatrixFloat& matrix2, float tolerance)
{
	Assert::IsFalse(matrix1.Width != matrix2.Width || matrix1.Height != matrix2.Height, L"Sizes don't match.");

	wchar_t message[64];
	for (size_t i = 0; i < matrix1.Height; ++i)
	{
		for (size_t j = 0; j < matrix1.Width; ++j)
		{
			_swprintf(message, L"[%u, %u]", i, j);

			Assert::AreEqual(MatrixFloat_Get(&matrix1, i, j), MatrixFloat_Get(&matrix2, i, j), tolerance, message);
		}
	}
}
