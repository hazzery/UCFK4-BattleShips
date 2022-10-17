# File:   Makefile
# Author: Harrison Parkes and Dominic Dumble
# Date:   12 Sep 2010
# Description:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I.. -I../utils -I../fonts -I../drivers -I../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../drivers/avr/system.h ../drivers/navswitch.h ../drivers/display.h ../drivers/ledmat.h ../drivers/led.h ../utils/pacer.h Communications.h TurnEvents.h ShipPlacement.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../drivers/avr/system.c ../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../drivers/navswitch.c ../drivers/avr/system.h ../drivers/navswitch.h ../drivers/avr/delay.h ../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../drivers/ledmat.c ../drivers/avr/system.h ../drivers/avr/pio.h ../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../drivers/display.c ../drivers/avr/system.h ../drivers/ledmat.h ../drivers/display.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../drivers/led.c ../drivers/avr/system.h ../drivers/avr/pio.h ../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../utils/pacer.c ../drivers/avr/system.h ../drivers/avr/timer.h ../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../drivers/avr/timer.c ../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../utils/font.c ../utils/font.h ../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../drivers/button.c ../drivers/avr/system.h ../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

board.o: Board.c Board.h Position.h
	$(CC) -c $(CFLAGS) $< -o $@

ship_placement.o: ShipPlacement.c ../drivers/navswitch.h ../drivers/display.h ../drivers/led.h ShipPlacement.h Ship.h Board.h Position.h ../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

communications.o: Communications.c ../drivers/navswitch.h ../drivers/led.h Communications.h Board.h Position.h ../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

turn_events.o: TurnEvents.c ../drivers/navswitch.h ../drivers/led.h TurnEvents.h Ship.h Board.h Position.h
	$(CC) -c $(CFLAGS) $< -o $@

ship.o: Ship.c Ship.h
	$(CC) -c $(CFLAGS) $< -o $@

ghostGL.o: GhostGL.c GhostGL.h Board.h ../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../drivers/avr/ir_uart.c ../drivers/avr/ir_uart.h ../drivers/avr/usart1.h ../drivers/avr/timer0.h ../drivers/avr/pio.h ../drivers/avr/delay.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../drivers/avr/usart1.c ../drivers/avr/usart1.h ../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../drivers/avr/timer0.c ../drivers/avr/timer0.h ../drivers/avr/system.h ../drivers/avr/bits.h ../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../drivers/avr/prescale.c ../drivers/avr/prescale.h ../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
game.out: game.o system.o navswitch.o ledmat.o display.o led.o pacer.o timer.o font.o button.o board.o ship_placement.o communications.o turn_events.o ship.o ghostGL.o ir_uart.o usart1.o timer0.o prescale.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


