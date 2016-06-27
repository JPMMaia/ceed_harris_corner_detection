#include "stdafx.h"
#include "MatrixTestUtils.h"

#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void TestUtils::AreEqual(const MatrixFloat& matrix1, const MatrixFloat& matrix2, float tolerance)
{
	Assert::IsFalse(matrix1.Width != matrix2.Width || matrix1.Height != matrix2.Height, L"Sizes don't match.");

	auto pMatrix1 = &matrix1;
	auto pMatrix2 = &matrix2;

	std::array<wchar_t, 64> message;
	for (size_t i = 0; i < matrix1.Height; ++i)
	{
		for (size_t j = 0; j < matrix1.Width; ++j)
		{
			//_swprintf_s_l(message.data(), message.size(), L"[%llu, %llu]", i, j);
			Assert::AreEqual(MatrixFloat_Get(pMatrix1, i, j), MatrixFloat_Get(pMatrix2, i, j), tolerance, message.data());
		}
	}
}
