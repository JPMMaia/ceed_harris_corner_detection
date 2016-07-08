#pragma once

#include "MatrixFloat.h"

#ifdef __cplusplus
extern "C"
{
#endif
		MatrixFloat Harris(const MatrixFloat* image, size_t radius);

#ifdef __cplusplus
}
#endif
