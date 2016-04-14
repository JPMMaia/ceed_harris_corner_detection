#include "Vector.h"

#include <stdlib.h>

void Vector_Initialize(Vector* vector, size_t size)
{
	vector->Data = (float*) malloc(size * sizeof(float));
	vector->Size = size;
}
void Vector_Shutdown(Vector* vector)
{
	if(vector->Data)
	{
		free(vector->Data);
		vector->Data = NULL;
	}

	vector->Size = 0;
}

float Vector_GetElement(const Vector* vector, size_t index)
{
	return vector->Data[index];
}
void Vector_SetElement(Vector* vector, size_t index, float element)
{
	vector->Data[index] = element;
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
