/** @file    ShipPlacement.h
 *  @authors Harrison Parkes
 *  @date    13th of October 2022
 *  @brief   Ship placement functionality
 *  @note    All functions implementing the ability to place ships on the game board
*/

#ifndef ENCE260_ASSIGNMENT_SHIPPLACEMENT_H
#define ENCE260_ASSIGNMENT_SHIPPLACEMENT_H

#include "game.h"

/**
 * @brief Controls the placement of all ships
 *
 * @return `true` if all ships have been placed, otherwise `false`
 */
extern bool place_ships(bool reset);

#endif //ENCE260_ASSIGNMENT_SHIPPLACEMENT_H