#pragma once

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

#include <stdio.h>
#include <stdint.h>
#include "Registers.h"
#include "Memory.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "Helper.h"

typedef struct {
    bool pressedDown;
} KeyData_t;

typedef struct {
    int state;
    int data;
} State_t;

#define STATE_OK 0
#define WAIT_FOR_INPUT 1
#define EXIT 2

State_t ExecInstruction(uint16_t opcode, registers_t* registers, uint16_t* stack, uint8_t* memory, SDL_Renderer* renderer, bool screen[SCREEN_HEIGHT][SCREEN_WIDTH], KeyData_t keys[], bool* draw_flag);
