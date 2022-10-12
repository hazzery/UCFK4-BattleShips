/** @file    Functions.h
 *  @authors Harrison Parkes, Dominic Dumble
 *  @date    2nd of October 2022
 *  @brief   Core game functionality
 *  @note    All functions core to the battleships game
*/

#ifndef ENCE260_ASSIGNMENT_FUNCTIONS_H
#define ENCE260_ASSIGNMENT_FUNCTIONS_H

#include "Position.h"

extern bool place_ships(void);
extern bool take_aim(Pos_t* shot_pos);
extern void fire(Pos_t pos);
extern bool win_check(void);
extern void swap_board_data(void);
extern char wait_for_signal(void);
extern void win_signal(void);
extern void game_lost(void);

#endif //ENCE260_ASSIGNMENT_FUNCTIONS_H
