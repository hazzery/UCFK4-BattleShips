/**
 *  @file   Board.h
 *  @author Harrison Parkes
 *  @date   1st of October 2022
 *  @brief  5x7 matrix type with related function
 *  @note   Used to store states if each pixel on the display matrix
*/

#ifndef ENCE260_ASSIGNMENT_BOARD_H
#define ENCE260_ASSIGNMENT_BOARD_H

#include "game.h"

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 7

// Force the enum values to only use one byte
typedef enum __attribute__ ((__packed__)) cell_state_e{
    Empty,
    Ship,
    Hit,
    Miss
} Cell_State_t;

typedef struct board_s {
    Cell_State_t grid[BOARD_HEIGHT][BOARD_WIDTH];
} Board_t;

extern Board_t ghost_board;
extern Board_t state_board;
extern Board_t oppositions_board;

/**
 * @brief Sets the value of a single cell on the specified board
 *
 * @param board The board to write to
 * @param pos The position of the cell to be set
 * @param state The state to set the cell to
 */
extern void board_set(Board_t* board, Pos_t pos, Cell_State_t state);

/**
 * @brief Gets the value of a single cell on the specified board
 *
 * @param pos The board to read from
 * @param pos The position of the cell to be read
 */
extern Cell_State_t board_get(Board_t* board, Pos_t pos);

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
extern Pos_t move_to_board(int8_t row, int8_t col);

/**
 * @brief Sets all of the pixels on the specified board to `0`
 *
 * @param board The board to wipe
 */
extern void board_wipe(Board_t* board);

/**
 * @brief Compresses the given board into 5 bytes for transfer over IR UART
 *
 * @param board The board to be compressed
 * @param compressed_board A pointer to where the compressed board should be written
 */
extern void compress_board(Board_t board, Bitmap_t compressed_board);

/**
 * @brief Uncompresses a 5 byte board to a 35 byte Board_t
 *
 * @param compressed_board A pointer to the 5 byte compressed board
 * @param board A pointer to a Board_t to overwrite with uncompressed board
 */
extern void uncompress_board(const Bitmap_t compressed_board, Board_t* board);

#endif //ENCE260_ASSIGNMENT_BOARD_H
