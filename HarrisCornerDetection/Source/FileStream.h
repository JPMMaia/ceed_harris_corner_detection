#pragma once

#include <stdio.h>
#include <stdint.h>

struct FileStream
{
	FILE* Stream;
};

#ifdef __cplusplus
extern "C"
{
#endif

	void FileStream_Open(struct FileStream* fileStream, const wchar_t* filenameW, const char* mode);
	void FileStream_Close(const struct FileStream* fileStream);
	void FileStream_SkipUntil(const struct FileStream* fileStream, uint8_t byte);
	void FileStream_ReadUInt8(const struct FileStream* fileStream, uint8_t* element);
	void FileStream_ReadInt32(const struct FileStream* fileStream, int32_t* element);
	void FileStream_ReadUInt32(const struct FileStream* fileStream, uint32_t* element);

#ifdef __cplusplus
}
#endif