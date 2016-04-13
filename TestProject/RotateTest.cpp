#include "stdafx.h"
#include "CppUnitTest.h"
#include "MathUtils.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestProject
{
	TEST_CLASS(RotateTest)
	{
	public:
		TEST_METHOD(Rotate180Test)
		{
			// Actual Matrix:
			MatrixFloat inputMatrix;
			{
				MatrixFloat_Initialize(&inputMatrix, 2, 3);

				inputMatrix.Data[0] = 0;
				inputMatrix.Data[1] = 1;

				inputMatrix.Data[2] = 2;
				inputMatrix.Data[3] = 3;

				inputMatrix.Data[4] = 4;
				inputMatrix.Data[5] = 5;
			}

			MatrixFloat actualMatrix = Rotate180(&inputMatrix);

			MatrixFloat expectedMatrix;
			{
				MatrixFloat_Initialize(&expectedMatrix, 2, 3);

				expectedMatrix.Data[0] = 5;
				expectedMatrix.Data[1] = 4;

				expectedMatrix.Data[2] = 3;
				expectedMatrix.Data[3] = 2;

				expectedMatrix.Data[4] = 1;
				expectedMatrix.Data[5] = 0;
			}

			TestUtils::AreEqual(expectedMatrix, actualMatrix, 0.005f);
		}
	};
}