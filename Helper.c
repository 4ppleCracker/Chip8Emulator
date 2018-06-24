#include "Helper.h"

char *int2bin(uint8_t a, char *buffer, int buf_size) {
    buffer += (buf_size - 1);

    for (int i = 7; i >= 0; i--) {
        *buffer-- = (a & 1) + '0';

        a >>= 1;
    }

    return buffer;
}

uint8_t GetKey(SDL_Event* event) {
    switch(event->key.keysym.scancode) {
                case SDL_SCANCODE_X:
                    return 0;
                case SDL_SCANCODE_1:
                    return 1;
                case SDL_SCANCODE_2:
                    return 2;
                case SDL_SCANCODE_3:
                    return 3;
                case SDL_SCANCODE_Q:
                    return 4;
                case SDL_SCANCODE_W:
                    return 5;
                case SDL_SCANCODE_E:
                    return 6;
                case SDL_SCANCODE_A:
                    return 7;
                case SDL_SCANCODE_S:
                    return 8;
                case SDL_SCANCODE_D:
                    return 9;
                case SDL_SCANCODE_Z:
                    return 0xA;
                case SDL_SCANCODE_C:
                    return 0xB;
                case SDL_SCANCODE_4:
                    return 0xC;
                case SDL_SCANCODE_R:
                    return 0xD;
                case SDL_SCANCODE_F:
                    return 0xE;
                case SDL_SCANCODE_V:
                    return 0xF;
                    break;
                default:
                    return 0x10;
            }
}

void Beep() {
    printf("Beep!\n");
}
