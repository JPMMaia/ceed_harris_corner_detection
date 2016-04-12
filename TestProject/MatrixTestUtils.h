#pragma once

#include "MatrixFloat.h"

namespace TestUtils
{
	void AreEqual(const MatrixFloat& matrix1, const MatrixFloat& matrix2, float tolerance);
}