#include "../../drivers/avr/system.h"
#include "../../drivers/navswitch.h"
#include "../../drivers/button.h"
#include "../../drivers/led.h"
#include "../../utils/pacer.h"
#include "../Functions.h"
#include "../GhostGL.h"

typedef enum game_state_e {
    Placing_Ships,
    Waiting,
    Aiming,
    Firing
} Game_State_t;
Game_State_t currentState = Placing_Ships;

bool isPlayerOne = false;

int main (void)
{
    system_init();
    led_init();
    button_init();
    ghostGL_init();
    pacer_init(600); // Initialize pacer to 120Hz

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

            case Waiting:
                win_check();
                break;

            case Aiming:
                if (take_aim(&shot_pos)) {
                    currentState = Firing;
                }
                break;

            case Firing:
                fire(shot_pos);
                currentState = Aiming;
                break;

            default:
                currentState = Waiting;
                break;
        }

        ghostGL_update(); // Refresh the matrix display
        pacer_wait(); // Wait for next pacer tick
    }
}