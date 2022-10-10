//
// Created by Harry on 9/10/22.
//

#include "GhostBoard.h"
#include <string.h>

bool ghost_board[BOARD_HEIGHT][BOARD_WIDTH];

/**
 * @brief Wipes the ghosting board, setting all cells to 0
 */
void ghost_wipe(void)
{
    memset(ghost_board, 0, BOARD_WIDTH * BOARD_HEIGHT);
}

/**
 * @brief Sets the value of a single cell on the ghosting board
 *
 * @param pos The position of the cell to be set
 * @param state The state to set the cell to
 */
void ghost_set(Pos_t pos, bool state)
{
    ghost_board[pos.row][pos.col] = state;
}