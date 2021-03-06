#pragma once

#include <stddef.h>

typedef struct _Vector
{
	float* Data;
	size_t Size;
	size_t ReservedSize;
} Vector;

#ifdef __cplusplus
extern "C"
{
#endif

	void Vector_Initialize(Vector* vector, size_t size);
	void Vector_Shutdown(Vector* vector);

	float Vector_GetElement(const Vector* vector, size_t index);
	void Vector_SetElement(Vector* vector, size_t index, float element);
	void Vector_AddElement(Vector* vector, float element);
	void Vector_Clear(Vector* vector);

	void Vector_OrderAscendent(Vector* vector);
	void Vector_OrderQuicksort(Vector* vector);

	void Vector_Print(Vector* vector);

#ifdef __cplusplus
}
#endif
