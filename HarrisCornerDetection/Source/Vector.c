#include "Vector.h"

#include <assert.h>
#include <stdlib.h>

void Vector_Initialize(Vector* vector, size_t size)
{
	vector->Data = (float*) malloc(size * sizeof(float));
	vector->Size = 0;
	vector->ReservedSize = size;
}
void Vector_Shutdown(Vector* vector)
{
	if(vector->Data)
	{
		free(vector->Data);
		vector->Data = NULL;
	}

	vector->Size = 0;
	vector->ReservedSize = 0;
}

float Vector_GetElement(const Vector* vector, size_t index)
{
#ifdef _DEBUG
	assert(index < vector->Size);
#endif

	return vector->Data[index];
}
void Vector_SetElement(Vector* vector, size_t index, float element)
{
#ifdef _DEBUG
	assert(index < vector->Size);
#endif

	vector->Data[index] = element;
}

void Vector_AddElement(Vector* vector, float element)
{
#ifdef _DEBUG
	assert(vector->Size < vector->ReservedSize);
#endif

	vector->Data[vector->Size++] = element;
}
void Vector_Clear(Vector* vector)
{
	vector->Size = 0;
}

void Vector_OrderAscendent(Vector* vector)
{
	for (size_t i = 0; i < vector->Size - 1; ++i)
	{
		for (size_t j = i; j < vector->Size; ++j)
		{
			if(vector->Data[i] > vector->Data[j])
			{
				float temp = vector->Data[i];
				vector->Data[i] = vector->Data[j];
				vector->Data[j] = temp;
			}
		}
	}
}
