#include "../../drivers/avr/system.h"
#include "../../drivers/navswitch.h"
#include "../../drivers/display.h"
#include "../../drivers/ledmat.h"
#include "../../drivers/led.h"
#include "../../utils/pacer.h"
#include "../Functions.h"

int main (void)
{
    system_init();
    ledmat_init();
    led_init();
    pacer_init(120); // Initialize pacer to 12Hz

    bool is_placing_ships = true;
    Pos_t shot_pos = {.row = 0, .col = 0};

// Dominic, please ignore these pragma lines, it makes my IDE happy
// because generally having an infinite loop is a bad thing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (1)
    {
        // Get new readings from navswitch
        navswitch_update();

        if (is_placing_ships) {
            place_ships();
        } else {
            win_check(); // wait for other player
            shot_pos = take_aim();
            fire(shot_pos);
        }

        // Refresh the matrix display
        display_update();
        // Wait for next pacer tick
        pacer_wait();
    }
#pragma clang diagnostic pop
}
