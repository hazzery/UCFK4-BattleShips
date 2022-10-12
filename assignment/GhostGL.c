//
// Created by Harry on 9/10/22.
//

#include <string.h>
#include "GhostGL.h"
#include "../drivers/avr/timer.h"
#include "../drivers/display.h"

/**
 * @brief Initializes the display, ready for use
 * Must be called exactly once, at the beginning of the program.
 */
void ghostGL_init(void)
{
    display_init();
}

/**
 * @brief Updates the states of the LEDs on the matrix display
 * Non zero values on the board or the ghost board will enable their respective LED.
 */
void ghostGL_update(void)
{
    static bool flash_on = true;

    if (timer_get() % 3900 == 0) {
        flash_on = !flash_on;
    }

    for (uint8_t row = 0; row < BOARD_HEIGHT; row ++) {
        for (uint8_t col = 0; col < BOARD_WIDTH; col ++) {
            if (flash_on) {
                display_pixel_set(col, row, state_board.grid[row][col] || ghost_board.grid[row][col]);
            } else {
                display_pixel_set(col, row, state_board.grid[row][col]);
            }
        }
    }
    display_update();
}

/**
 * @brief Sets all of the pixels off
 */
void ghostGL_clear(void)
{
    board_wipe(&ghost_board);
    board_wipe(&state_board);
    display_clear();
}