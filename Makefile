# File:   Makefile
# Author: H. D. Parkes
# Date:   2 Oct 2022
# Descr:  Makefile for game

BINARY=game.out
CODEDIRS=. ../drivers ../drivers/avr ../utils
INCDIRS=. ../drivers ../drivers/avr ../utils ../fonts

CC=avr-gcc
OPT=-00
#DEPFLAGS=-MP -MD
DEPFLAGS=-MMD
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g $(DEPFLAGS) $(foreach Dir,$(INCDIRS),-I$(Dir))

CFILES=$(foreach Dir,$(CODEDIRS),$(wildcard $(Dir)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

OBJCOPY = avr-objcopy
SIZE = avr-size


# Default target.
all: $(BINARY)

# Link: create ELF output file from object files.
$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Compile: create object files from C source files.
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Target: clean project.
.PHONY: clean
clean:
	rm $(OBJECTS) $(DEPFILES)


# Target: program project.
.PHONY: program
program: $(BINARY)
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
