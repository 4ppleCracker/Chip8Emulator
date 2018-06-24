#pragma once

#include "stdint.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// buffer must have length >= sizeof(int) + 1
// Write to the buffer backwards so that the binary representation
// is in the correct order i.e.  the LSB is on the far right
// instead of the far left of the printed string
char *int2bin(uint8_t a, char *buffer, int buf_size);

uint8_t GetKey(SDL_Event* event);

void Beep();

#define DecreaseToZero(value) if(value > 0) value--;
