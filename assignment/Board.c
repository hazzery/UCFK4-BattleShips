//
// Created by Harry on 1/10/22.
//

#include "Board.h"

Cell_State_t board[BOARD_HEIGHT][BOARD_WIDTH];

/**
 * @brief Reads the state of the specified cell
 *
 * @param pos The cell to get the state of
 * @return The state of cell at `pos`
 */
Cell_State_t board_get(Pos_t pos)
{
    return board[pos.row][pos.col];
}

/**
 * @brief Sets the state of the specified cell
 *
 * @param pos The cell to set the state of
 * @param state The state to set the cell to
 */
void board_set(Pos_t pos, Cell_State_t state)
{
    board[pos.row][pos.col] = state;
}