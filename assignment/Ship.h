//
// Created by Harry on 1/10/22.
//

#ifndef ENCE260_ASSIGNMENT_SHIP_H
#define ENCE260_ASSIGNMENT_SHIP_H

#include <stdint.h>
#include <stdbool.h>
#include "Position.h"

#define NUM_SHIPS 4

typedef struct ship_s {
    uint8_t length;
    Pos_t start_pos;
    bool placed_horizontally;
} Ship_t;

extern Ship_t ships[NUM_SHIPS];
extern Pos_t  ship_end_pos(Ship_t ship);
extern void shift_ship(Ship_t* ship, int8_t delta_row, int8_t delta_col);

#endif //ENCE260_ASSIGNMENT_SHIP_H
