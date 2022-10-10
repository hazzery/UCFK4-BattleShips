//
// Created by Harry on 4/10/22.
//

#include "Ship.h"

Ship_t ships[NUM_SHIPS] = {
    {.length = 4, .placed_horizontally = false},
    {.length = 3, .placed_horizontally = false},
    {.length = 2, .placed_horizontally = false},
    {.length = 2, .placed_horizontally = false}
};

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
Pos_t ship_end_pos(Ship_t ship)
{
    if (ship.placed_horizontally) { // Ship exists in one row, spanning multiple columns
        return (Pos_t){ship.start_pos.row, ship.start_pos.col + ship.length - 1};
    } else { // Ship exists in one column, spanning multiple rows
        return (Pos_t){ship.start_pos.row + ship.length - 1, ship.start_pos.col};
    }
}