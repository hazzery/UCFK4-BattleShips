/** @file    TurnEvents.h
 *  @authors Harrison Parkes
 *  @date    13th of October 2022
 *  @brief   Events that occur on every turn of the game
 *  @note    Functions implementing core events that happen in every turn of battleships
*/

#ifndef ENCE260_ASSIGNMENT_TURNEVENTS_H
#define ENCE260_ASSIGNMENT_TURNEVENTS_H

#include "game.h"

/**
 * @brief Allows player to choose where to fire their missile
 *
 * Croshair begins at top left corner, and is moved with the navswitch
 * pressing the navswitch down confirms the position to fire at
 *
 * @return The position selected by the user
 */
extern bool take_aim(Pos_t* shot_pos);

/**
 * @brief "Fires" a "missile" at the oppositions game board
 *
 * Gets the current state of the oppositions board at the given position
 * and updates the state accordingly
 *
 * @param pos The position on the opposition's board to fire at
 */
extern void fire(Pos_t pos);

/**
 * @brief Checks to see if all ships have been sunk on this Fun Kit
 *
 * @return `true` if game has been won, otherwise `false`
 */
extern bool all_ships_sunk(void);

/**
 * @brief Sets number of ships hit to 0
 */
void reset_shot_count(void);

#endif //ENCE260_ASSIGNMENT_TURNEVENTS_H
