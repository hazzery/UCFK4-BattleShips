#include "../../drivers/avr/system.h"
#include "../../drivers/display.h"
#include "../../drivers/ledmat.h"
#include "../../drivers/led.h"
#include "../Functions.h"

int main (void)
{
    system_init();
    ledmat_init();
    led_init();
//    pacer_init();

//    place_ships();
    display_pixel_set(0, 0, 1);
    1==1;

//    Pos_t shot_pos = take_aim();
//    led_set(0, 0);

//#pragma clang diagnostic push
//#pragma ide diagnostic ignored "EndlessLoop"
//    while (1)
//    {
//        Pos_t shot_pos = take_aim();
//        fire(shot_pos);
//        win_check(); // And wait for other player's turn
//    }
//#pragma clang diagnostic pop
}
