/** @file    GhostGL.h
 *  @authors Harrison Parkes
 *  @date    9th of October 2022
 *  @brief   Matrix display graphics
 *  @note    Reads from the ghost and state boards to update the matrix display
*/

#ifndef ENCE260_ASSIGNMENT_GHOSTGL_H
#define ENCE260_ASSIGNMENT_GHOSTGL_H

#include "Board.h"

extern void ghostGL_init(void);
extern void ghostGL_update(void);
extern void ghostGL_clear(void);

#endif //ENCE260_ASSIGNMENT_GHOSTGL_H
