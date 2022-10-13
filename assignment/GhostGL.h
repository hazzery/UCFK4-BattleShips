/** @file    GhostGL.h
 *  @authors Harrison Parkes
 *  @date    9th of October 2022
 *  @brief   Matrix display graphics
 *  @note    Reads from the ghost and state boards to update the matrix display
*/

#ifndef ENCE260_ASSIGNMENT_GHOSTGL_H
#define ENCE260_ASSIGNMENT_GHOSTGL_H


extern void ghostGL_init(void);

/**
 * @brief Updates the states of the LEDs on the matrix display
 * Non zero values on the board or the ghost board will enable their respective LED.
 */
extern void ghostGL_update(void);

/**
 * @brief Sets all of the pixels off
 */
extern void ghostGL_clear(void);

#endif //ENCE260_ASSIGNMENT_GHOSTGL_H
