#include "../../drivers/avr/ir_uart.h"
#include "../../drivers/avr/system.h"
#include "../../drivers/navswitch.h"
#include "../../drivers/button.h"
#include "../../drivers/led.h"
#include "../../utils/pacer.h"
#include "../Functions.h"
#include "../GhostGL.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
typedef enum game_state_e {
    Placing_Ships,
    Initializing,
    Waiting,
    Aiming,
    Firing,
    Won
} Game_State_t;
Game_State_t currentState = Placing_Ships;

bool is_player_one = false;

int main (void)
{
    led_init();
    button_init();
    system_init();
    ir_uart_init();
    ghostGL_init();
    pacer_init(300); // Initialize pacer to 300Hz so display columns update at 60Hz

    led_set(LED1, 0);

    Pos_t shot_pos = {.row = 0, .col = 0};

    while (1)
    {
        navswitch_update(); // Get new readings from navswitch
        button_update(); // Get new readings from button

        switch (currentState) {
            case Placing_Ships:
                if (place_ships()) {
                    ghostGL_clear();
                    currentState = Initializing;
                }
                break;

            case Initializing:
                swap_board_data();
                if (!isPlayerOne) {
                    currentState = Waiting;
                } else {
                    currentState = Aiming;
                }
                break;

            case Waiting:
                if (win_check()) {
                    currentState = Won;
                }
                break;

            case Aiming:
                if (take_aim(&shot_pos)) {
                    shot_pos = (Pos_t){.row = 0, .col = 0};
                    currentState = Firing;
                }
                break;

            case Firing:
                fire(shot_pos);
                currentState = Waiting;
                break;

            default:
                currentState = Waiting;
                break;
        }

        ghostGL_update(); // Refresh the matrix display
        pacer_wait(); // Wait for next pacer tick
    }
}
#pragma clang diagnostic pop