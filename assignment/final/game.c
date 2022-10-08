#include "../../drivers/avr/system.h"
#include "../../drivers/navswitch.h"
//#include "../../drivers/display.h"
#include "../../drivers/ledmat.h"
//#include "../../drivers/led.h"
#include "../../utils/pacer.h"
#include "../../utils/tinygl.h"
#include "../Functions.h"

// Dominic, please ignore these pragma lines, it makes my IDE happy
// because generally having an infinite loop is a bad thing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
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
    ledmat_init();
//    led_init();
    pacer_init(120); // Initialize pacer to 12Hz

    Pos_t shot_pos = {.row = 0, .col = 0};

    while (1)
    {
        // Get new readings from navswitch
        navswitch_update();

        switch (currentState) {
            case Placing_Ships:
                if (place_ships()) {
                    currentState = Waiting;
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
                currentState = Waiting;
                break;

            default:
                currentState = Waiting;
                break;
        }

        // Refresh the matrix display
//        display_update();
        tinygl_update();
        // Wait for next pacer tick
        pacer_wait();
    }
}
#pragma clang diagnostic pop