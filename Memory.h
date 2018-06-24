#pragma once

#include <stdint.h>
#include "Registers.h"

void Push(uint16_t* stack, registers_t* registers, uint16_t data);
uint16_t Pop(uint16_t* stack, registers_t* registers);
