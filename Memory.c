#include "Memory.h"

void Push(uint16_t* stack, registers_t* registers, uint16_t data) {
    stack[registers->SP++] = data;
   //registers->SP++;
}
uint16_t Pop(uint16_t* stack, registers_t* registers) {
    return stack[--registers->SP];
}
