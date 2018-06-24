#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VReg(n) uint8_t V ## n

typedef struct {
    union {
        struct {
            VReg(0);
            VReg(1);
            VReg(2);
            VReg(3);
            VReg(4);
            VReg(5);
            VReg(6);
            VReg(7);
            VReg(8);
            VReg(9);
            VReg(A);
            VReg(B);
            VReg(C);
            VReg(D);
            VReg(E);
            VReg(F);
        };
        uint8_t V[0xF];
    };
    uint16_t I;
    uint8_t DT;
    uint8_t ST;
    uint16_t PC;
    uint8_t SP;
} registers_t;

#define PrintRegister(RegName, Data) sprintf(Buffer + strlen(Buffer), "%s => %X ", #RegName, Data);
#define PrintNewLine() sprintf(Buffer + strlen(Buffer), "\n");

void PrintRegisters();
void fPrintRegisters(registers_t registers, char* Buffer);
