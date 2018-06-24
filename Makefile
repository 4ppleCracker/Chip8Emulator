TARGET = Chip8Emulator
LIBS = -lm -lSDL2 -lSDL2_ttf
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all
default: $(TARGET) run
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) -Wall $(LIBS) -o $@
	
run:
	@./$(TARGET)
	
clean:
	@rm -f *.o
	@rm -f $(TARGET)
