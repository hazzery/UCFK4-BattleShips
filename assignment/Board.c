//
// Created by Harry on 1/10/22.
//

#include "Board.h"
#include <string.h>

Board_t ghost_board;
Board_t state_board;
Board_t oppositions_board;

/**
 * @brief Sets the value of a single cell on the specified board
 *
 * @param board The board to write to
 * @param pos The position of the cell to be set
 * @param state The state to set the cell to
 */
void board_set(Board_t* board, Pos_t pos, Cell_State_t state)
{
    board->grid[pos.row][pos.col] = state;
}

/**
 * @brief Sets the value of a single cell on the specified board
 *
 * @param pos The board to read from
 * @param pos The position of the cell to be read
 */
Cell_State_t board_get(Board_t* board, Pos_t pos)
{
    return board->grid[pos.row][pos.col];
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

/**
 * @brief Sets all of the pixels on the specified board to `0`
 *
 * @param board The board to wipe
 */
void board_wipe(Board_t* board)
{
    memset(board->grid, 0, BOARD_WIDTH * BOARD_HEIGHT);
}

/**
 * @brief Compresses the given board into 5 bytes for transfer over IR UART
 *
 * @param board The board to be compressed
 * @param compressed_board A pointer to where the compressed board should be written
 */
void compress_board(Board_t board, uint8_t compressed_board[])
{
    for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
        for (uint8_t row = 0; row < BOARD_HEIGHT; row++) {
            compressed_board[col] |= board.grid[row][col] << row;
        }
    }
}

/**
 * @brief Uncompresses a 5 byte board to a 35 byte Board_t
 * @param compressed_board A pointer to the 5 byte compressed board
 * @param board A pointer to a Board_t to overwrite with uncompressed board
 */
void uncompress_board(const uint8_t compressed_board[], Board_t* board)
{
    for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
        for (uint8_t row = 0; row < BOARD_HEIGHT; row++) {
            board->grid[row][col] = (compressed_board[col] & (1 << row)) >> row;
        }
    }
}
