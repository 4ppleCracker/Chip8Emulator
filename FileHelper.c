#include "FileHelper.h"

FILE* GetFile(const char* filename) {
    return fopen(filename, "rb");
}

ssize_t GetFileSize(FILE* file) {
    fseek(file, 0L, SEEK_END);
    ssize_t size = ftell(file);
    rewind(file);
    return size;
}

ssize_t ReadFile(FILE* file, uint16_t* buffer, ssize_t size) {
    return fread(buffer, sizeof(char), size, file);
}

int ReadRom(char* RomName, uint8_t* RomTarget, ssize_t* romSize) {
    FILE* rom = GetFile(RomName);
    
    *romSize = GetFileSize(rom);
    
    uint16_t* RomBuff = malloc(*romSize * sizeof(uint16_t));
    ssize_t readSize = ReadFile(rom, RomBuff, *romSize);
    if(readSize != *romSize) {
        puts("Couldn't read all rom data, exiting");
        return -1;
    }
    
    printf("Read %lu bytes\n", readSize);
    
    memcpy(RomTarget, RomBuff, readSize);
    
    free(RomBuff);
    return readSize;
}
