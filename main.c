#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stddef.h>

#include "Registers.h"
#include "Memory.h"
#include "Opcode.h"
#include "Screen.h"
#include "Helper.h"
#include "HexSprites.h"
#include "FileHelper.h"
#include "Rendering.h"
#include <SDL2/SDL_ttf.h>
#include "Constants.h"

#include "Chip8.h"

#define DEBUG 0
#define INTERACTIVE 0

bool Running = true;

void Exit(int num) {
    puts("Quitting");
    Running = false;
    SDL_Quit();
    TTF_Quit();
    exit(num);;
}

void InitSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        Exit(-1);
    }
    if(TTF_Init() < 0) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        Exit(-1);
    }
}
void InitSprites(uint8_t* Memory) {
    for(int i = 0; i < 16; i++) {
        CopySpriteToInterpreterMemory(Memory, hex[i], i);
    }
}
void InitKeys(KeyData_t Keys[0xF]) {
    memset(Keys, 0, sizeof(KeyData_t) * 0xF);
}

int PCBoundsCheck(uint16_t PC, uint16_t Min, uint16_t Max) {
     if(PC > Max || PC < Min) {
        printf("Error: PC is out of bounds %d\n", Chip8.Registers.PC);
        return -1;
    }
    return 0;
}

SDL_Thread* DrawThread = NULL;

bool draw_flag = false;

SDL_Window* window;
SDL_Renderer* renderer;

static int DrawScreen() {
#if DEBUG == 1
    SDL_Rect Message_rect;
    TTF_Font* TextFont = TTF_OpenFont("./Fonts/Bitter-Regular.ttf", 12);
    SDL_Color Color = {255, 0, 255};
#endif
    
    while(Running) {
        if(draw_flag == true) {
            Draw(renderer, Chip8.Screen);
            
#if DEBUG == 1
            char Text[128] = "";
            
            sprintf(Text + strlen(Text), "Registers:\n");
            fPrintRegisters(Chip8.Registers, Text);
            
            SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(TextFont,Text, Color, 400);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            
            SDL_GetClipRect(surfaceMessage, &Message_rect);
            
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            
            SDL_DestroyTexture(Message);
            SDL_FreeSurface(surfaceMessage);
#endif
            
            SDL_RenderPresent(renderer);
            draw_flag = false;
        }
    }
    return 0;
}

int main() {
    
    InitSprites(Chip8.Memory);
    InitKeys(Chip8.Keys);
    InitSDL();
    srand(time(NULL));
    
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, SDL_WINDOW_SHOWN, &window, &renderer);
    
    State_t state = { .state = STATE_OK };
    
    ssize_t romSize;
    if(ReadRom(Chip8.Memory+0x200, &romSize) != romSize) {
        Exit(-1);
    }
    
    Chip8.Registers.PC = 0x200;
    
    DrawThread = SDL_CreateThread(DrawScreen, "DrawThread", NULL);
    
    int ticks = SDL_GetTicks();
    int delta = 0;
    
    SDL_Event event;
    while (Running) {
        int currentticks = SDL_GetTicks();
        delta = currentticks - ticks;
        ticks = currentticks;
        
       if(PCBoundsCheck(Chip8.Registers.PC, 0x200, romSize + 0x200) < 0)
           Exit(-1);
       
       while(SDL_PollEvent(&event)) {
            uint8_t key = GetKey(&event);
            if(key < 0x10) {
                    Chip8.Keys[key].pressedDown = (event.key.type == SDL_KEYDOWN ? true : false);
            }
            switch(event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    Exit(0);
                    break;
            }
        }
        
        uint16_t opcode;
        
        if(state.state == STATE_OK) {
#if INTERACTIVE == 1
            /*printf("\nType your opcode in hexadecimal\n");
            fputs("> ", stdout);
            if(scanf("%x", &opcode) < 0)
                Running = false;*/
#else
            opcode = Chip8.Memory[Chip8.Registers.PC] << 8 | Chip8.Memory[Chip8.Registers.PC + 1];
#endif
            
            DecreaseToZero(Chip8.Registers.DT);
            DecreaseToZero(Chip8.Registers.ST);
            
            if(Chip8.Registers.ST > 0) {
               Beep();
            }
#if DEBUG == 1
            printf("Executing opcode %X at offset %X\n", opcode, Chip8.Registers.PC);
#endif
            state = ExecInstruction(opcode, &Chip8.Registers, Chip8.Stack, Chip8.Memory, renderer, Chip8.Screen, Chip8.Keys, &draw_flag);
            
            Chip8.Registers.PC += 2;
        } else if (state.state == WAIT_FOR_INPUT) {
            puts("Waiting for input...");
            for(int key = 0; key < 0x10; key++) {
                if(Chip8.Keys[key].pressedDown) {
                    Chip8.Registers.V[state.data] = key;
                    state.state = STATE_OK;
                }
            }
        } else if (state.state == EXIT) {
            Exit(0);
        }
        if(delta < DESIRED_TICKS)
         SDL_Delay(DESIRED_TICKS - delta);
    }
    
    SDL_Quit();
}





