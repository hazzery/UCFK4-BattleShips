/** @file   Ship.h
 *  @authors Harrison Parkes
 *  @date   1st of October 2022
 *  @brief  Introduces Battleships ship container type
 *  @note   Ship data structure controlling placement of ships on the display matrix
*/

#ifndef ENCE260_ASSIGNMENT_SHIP_H
#define ENCE260_ASSIGNMENT_SHIP_H

#include "final/game.h"

#define NUM_SHIPS 4

#define SHIP1_LENGTH 4
#define SHIP2_LENGTH 3
#define SHIP3_LENGTH 2
#define SHIP4_LENGTH 2

#define NUM_SHIP_CELLS (SHIP1_LENGTH + SHIP2_LENGTH + SHIP3_LENGTH + SHIP4_LENGTH)

typedef struct ship_s {
    uint8_t length;
    Pos_t start_pos;
    bool placed_horizontally;
} Ship_t;

extern Ship_t ships[NUM_SHIPS];

/**
 * @brief Calculates the last position this ship occupies
 *
 * As as ship is just a straight line, we get the last position
 * the line will take up on the board assuming the line starts at
 * `ship.start_pos`, is `ship.length` long, and either vertical
 * or horizontal based on `ship.placed_horizontally`
 *
 * @param ship The ship to get the end position
 * @return The position of the ship's end (tail)
 */
extern Pos_t  ship_end_pos(Ship_t ship);

#endif //ENCE260_ASSIGNMENT_SHIP_H
