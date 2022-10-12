/** @file   Ship.h
 *  @authors Harrison Parkes
 *  @date   1st of October 2022
 *  @brief  Introduces Battleships ship container type
 *  @note   Ship data structure controlling placement of ships on the display matrix
*/

#ifndef ENCE260_ASSIGNMENT_SHIP_H
#define ENCE260_ASSIGNMENT_SHIP_H

#include <stdint.h>
#include <stdbool.h>
#include "Position.h"

#define NUM_SHIPS 4
#define NUM_SHIP_CELLS 11

typedef struct ship_s {
    uint8_t length;
    Pos_t start_pos;
    bool placed_horizontally;
} Ship_t;

extern Ship_t ships[NUM_SHIPS];
extern Pos_t  ship_end_pos(Ship_t ship);
extern void shift_ship(Ship_t* ship, int8_t delta_row, int8_t delta_col);

#endif //ENCE260_ASSIGNMENT_SHIP_H
