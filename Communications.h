/** @file    Communications.h
 *  @authors Harrison Parkes, Dominic Dumble
 *  @date    13th of October 2022
 *  @brief   Necessary communication functionality
 *  @note    Implements the IR communications necessary for battleships
*/

#ifndef ENCE260_ASSIGNMENT_COMMUNICATIONS_H
#define ENCE260_ASSIGNMENT_COMMUNICATIONS_H

#include "game.h"

#define WIN_SIGNAL 'W'
#define LOSS_SIGNAL 'L'
#define NEXT_TURN_SIGNAL_P1 'T'
#define NEXT_TURN_SIGNAL_P2 'U'
#define PLAYER1_SIGNAL '1'

/**
 * @brief player one select and swaps game board information
 *
 * waits until a player pushes the button and assigns them as player one
 * compresses player board and sends to other player before receiving
 * other players board and vice versa if player 2
 */
extern void swap_board_data(Bitmap_t compressed_board);

/**
 * @brief Receives status signal from the opposition
 *
 * @return The signal from the opposition, 'W' if the opposition has won, 'T' if it time to take another turn
*/
extern char wait_for_signal(bool is_player_one);

/**
 * @brief Sends signal to the opposition to tell them the game has been won
 * and shows the user they have won.
 */
extern void win_signal(void);

/**
 * @brief Shows the user they have lost the game
 */
extern void game_lost(void);

#endif //ENCE260_ASSIGNMENT_COMMUNICATIONS_H
