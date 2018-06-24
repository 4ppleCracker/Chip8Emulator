#include "Screen.h"

void CopySpriteToInterpreterMemory(uint8_t* Memory, sprite_t sprite, uint8_t index) {
    for(int i = 0; i < 8; i++) {
        uint8_t* startOfSprite = Memory + (index * (SPRITEROWSIZE * 8));
        uint8_t rowOffset = (SPRITEROWSIZE * i);
        memcpy(startOfSprite + rowOffset, &sprite.Data[i], SPRITEROWSIZE);
    }
}
