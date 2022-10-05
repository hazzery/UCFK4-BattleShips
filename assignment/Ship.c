//
// Created by Harry on 4/10/22.
//

#include "Ship.h"

Ship_t ships[NUM_SHIPS] = {
    {.length = 4},
    {.length = 3},
    {.length = 2},
    {.length = 1},
};

Pos_t ship_end_pos(Ship_t ship)
{
    if (ship.placed_horizontally)
        return (Pos_t){ship.start_pos.row + ship.length, ship.start_pos.col};
    else
        return (Pos_t){ship.start_pos.row, ship.start_pos.col + ship.length};
}