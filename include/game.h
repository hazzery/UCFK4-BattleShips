/** @file    game.h
 *  @authors Harrison Parkes
 *  @date    13th of October 2022
 *  @brief   Game wide definitions
*/

#ifndef ENCE260_ASSIGNMENT_GAME_H
#define ENCE260_ASSIGNMENT_GAME_H

#include <stdbool.h>
#include <stdint.h>
#include "../../common/Position.h"

#define DISPLAY_FREQUENCY 300

#define BLUE_LED 0

#define HIGH 1
#define LOW 0

#define BOARD_WIDTH 5

typedef uint8_t Bitmap_t[BOARD_WIDTH];

#endif //ENCE260_ASSIGNMENT_GAME_H
