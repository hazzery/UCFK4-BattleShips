/** @file    Communications.c
 *  @authors Harrison Parkes, Dominic Dumble
 *  @date    13th of October 2022
 *  @brief   Necessary communication functionality
 *  @note    Implements the IR communications necessary for battleships
*/

#include "../drivers/avr/ir_uart.h"
#include "../drivers/navswitch.h"
#include "../drivers/button.h"
#include "../drivers/led.h"
#include "../utils/pacer.h"
#include "../utils/tinygl.h"
#include "Communications.h"
#include "final/game.h"
#include "Board.h"

extern bool is_player_one;
extern uint8_t compressed_board;

/**
 * @brief player one select and swaps game board information
 * 
 * waits until a player pushes the button and assigns them as player one
 * compresses player board and sends to other player before receiving
 * other players board and vice versa if player 2
 */
void swap_board_data(void)
{
    // Loops until one player presses Button1
    // Player that presses button becomes Player1
    bool playerSelected = false;
    while (!playerSelected) {
        button_update();
        if (button_push_event_p(BUTTON1)) {
            ir_uart_putc(PLAYER1_SIGNAL);
            is_player_one = true;
            playerSelected = true;
        } else if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == PLAYER1_SIGNAL) {
                led_set(LED1, HIGH);
                is_player_one = false;
                playerSelected = true;
            }
        }
    }

    //uint8_t compressed_board[BOARD_WIDTH];
    //compress_board(state_board, compressed_board);

    uint8_t oppositions_compressed_board[BOARD_WIDTH];

    // Slow down pacer for IR communication
    pacer_init(TRANSFER_FREQUENCY);
    bool board_received = false;

    if (is_player_one) {
        // Player1 transfers their board data first...
        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
            while (!ir_uart_write_ready_p()) continue;
            ir_uart_putc(compressed_board[col]);
            pacer_wait();
        }
        while (!board_received) {
            // ...then receives the opposition's.
            for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
                while (!ir_uart_read_ready_p()) continue;
                oppositions_compressed_board[col] = ir_uart_getc();
                pacer_wait();
            }
            board_received = true;
        }
    } else {
        // Player2 does the exact opposite of Player1
        while (!board_received) {
            for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
                while (!ir_uart_read_ready_p()) continue;
                oppositions_compressed_board[col] = ir_uart_getc();
                pacer_wait();
            }
            board_received = true;
        }
        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
            while (!ir_uart_write_ready_p()) continue;
            ir_uart_putc(compressed_board[col]);
            pacer_wait();
        }
    }

    // Speed the pacer back up for running the display
    pacer_init(DISPLAY_FREQUENCY);
    uncompress_board(oppositions_compressed_board, &oppositions_board);
}

/**
 * @brief Receives status signal from the opposition
 *
 * @return The signal from the opposition, 'W' if the opposition has won, 'T' if it time to take another turn
*/
char wait_for_signal(void)
{
    while (!ir_uart_read_ready_p()) continue;

    return ir_uart_getc();
}

/**
 * @brief Sends signal to the opposition to tell them the game has been won
 * and shows the user they have won.
 */
void win_signal(void)
{
    while (!ir_uart_write_ready_p()) continue;

    ir_uart_putc(WIN_SIGNAL);

    tinygl_init(DISPLAY_FREQUENCY);
    tinygl_draw_char(WIN_SIGNAL, tinygl_point(0, 0));
    while (!navswitch_push_event_p(NAVSWITCH_PUSH)) {
        tinygl_update();
        pacer_wait();
    }
}

/**
 * @brief Shows the user they have lost the game
 */
void game_lost(void)
{
    tinygl_init(DISPLAY_FREQUENCY);
    tinygl_draw_char(LOSS_SIGNAL, tinygl_point(0, 0));
    while (!navswitch_push_event_p(NAVSWITCH_PUSH)) {
        tinygl_update();
        pacer_wait();
    }
}