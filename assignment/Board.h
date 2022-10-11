//
// Created by Harry on 1/10/22.
//

#ifndef ENCE260_ASSIGNMENT_BOARD_H
#define ENCE260_ASSIGNMENT_BOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "Position.h"

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 7

typedef enum __attribute__ ((__packed__)) cell_state_e{
    Empty,
    Ship,
    Hit,
    Miss
} Cell_State_t;

extern Cell_State_t board_get(Pos_t pos);
extern void board_set(Pos_t pos, Cell_State_t state);

extern bool is_on_board(Pos_t pos);
extern Pos_t move_to_board(int8_t row, int8_t col);

extern void compress_board(uint8_t compressed_board[]);
extern void uncompress_board(uint8_t compressed_board[]);

#endif //ENCE260_ASSIGNMENT_BOARD_H
