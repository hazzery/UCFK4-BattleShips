# File:   Makefile
# Author: H Parkes
# Description: Makefile for AVR project

PROJECT_NAME		:= BattleShips
SRC_EXTENSION		:= c
SRC_DIRECTORIES		:= . ./src ../drivers ../drivers/avr ../utils
INCLUDE_DIRECTORIES := ./include ../drivers ../drivers/avr ../utils ../fonts

CC 					:= avr-gcc
OPTIMIZATION_FLAGs	:= -00
DEPENDENCY_FLAGS 	:= -MMD
MMCU 				:= atmega32u2
CFLAGS 				:= -mmcu=$(MMCU) -Os -Wall -Wstrict-prototypes -Wextra -g $(DEPFLAGS) $(foreach Directory,$(INCLUDE_DIRECTORIES),-I$(Directory))

#---------------------------------------------------------------------------------
#MAKE RULES - SHOULDN'T NEED TO CHANGE ANYTHING BELOW HERE
#---------------------------------------------------------------------------------

BINARY 				:= $(PROJECT_NAME).out
HEX			 		:= $(patsubst %.out,%.hex,$(BINARY))

SRC_FILES 			:= $(foreach Directory,$(SRC_DIRECTORIES),$(wildcard $(Directory)/*.$(SRC_EXTENSION)))
OBJECT_FILES		:= $(addprefix build/,$(notdir $(SRC_FILES:.$(SRC_EXTENSION)=.o)))
DEPENDENCY_FILES	:= $(patsubst %.$(SRC_EXTENSION),%.d,$(SRC_FILES))


# Default target - Build binary file
all: $(BINARY)

# Clean project - Delete all build output
.PHONY: clean
clean:
	rm $(OBJECT_FILES) $(DEPENDENCY_FILES) $(BINARY) $(HEX)

# Flash hex file onto microcontroller
# Erases any existing program on microcontroller, uploads, and starts program running
.PHONY: upload
program: $(BINARY)
	avr-objcopy -O ihex $(BINARY) $(HEX)
	dfu-programmer $(MMCU) erase; dfu-programmer $(MMCU) flash $(HEX); dfu-programmer $(MMCU) start

-include $(DEPENDENCY_FILES)

# Link object files into single binary file
$(BINARY): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $^ -o $@ -lm
	avr-size $@

# Compile source files into object files
$(OBJECT_FILES): build/%.o: $(findstring $(wildcard */%.c),$(SRC_FILES))
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@
