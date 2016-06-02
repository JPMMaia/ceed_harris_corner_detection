#include "Vector.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void Vector_OrderQuicksortAuxiliary(Vector* vector, size_t low, size_t high);
static size_t Vector_QuicksortPartition(Vector* vector, size_t low, size_t high);

void Vector_Initialize(Vector* vector, size_t size)
{
	vector->Data = (float*)malloc(size * sizeof(float));
	vector->Size = 0;
	vector->ReservedSize = size;
}
void Vector_Shutdown(Vector* vector)
{
	if (vector->Data)
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
			if (vector->Data[i] > vector->Data[j])
			{
				float temp = vector->Data[i];
				vector->Data[i] = vector->Data[j];
				vector->Data[j] = temp;
			}
		}
	}
}

void Vector_OrderQuicksort(Vector* vector)
{
	Vector_OrderQuicksortAuxiliary(vector, 0, vector->Size - 1);
}

void Vector_OrderQuicksortAuxiliary(Vector* vector, size_t low, size_t high)
{
	if (low < high)
	{
		size_t p = Vector_QuicksortPartition(vector, low, high);

		Vector_OrderQuicksortAuxiliary(vector, low, p);
		Vector_OrderQuicksortAuxiliary(vector, p + 1, high);
	}
}

size_t Vector_QuicksortPartition(Vector* vector, size_t low, size_t high)
{
	float pivot = vector->Data[low];
	int i = (int)low - 1;
	int j = (int)high + 1;

	while(1)
	{
		do
		{
			++i;
		}
		while (vector->Data[i] < pivot);

		do
		{
			--j;
		} 
		while (vector->Data[j] > pivot);

		if (i >= j)
			return j;

		float temp = vector->Data[i];
		vector->Data[i] = vector->Data[j];
		vector->Data[j] = temp;
	}
}

void Vector_Print(Vector* vector)
{
	printf("Vector; Size: %llu; ReservedSize: %llu; Elements:", (long long unsigned int)vector->Size, (long long unsigned int)vector->ReservedSize);
	for (size_t i = 0; i < vector->Size; ++i)
		printf(" %f;", vector->Data[i]);
	printf("\n");
}
