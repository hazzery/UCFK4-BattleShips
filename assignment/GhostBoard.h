//
// Created by Harry on 9/10/22.
//

#ifndef ENCE260_ASSIGNMENT_GHOSTING_H
#define ENCE260_ASSIGNMENT_GHOSTING_H

#ifndef BOARD_WIDTH
#define BOARD_WIDTH 5
#define BOARD_HEIGHT 7
#endif

#include "Position.h"
#include <stdbool.h>

extern void ghost_wipe(void);
extern void ghost_set(Pos_t pos, bool state);

#endif //ENCE260_ASSIGNMENT_GHOSTING_H
