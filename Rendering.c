#include "Rendering.h"

void Draw(SDL_Renderer* renderer, bool Screen[32][64]) {
    for(int x = 0; x < SCREEN_WIDTH; x++) {
        for(int y= 0; y < SCREEN_HEIGHT; y++) {
            if(Screen[y][x])
                SDL_SetRenderDrawColor(renderer, 0x66, 0xFF, 0x66, 0xFF);
            SDL_Rect pixel = { .w = PIXEL_SIZE, .h = PIXEL_SIZE, .x = x * PIXEL_SIZE, .y = y * PIXEL_SIZE };
            SDL_RenderFillRect(renderer, &pixel);
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        }
    }
}
