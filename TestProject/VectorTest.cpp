#include "stdafx.h"

#include "CppUnitTest.h"
#include "Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestProject
{
	TEST_CLASS(VectorTest)
	{
	public:
		TEST_METHOD(VectorBasicsTest)
		{
			Vector vector;
			Vector_Initialize(&vector, 5);

			Assert::IsTrue(5 == vector.Size);

			Vector_SetElement(&vector, 0, 2.0f);
			Assert::AreEqual(2.0f, Vector_GetElement(&vector, 0));

			Vector_Shutdown(&vector);
			Assert::IsTrue(0 == vector.Size);
		}

		TEST_METHOD(VectorOrderingTest)
		{
			Vector vector;
			Vector_Initialize(&vector, 5);

			Vector_SetElement(&vector, 0, 2.0f);
			Vector_SetElement(&vector, 1, 1.0f);
			Vector_SetElement(&vector, 2, 5.0f);
			Vector_SetElement(&vector, 3, -3.0f);
			Vector_SetElement(&vector, 4, 2.0f);

			Vector_OrderAscendent(&vector);

			Assert::AreEqual(-3.0f, Vector_GetElement(&vector, 0));
			Assert::AreEqual(1.0f, Vector_GetElement(&vector, 1));
			Assert::AreEqual(2.0f, Vector_GetElement(&vector, 2));
			Assert::AreEqual(2.0f, Vector_GetElement(&vector, 3));
			Assert::AreEqual(5.0f, Vector_GetElement(&vector, 4));

			Vector_Shutdown(&vector);
		}
	};
}