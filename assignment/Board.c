//
// Created by Harry on 1/10/22.
//

#include "Board.h"

State_t board[BOARD_HEIGHT][BOARD_WIDTH];

State_t board_get(Pos_t pos)
{
    return board[pos.row][pos.col];
}

void board_set(Pos_t pos, State_t state)
{
    board[pos.row][pos.col] = state;
}