#pragma once

#include <stdint.h>
#include <string.h>

typedef struct {
    uint8_t Index;
    uint8_t Data[8];
} sprite_t;

#define SPRITEROWSIZE (sizeof(uint8_t))

void CopySpriteToInterpreterMemory(uint8_t* Memory, sprite_t sprite, uint8_t index);
