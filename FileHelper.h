#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

FILE* GetFile(const char* filename);
ssize_t GetFileSize(FILE* file);
ssize_t ReadFile(FILE* file, uint16_t* buffer, ssize_t size);
int ReadRom(uint8_t* RomTarget, ssize_t* romSize);
