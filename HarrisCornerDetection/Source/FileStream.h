#pragma once

#include <stdio.h>
#include <stdint.h>

typedef struct _FileStream
{
	FILE* Stream;
} FileStream;

#ifdef __cplusplus
extern "C"
{
#endif

	void FileStream_Open(FileStream* fileStream, const wchar_t* filenameW, const char* mode);
	void FileStream_Close(const FileStream* fileStream);
	void FileStream_SkipUntil(const FileStream* fileStream, uint8_t byte);
	void FileStream_ReadUInt8(const FileStream* fileStream, uint8_t* element);
	void FileStream_ReadInt32(const FileStream* fileStream, int32_t* element);
	void FileStream_ReadUInt32(const FileStream* fileStream, uint32_t* element);
	void FileStream_ReadFloat(const FileStream* fileStream, float* element);

#ifdef __cplusplus
}
#endif