#pragma once
#define ZERO \
        {\
            0xF0, \
            0x90, \
            0x90, \
            0x90, \
            0xF0\
        }
#define ONE \
        {\
            0x20,\
            0x60,\
            0x20,\
            0x20,\
            0x70\
        }
#define TWO \
        {\
            0xF0, \
            0x10, \
            0xF0, \
            0x80, \
            0xF0\
        }
#define THREE \
        {\
            0xF0, \
            0x10, \
            0xF0, \
            0x10, \
            0xF0\
        }
#define FOUR \
        {\
            0x90, \
            0x90, \
            0xF0, \
            0x10, \
            0x10\
        }
#define FIVE \
        {\
            0xF0, \
            0x80, \
            0xF0, \
            0x10, \
            0xF0\
        }
#define SIX \
        {\
            0xF0, \
            0x80, \
            0xF0, \
            0x90, \
            0xF0\
        }
#define SEVEN \
        {\
            0xF0, \
            0x10, \
            0x20, \
            0x40, \
            0x40\
        }
#define EIGHT \
        {\
            0xF0, \
            0x90, \
            0xF0, \
            0x90, \
            0xF0\
        }
#define NINE \
        {\
            0xF0, \
            0x90, \
            0xF0, \
            0x10, \
            0xF0\
        }
#define HEX_A \
        {\
            0xF0, \
            0x90, \
            0xF0, \
            0x90, \
            0x90\
        }
#define HEX_B \
        {\
            0xE0, \
            0x90, \
            0xE0, \
            0x90, \
            0xE0\
        }
#define HEX_C \
        {\
            0xF0, \
            0x80, \
            0x80, \
            0x80, \
            0xF0\
        }
#define HEX_D \
        {\
            0xE0, \
            0x90, \
            0x90, \
            0x90, \
            0xE0\
        }
#define HEX_E \
        {\
            0xF0, \
            0x80, \
            0xF0, \
            0x80, \
            0xF0\
        }
#define HEX_F \
        {\
            0xF0, \
            0x80, \
            0xF0, \
            0x80, \
            0x80\
        }

const sprite_t hex[16] = {
        {0,ZERO},
        {1,ONE},
        {2,TWO},
        {3,THREE},
        {4,FOUR},
        {5,FIVE},
        {6,SIX},
        {7,SEVEN},
        {8,EIGHT},
        {9,NINE},
        {10,HEX_A},
        {11,HEX_B},
        {12,HEX_C},
        {13,HEX_D},
        {14,HEX_E},
        {15,HEX_F},
};        
        
