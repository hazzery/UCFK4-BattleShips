/** @file   Board.h
 *  @author Harrison Parkes
 *  @date   1st of October 2022
 *  @brief  5x7 matrix type with related function
 *  @note   Used to store states if each pixel on the display matrix
*/

#ifndef ENCE260_ASSIGNMENT_BOARD_H
#define ENCE260_ASSIGNMENT_BOARD_H

#include "final/game.h"

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

extern void board_set(Board_t* board, Pos_t pos, Cell_State_t state);
extern Cell_State_t board_get(Board_t* board, Pos_t pos);

extern Pos_t move_to_board(int8_t row, int8_t col);

extern void board_wipe(Board_t* board);

extern void compress_board(Board_t board, uint8_t compressed_board[]);
extern void uncompress_board(const uint8_t compressed_board[], Board_t* board);

#endif //ENCE260_ASSIGNMENT_BOARD_H
