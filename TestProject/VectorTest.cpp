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

			Assert::IsTrue(5 == vector.ReservedSize);
			Assert::IsTrue(0 == vector.Size);

			Vector_AddElement(&vector, 2.0f);
			Assert::AreEqual(2.0f, Vector_GetElement(&vector, 0));
			Assert::IsTrue(1 == vector.Size);

			Vector_Clear(&vector);
			Assert::IsTrue(0 == vector.Size);
			Assert::IsTrue(5 == vector.ReservedSize);

			Vector_Shutdown(&vector);
			Assert::IsTrue(0 == vector.Size);
			Assert::IsTrue(0 == vector.ReservedSize);
		}

		TEST_METHOD(VectorOrderingTest)
		{
			Vector vector;
			Vector_Initialize(&vector, 5);

			Vector_AddElement(&vector, 2.0f);
			Vector_AddElement(&vector, 1.0f);
			Vector_AddElement(&vector, 5.0f);
			Vector_AddElement(&vector, -3.0f);
			Vector_AddElement(&vector, 2.0f);

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