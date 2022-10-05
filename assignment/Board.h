//
// Created by Harry on 1/10/22.
//

#ifndef ENCE260_ASSIGNMENT_BOARD_H
#define ENCE260_ASSIGNMENT_BOARD_H

#include <stdint.h>
#include "Position.h"

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 7

typedef enum cell_state_e {
    Empty,
    Ship,
    Hit,
    Miss
} Cell_State_t;

extern Cell_State_t board_get(Pos_t pos);
extern void board_set(Pos_t pos, Cell_State_t state);



#endif //ENCE260_ASSIGNMENT_BOARD_H
