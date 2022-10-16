/** @file    GhostGL.c
 *  @authors Harrison Parkes, Dominic Dumble
 *  @date    9th of October 2022
 *  @brief   Matrix display graphics
 *  @note    Reads from the ghost and state boards to update the matrix display
*/
#include "../drivers/display.h"
#include "final/game.h"
#include "GhostGL.h"
#include "Board.h"

#define GHOST_FLASH_TICKS (DISPLAY_FREQUENCY / 2)

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
    static uint8_t flash_ticks = 0;
    flash_ticks++;

    // Turns the ghosted pixels on and off at a rate of 2Hz
    if (flash_ticks >= GHOST_FLASH_TICKS) {
        flash_on = !flash_on;
        flash_ticks = 0;
    }

    //Individually set each pixel on the matrix display
    for (uint8_t row = 0; row < BOARD_HEIGHT; row ++) {
        for (uint8_t col = 0; col < BOARD_WIDTH; col ++) {
            if (flash_on) {
                display_pixel_set(col, row, state_board.grid[row][col] || ghost_board.grid[row][col]);
            } else {
                display_pixel_set(col, row, state_board.grid[row][col] || oppositions_board.grid[row][col]);
            }
        }
    }
    display_update();
}

/**
 * @brief compresses board for communication before wiping data
 * 
 * @param compressed_board where compressed board data is stored
*/
void preclear_compress(uint8_t compressed_board[])
{
    compress_board(state_board, compressed_board);
}

/**
 * @brief Sets all of the pixels off
 */
void ghostGL_clear(void)
{
    // We call this function to turn the display off straight after
    // the fourth ship is placed, but at the current moment
    // the board_wipe function clears all the memory, and then
    // we go to send over the board data. Which just got wiped.

    // I can think of two ways to fix this
    // Instead of wiping the board to clear the screen, we could
    // turn off the display, while the transmission is happening
    // and turn it back on.
    // OR, a probably better solution, we compress the board as
    // soon as the 4th ship is placed, and just keep that
    // still wiping the normal board as we don't need it
    board_wipe(&ghost_board);
    board_wipe(&state_board);
    display_clear();
}