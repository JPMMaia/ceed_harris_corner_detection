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

		static void TestOrderStatisticsFiltering(const std::wstring& inputFilename, const std::wstring& outputFilename, size_t order, size_t onesSize)
		{
			// Load expected matrix:
			MatrixFloat expectedMatrix;
			MatrixFloat_Load(&expectedMatrix, outputFilename.c_str());

			// Compute actual matrix:
			MatrixFloat actualMatrix;
			{
				MatrixFloat inputMatrix;
				MatrixFloat_Load(&inputMatrix, inputFilename.c_str());
				{
					MatrixFloat onesMatrix;
					MatrixFloat_Initialize(&onesMatrix, onesSize, onesSize);
					for (size_t i = 0; i < onesSize; ++i)
					{
						for (size_t j = 0; j < onesSize; ++j)
						{
							MatrixFloat_Set(&onesMatrix, i, j, 1.0f);
						}
					}					

#ifdef _OPTIMIZATION_ORDER_STATISTIC_FILTERING_SPECIALIZED
					actualMatrix = OrderStatisticFilteringSpecialized(&inputMatrix, &onesMatrix);
#else
					actualMatrix = OrderStatisticFiltering(&inputMatrix, order, &onesMatrix);
#endif

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

#ifndef _OPTIMIZATION_ORDER_STATISTIC_FILTERING_SPECIALIZED
		TEST_METHOD(OrderStatisticFilteringMatrixATest)
		{
			TestOrderStatisticsFiltering(L"Resources/OrderStatisticFilteringMatrixAInput.txt", L"Resources/OrderStatisticFilteringMatrixAOutput.txt", 3, 2);
		}
#endif

		TEST_METHOD(OrderStatisticFilteringMatrixBTest)
		{
			TestOrderStatisticsFiltering(L"Resources/OrderStatisticFilteringMatrixBInput.txt", L"Resources/OrderStatisticFilteringMatrixBOutput.txt", 49, 7);
		}

		TEST_METHOD(OrderStatisticFilteringMatrixCTest)
		{
			TestOrderStatisticsFiltering(L"Resources/OrderStatisticFilteringMatrixCInput.txt", L"Resources/OrderStatisticFilteringMatrixCOutput.txt", 49, 7);
		}
	};
}