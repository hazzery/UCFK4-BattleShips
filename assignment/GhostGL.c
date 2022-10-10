//
// Created by Harry on 9/10/22.
//

#include "GhostGL.h"
#include "../drivers/display.h"

extern bool ghost_board[BOARD_HEIGHT][BOARD_WIDTH];
extern Cell_State_t board[BOARD_HEIGHT][BOARD_WIDTH];

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
    for (uint8_t row = 0; row < BOARD_HEIGHT; row ++) {
        for (uint8_t col = 0; col < BOARD_WIDTH; col ++) {
            display_pixel_set(col, row, board[row][col] || ghost_board[row][col]);
        }
    }
    display_update();
}

/**
 * @brief Sets all of the pixels off
 */
void ghostGL_clear(void)
{
    ghost_wipe();
    display_clear();
}