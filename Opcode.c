#include "Opcode.h"

State_t ExecInstruction (uint16_t opcode, registers_t* registers, uint16_t* stack, uint8_t* memory, SDL_Renderer* renderer, bool screen[SCREEN_HEIGHT][SCREEN_WIDTH], KeyData_t keys[], bool* draw_flag)
{
    const State_t state_t_ok = { .state = STATE_OK };
    if(opcode == 0x0000) {
        PrintRegisters(*registers);
        return state_t_ok;
    }
    if(opcode == 0x0001) {
        State_t exit;
        exit.state = EXIT;
        exit.data = 0;
        return exit;
    }
    if(opcode == 0x00E0) {
        for(int y = 0; y < SCREEN_HEIGHT; y++) {
            memset(screen[y], 0, SCREEN_WIDTH * sizeof(uint8_t));
        }
        *draw_flag = true;
        return state_t_ok;
    }
    if(opcode == 0x00EE) {
        int addr = Pop(stack, registers);
        registers->PC = addr;
        return state_t_ok;
    }
    int maskedopcode = (opcode & 0xF000);
    switch(maskedopcode >> 12) {
        case 0x1: {
            int addr = opcode & 0x0FFF;
            registers->PC = addr - 2;
            break;
        }
        case 0x2: {
            int addr = opcode & 0x0FFF;
            Push(stack, registers, registers->PC);
            registers->PC = addr - 2;
            break;  
        }
        case 0x3: {
            int V = (opcode & 0x0F00) >> 4*2;
            int Byte = opcode & 0x00FF;
            if(registers->V[V] == Byte) {
                registers->PC += 2;
            }
            break;  
        }
        case 0x4: {
            int V = (opcode & 0x0F00) >> 4*2;
            int Byte = opcode & 0x00FF;
            if(registers->V[V] != Byte) {
                registers->PC += 2;
            }
        }
        case 0x5: {
            int V = (opcode & 0x0F00) >> 4*2;
            int V2= opcode & 0x00F0 >> 4;
            if(registers->V[V] == registers->V[V2]) {
                registers->PC += 2;
            }
            break;  
        }
        case 0x6: {
            int V = (opcode & 0x0F00) >> 4*2;
            int Byte = opcode & 0x00FF;
            registers->V[V] = Byte;
            break;  
        }
        case 0x7: {
            int V = (opcode & 0x0F00) >> 4*2;
            int Byte = opcode & 0x00FF;
            registers->V[V] += Byte;
            break;  
        }
        case 0x8: {
            int V = (opcode & 0x0F00) >> 4*2;
            int V2 = (opcode & 0x00F0) >> 4*1;
            switch(opcode & 0x000F) {
                case 0x0: {
                    registers->V[V] = registers->V[V2];
                    break;
                }
                case 0x1: {
                    registers->V[V] = registers->V[V] | registers->V[V2];
                    break;
                }
                case 0x2: {
                    registers->V[V] = registers->V[V] & registers->V[V2];
                    break;
                }
                case 0x3: {
                    registers->V[V] = registers->V[V] ^ registers->V[V2];
                    break;
                }
                case 0x4: {
                    if(registers->V[V] + registers->V[V2] > UINT8_MAX)
                        registers->VF = 1;
                    registers->V[V] += registers->V[V2];
                    break;
                }
                case 0x5: {
                    if(registers->V[V2] > registers->V[V])
                        registers->VF = 0;
                    else
                        registers->VF = 1;
                    registers->V[V] -= registers->V[V2];
                    break;
                }
                case 0x6: {
                    if((registers->V[V] & 0x1) == 1)
                        registers->VF = 1;
                    else
                        registers->VF = 0;
                    registers->V[V] >>= 1;
                    break;
                }
                case 0x7: {
                    if(registers->V[V] > registers->V[V2])
                        registers->VF = 0;
                    else
                        registers->VF = 1;
                    registers->V[V] = registers->V[V2] - registers->V[V];
                    break;
                }
                case 0xE: {
                    if((registers->V[V] & 0x80) == 0x80)
                        registers->VF = 1;
                    else
                        registers->VF = 0;
                    registers->V[V] <<= 2;
                    break;
                }
                default: {
                    printf("No such opcode\n");
                    break;
                }
            }
            break;
        }
        case 0x9: {
            int V = (opcode & 0x0F00) >> 4*2;
            int V2 = opcode & 0x00F0;
            if(registers->V[V] != registers->V[V2]) {
                registers->PC += 2;
            }
            break;
        }
        case 0xA: {
            registers->I = opcode & 0x0FFF;
            break;
        }
        case 0xB: {
            uint16_t Data = opcode & 0x0FFF;
            registers->PC = Data + registers->V0;
            break;
        }
        case 0xC: {
            int V = (opcode & 0x0F00) >> 4*2;
            int Byte = opcode & 0x00FF;
            uint8_t rbyte = rand() % 256;
            registers->V[V] = rbyte & Byte;
            break;
        }
        case 0xD: {
            int V = (opcode & 0x0F00) >> 4*2;
            int V2 = (opcode & 0x0F0) >> 4*1;
            int Nib = opcode & 0x000F;
            registers->VF = 0;
            for(int i = 0; i < Nib; i++) {
                uint8_t byte = memory[registers->I + i];
                for(int x = 0; x < 8; x++) {
                    bool pixel = (byte >> x) & 1;
                    bool* scrpixel = &screen[registers->V[V2] + i][registers->V[V] + ( 7 - x)];
                    if(*scrpixel == 1 && pixel == 1)
                        registers->VF = 1;
                    *scrpixel ^= pixel;
                }
            }
            *draw_flag = true;
            break;
        }
        case 0xE: {
            int V = (opcode & 0x0F00) >> 4*2;
            
            switch(opcode & 0x00FF) {
                case 0x9E: {
                    if(keys[registers->V[V]].pressedDown)
                        registers->PC += 2;
                    break;
                }
                case 0xA1: {
                    if(!keys[registers->V[V]].pressedDown)
                        registers->PC += 2;
                    break;
                }
                default: {
                    printf("No such opcode\n");
                    break;
                }
            }
            break;
        }
        case 0xF: {
            int V = (opcode & 0x0F00) >> 4*2;
            switch(opcode & 0x00FF) {
                case 0x07: {
                    registers->V[V] = registers->DT;
                    break;
                }
                case 0x0A: {
                    State_t wait;
                    wait.state = WAIT_FOR_INPUT;
                    wait.data = V;
                    return wait;
                    break;
                }
                case 0x15: {
                    registers->DT = registers->V[V];
                    break;
                }
                case 0x18: {
                    registers->ST = registers->V[V];
                    break;
                }
                case 0x1E: {
                    registers->I += registers->V[V];
                    break;
                }
                case 0x29: {
                    registers->I = 8 * registers->V[V];
                    break;
                }
                case 0x33: {
                    uint8_t hundreds = (registers->V[V] / 100) % 10;
                    uint8_t tens = (registers->V[V] / 10) % 10;
                    uint8_t ones = (registers->V[V] / 1) % 10;
                    memory[registers->I] = hundreds;
                    memory[registers->I + 1] = tens;
                    memory[registers->I + 2] = ones;
                    break;
                }
                case 0x55: {
                    for(int i = 0; i <= V; i++) {
                        memory[registers->I + i] = registers->V[i];
                    }
                    registers->I = V + 1;
                    break;
                }
                case 0x65: {
                    for(int i = 0; i <= V; i++) {
                         registers->V[i] = memory[registers->I + i];
                    }
                    registers->I = V + 1;
                    break;
                }
                default: {
                    printf("No such opcode\n");
                    break;
                }
            }
            break;
        }
        default: {
            printf("No such opcode\n");
            break;
        }
    }
    return state_t_ok;
}
