/** @file    GhostGL.h
 *  @authors Harrison Parkes, Dominic Dumble
 *  @date    9th of October 2022
 *  @brief   Matrix display graphics
 *  @note    Reads from the ghost and state boards to update the matrix display
*/

#ifndef ENCE260_ASSIGNMENT_GHOSTGL_H
#define ENCE260_ASSIGNMENT_GHOSTGL_H

/**
 * @brief Initializes the display, ready for use
 * Must be called exactly once, at the beginning of the program.
 */
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

/**
 * @brief compresses board for communication before wiping data
 * 
 * @param compressed_board where compressed board data is stored
*/
extern void preclear_compress(Bitmap_t compressed_board);

#endif //ENCE260_ASSIGNMENT_GHOSTGL_H
