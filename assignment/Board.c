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

/**
 * @brief  Checks if the given position is visible on the 5x7 grid
 *
 * @param pos The position to check
 * @return `true` if the position is on the board, otherwise `false`
 */
bool is_on_board(Pos_t pos)
{
    if (pos.row > BOARD_HEIGHT - 1)
        return false;

    if ( pos.col > BOARD_WIDTH - 1)
        return false;

    return true;
}

/**
 * @brief Moves the given position to its nearest position on the board if it was not
 *
 * Essentially just forces the coordinates onto the bounds of the board.
 * Moves negative ordinates to 0, or large ordinates to BOARD_HEIGHT/WIDTH.
 * Used to prevent user from firing / placing a ship off of the board.
 *
 * @param row the row to be moved
 * @param col the column to be moved
 * @return a `Pos_t` of the nearest board position to the given coordinates
 */
Pos_t move_to_board(int8_t row, int8_t col)
{
    if (row < 0)
        row = 0;
    else if (row > BOARD_HEIGHT - 1)
        row = BOARD_HEIGHT - 1;

    if (col < 0)
        col = 0;
    else if(col > BOARD_WIDTH - 1)
        col = BOARD_WIDTH - 1;

    return (Pos_t) {
        .row = row, .col = col
    };
}