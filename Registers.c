#include "Registers.h"

void fPrintRegisters(registers_t registers, char* Buffer) {
    PrintRegister(V0, registers.V0);
    PrintRegister(V1, registers.V1);
    PrintRegister(V2, registers.V2);
    PrintRegister(V3, registers.V3);
    PrintNewLine();
    PrintRegister(V4, registers.V4);
    PrintRegister(V5, registers.V5);
    PrintRegister(V6, registers.V6);
    PrintRegister(V7, registers.V7);
    PrintNewLine();
    PrintRegister(V8, registers.V8);
    PrintRegister(V9, registers.V9);
    PrintRegister(VA, registers.VA);
    PrintRegister(VB, registers.VB);
    PrintNewLine();
    PrintRegister(VC, registers.VC);
    PrintRegister(VD, registers.VD);
    PrintRegister(VE, registers.VE);
    PrintRegister(VF, registers.VF);
    PrintNewLine();
    PrintRegister(I, registers.I);
    PrintRegister(DT, registers.DT);
    PrintRegister(ST, registers.ST);
    PrintRegister(PC, registers.PC);
    PrintNewLine();
}

void PrintRegisters() {
    char Buffer[64];
    printf("%s", Buffer);
}
