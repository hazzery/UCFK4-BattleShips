/** @file   Ship.c
 *  @authors Harrison Parkes
 *  @date   1st of October 2022
 *  @brief  Introduces Battleships ship container type
 *  @note   Ship data structure controlling placement of ships on the display matrix
*/

#include "include/Ship.h"
#include "include/game.h"

Ship_t ships[NUM_SHIPS] = {
    {.length = SHIP1_LENGTH, .placed_horizontally = false},
    {.length = SHIP2_LENGTH, .placed_horizontally = false},
    {.length = SHIP3_LENGTH, .placed_horizontally = false},
    {.length = SHIP4_LENGTH, .placed_horizontally = false}
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