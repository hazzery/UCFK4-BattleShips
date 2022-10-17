/** @file    game.c
 *  @authors Harrison Parkes, Dominic Dumble
 *  @date    1st of October 2022
 *  @brief   Battler Ships main loop
*/

#include "../../drivers/avr/ir_uart.h"
#include "../../drivers/avr/system.h"
#include "../../drivers/navswitch.h"
#include "../../drivers/button.h"
#include "../../drivers/led.h"
#include "../../utils/pacer.h"
#include "../Communications.h"
#include "../ShipPlacement.h"
#include "../TurnEvents.h"
#include "../GhostGL.h"
#include "game.h"

typedef enum game_state_e {
    Placing_Ships,
    Initializing,
    Waiting,
    Aiming,
    Firing,
    Won,
    Lost,
    Done
} Game_State_t;
Game_State_t currentState = Placing_Ships;

bool is_player_one = false;
uint8_t compressed_board[BOARD_WIDTH];

int main (void)
{
    led_init();
    button_init();
    system_init();
    ir_uart_init();
    ghostGL_init();
    pacer_init(DISPLAY_FREQUENCY); // Initialize pacer to 300Hz so display columns update at 60Hz

    led_set(BLUE_LED, LOW);

    Pos_t shot_pos = {.row = 0, .col = 0};
    char signal = 0;

    while (1)
    {
        navswitch_update(); // Get new readings from navswitch
        button_update(); // Get new readings from button

        switch (currentState) {
            case Placing_Ships:
                if (place_ships()) {
                    preclear_compress(compressed_board);
                    ghostGL_clear();
                    currentState = Initializing;
                }
                break;

            case Initializing:
                swap_board_data(compressed_board);
                if (is_player_one) {
                    currentState = Aiming;
                } else {
                    currentState = Waiting;
                }
                break;

            case Waiting:
                signal = wait_for_signal(is_player_one);
                if (signal == WIN_SIGNAL) {
                    currentState = Lost;
                } else if ((signal == NEXT_TURN_SIGNAL_P1) || (signal == NEXT_TURN_SIGNAL_P2)) {
                    currentState = Aiming;
                }
                led_set(BLUE_LED, LOW);
                break;

            case Aiming:
                if (take_aim(&shot_pos)) {
                    currentState = Firing;
                }
                break;

            case Firing:
                fire(shot_pos);
                shot_pos = (Pos_t){.row = 0, .col = 0};
                if (all_ships_sunk()) {
                    currentState = Won;
                    led_set(BLUE_LED, LOW);
                } else {
                    currentState = Waiting;
                    while (!ir_uart_write_ready_p()) continue;
                    if (is_player_one) {
                        ir_uart_putc(NEXT_TURN_SIGNAL_P2);
                    } else {
                        ir_uart_putc(NEXT_TURN_SIGNAL_P1);
                    }
                }
                break;

            case Won:
                win_signal();
                currentState = Done;
                break;

            case Lost:
                //This state is only activated by signal from over board winning
                game_lost();
                currentState = Done;
                break;

            case Done:
                break;

            default:
                currentState = Waiting;
                break;
        }

        ghostGL_update(); // Refresh the matrix display
        pacer_wait(); // Wait for next pacer tick
    }
}