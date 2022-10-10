//
// Created by Harry on 9/10/22.
//

#include "GhostBoard.h"
#include <string.h>

bool ghost_board[BOARD_HEIGHT][BOARD_WIDTH];

void ghost_wipe(void)
{
    memset(ghost_board, 0, BOARD_WIDTH * BOARD_HEIGHT);
}

void ghost_set(Pos_t pos, bool state)
{
    ghost_board[pos.row][pos.col] = state;
}