#pragma once

#include <stddef.h>

typedef struct _Vector
{
	float* Data;
	size_t Size;
} Vector;

#ifdef __cplusplus
extern "C"
{
#endif

	void Vector_Initialize(Vector* vector, size_t size);
	void Vector_Shutdown(Vector* vector);

	float Vector_GetElement(const Vector* vector, size_t index);
	void Vector_SetElement(Vector* vector, size_t index, float element);

	void Vector_OrderAscendent(Vector* vector);

#ifdef __cplusplus
}
#endif