#include "../../drivers/avr/system.h"
#include "../../drivers/navswitch.h"
#include "../../drivers/display.h"
#include "../../drivers/ledmat.h"
#include "../../drivers/led.h"
#include "../../utils/pacer.h"
#include "../Functions.h"

typedef enum game_state_e {
    Placing_Ships,
    Waiting,
    Aiming,
    Firing
} Game_State_t;

Game_State_t currentState = Placing_Ships;

int main (void)
{
    system_init();
    ledmat_init();
    led_init();
    pacer_init(120); // Initialize pacer to 12Hz

    Pos_t shot_pos = {.row = 0, .col = 0};

// Dominic, please ignore these pragma lines, it makes my IDE happy
// because generally having an infinite loop is a bad thing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (1)
    {
        // Get new readings from navswitch
        navswitch_update();

        switch (currentState) {
            case Placing_Ships:
                place_ships();
                break;
            case Waiting:
                win_check();
                break;
            case Aiming:
                shot_pos = take_aim();
                break;
            case Firing:
                fire(shot_pos);
                break;
        }

        // Refresh the matrix display
        display_update();
        // Wait for next pacer tick
        pacer_wait();
    }
#pragma clang diagnostic pop
}
