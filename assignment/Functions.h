//
// Created by Harry on 2/10/22.
// Edited by Dominic
//

#ifndef ENCE260_ASSIGNMENT_FUNCTIONS_H
#define ENCE260_ASSIGNMENT_FUNCTIONS_H

#include "Position.h"

extern bool place_ships(void);
//extern Pos_t take_aim(void);
extern bool take_aim(Pos_t* shot_pos);
extern void fire(Pos_t pos);
extern bool win_check(void);
extern void swap_board_data(void);
extern char wait_for_signal(void);
extern void win_signal(void);
extern void game_lost(void);

#endif //ENCE260_ASSIGNMENT_FUNCTIONS_H
