#include "stdafx.h"
#include "CppUnitTest.h"
#include "MathUtils.h"
#include "MatrixTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(OrderStatisticFilteringTest)
	{
	public:

		TEST_METHOD(OrderStatisticFilteringMatrixATest)
		{
			// Load expected matrix:
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, L"Resources/OrderStatisticFilteringMatrixAOutput.txt");

			// Compute actual matrix:
			MatrixFloat actualMatrix;
			{
				MatrixFloat inputMatrix;
				MatrixFloat_Load(&inputMatrix, L"Resources/OrderStatisticFilteringMatrixAInput.txt");
				{
					const size_t radius = 3;
					const size_t size = 2 * radius + 1;
					MatrixFloat onesMatrix;
					MatrixFloat_Initialize(&onesMatrix, size, size);
					for (size_t i = 0; i < size; ++i)
					{
						for (size_t j = 0; j < size; ++j)
						{
							MatrixFloat_Set(&onesMatrix, i, j, 1.0f);
						}
					}

					OrderStatisticFiltering(&inputMatrix, size*size, &onesMatrix);

					MatrixFloat_Shutdown(&onesMatrix);
				}

				MatrixFloat_Shutdown(&inputMatrix);
			}

			// Compare images:
			TestUtils::AreEqual(expectedMatrix, actualMatrix, 0.001f);

			// Free resources:
			MatrixFloat_Shutdown(&actualMatrix);
			MatrixFloat_Shutdown(&expectedMatrix);
		}
	};
}