#include "stdafx.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool operator==(const MatrixFloat& matrix1, const MatrixFloat& matrix2)
{
	if (matrix1.Width != matrix2.Width || matrix1.Height != matrix2.Height)
		return false;

	for (size_t i = 0; i < matrix1.Height; ++i)
	{
		for (size_t j = 0; j < matrix1.Width; ++j)
		{
			if (MatrixFloat_Get(&matrix1, i, j) != MatrixFloat_Get(&matrix2, i, j))
				return false;
		}
	}

	return true;
}
