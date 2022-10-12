/** @file    Position.h
 *  @authors Harrison Parkes
 *  @date    1st of October 2022
 *  @brief   Introduces position type
 *  @note    Row, column based coordinate data structure
*/

#ifndef ENCE260_ASSIGNMENT_POSITION_H
#define ENCE260_ASSIGNMENT_POSITION_H

#include <stdint.h>

typedef struct position_s {
    uint8_t row;
    uint8_t col;
} Pos_t;

#endif //ENCE260_ASSIGNMENT_POSITION_H
