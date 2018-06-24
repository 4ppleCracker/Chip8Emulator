#pragma once

#include <stdlib.h>

#include "Registers.h"
#include "Memory.h"
#include "Constants.h"

struct Chip8_t {

    registers_t Registers;

    uint8_t Memory[RAM_SIZE];

    uint16_t Stack[16];

    bool Screen[SCREEN_HEIGHT][SCREEN_WIDTH];

    KeyData_t Keys[0xF];
    
} Chip8;
