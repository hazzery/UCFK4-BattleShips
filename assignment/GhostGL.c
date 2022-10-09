//
// Created by Harry on 9/10/22.
//

#include "GhostGL.h"
#include "../drivers/display.h"

extern bool ghost_board[BOARD_HEIGHT][BOARD_WIDTH];
extern Cell_State_t board[BOARD_HEIGHT][BOARD_WIDTH];

void ghostGL_init(void)
{
    display_init();
}

void ghostGL_update(void)
{
    for (uint8_t row = 0; row < BOARD_HEIGHT; row ++) {
        for (uint8_t col = 0; col < BOARD_WIDTH; col ++) {
            display_pixel_set(col, row, board[row][col] || ghost_board[row][col]);
        }
    }
    display_update();
}