# File:   Makefile
# Author: H. D. Parkes
# Date:   2 Oct 2022
# Descr:  Makefile for game

BINARY=main.out
CODEDIRS=. ../drivers ../drivers/avr ../utils
INCDIRS=. ../drivers ../drivers/avr ../utils ../fonts

CC=avr-gcc
OPT=-00
DEPFLAGS=-MMD
MMCU=atmega32u2
CFLAGS = -mmcu=$(MMCU) -Os -Wall -Wstrict-prototypes -Wextra -g $(DEPFLAGS) $(foreach Dir,$(INCDIRS),-I$(Dir))

CFILES=$(foreach Dir,$(CODEDIRS),$(wildcard $(Dir)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

HEX = $(patsubst %.out,%.hex,$(BINARY))

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
	rm $(OBJECTS) $(DEPFILES) $(BINARY) $(HEX)


# Target: Flash hex onto board.
.PHONY: program
program: $(BINARY)
	$(OBJCOPY) -O ihex $(BINARY) $(HEX)
	dfu-programmer $(MMCU) erase; dfu-programmer $(MMCU) flash $(HEX); dfu-programmer $(MMCU) start
