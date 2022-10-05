//
// Created by Harry on 1/10/22.
//

#include "Board.h"

Cell_State_t board[BOARD_HEIGHT][BOARD_WIDTH];

Cell_State_t board_get(Pos_t pos)
{
    return board[pos.row][pos.col];
}

void board_set(Pos_t pos, Cell_State_t state)
{
    board[pos.row][pos.col] = state;
}