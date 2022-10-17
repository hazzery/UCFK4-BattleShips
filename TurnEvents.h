/** @file    TurnEvents.h
 *  @authors Harrison Parkes
 *  @date    13th of October 2022
 *  @brief   Events that occur on every turn of the game
 *  @note    Functions implementing core events that happen in every turn of battleships
*/

#ifndef ENCE260_ASSIGNMENT_TURNEVENTS_H
#define ENCE260_ASSIGNMENT_TURNEVENTS_H

#include "final/game.h"

extern bool take_aim(Pos_t* shot_pos);
extern void fire(Pos_t pos);

/**
 * @brief Checks to see if all ships have been sunk on this Fun Kit
 *
 * @return `true` if game has been won, otherwise `false`
 */
extern bool all_ships_sunk(void);

#endif //ENCE260_ASSIGNMENT_TURNEVENTS_H
