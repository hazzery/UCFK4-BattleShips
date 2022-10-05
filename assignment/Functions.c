//
// Created by Harry on 2/10/22.
//

#include "../drivers/navswitch.h"
#include "../drivers/display.h"
#include "../drivers/led.h"
#include "Functions.h"
#include "Board.h"
#include "Ship.h"

static void place_ship(Ship_t ship)
{
    // While navswitch isn't pushed in
    if (navswitch_up_p(NAVSWITCH_PUSH)) {

        // Read navswitch values
        int8_t ship_start_row = ship.start_pos.row - (navswitch_push_event_p(NAVSWITCH_NORTH) - navswitch_push_event_p(NAVSWITCH_SOUTH));
        int8_t ship_start_col = ship.start_pos.col + navswitch_push_event_p(NAVSWITCH_EAST) - navswitch_push_event_p(NAVSWITCH_WEST);

        // If row value actually on the LED matrix, update position
        if (ship_start_row >= 0 && ship_start_row <= BOARD_HEIGHT)
            ship.start_pos.row = ship_start_row;

        // If column value actually on the LED matrix, update position
        if (ship_start_col >= 0 && ship_start_col <= BOARD_WIDTH)
            ship.start_pos.col = ship_start_col;

        display_pixel_set(ship.start_pos.col, ship.start_pos.row, 1);
    }
}

/**
 * @brief Controlls the placement of all `NUM_SHIPS` ships
 *
 * @return `true` if all ships have been placed, otherwise `false`
 */
bool place_ships(void)
{
    static uint8_t ships_placed = 0;
//    static int8_t prev_ships_placed = -1;

//    if (prev_ships_placed != ships_placed)
    place_ship(ships[ships_placed]);


    return ships_placed == NUM_SHIPS;
}

Pos_t take_aim(void)
{
    // Shot initial position is top left corner
    Pos_t shot_pos = {.row = 0, .col = 0};


    // While navswitch isn't pushed in
    while (navswitch_up_p(NAVSWITCH_PUSH)) {
        // Get new readings from navswitch
        navswitch_update();
        led_set(0, 1);

        // Read navswitch values
        int8_t shot_row = shot_pos.row - (navswitch_push_event_p(NAVSWITCH_NORTH) - navswitch_push_event_p(NAVSWITCH_SOUTH));
        int8_t shot_col = shot_pos.col + navswitch_push_event_p(NAVSWITCH_EAST) - navswitch_push_event_p(NAVSWITCH_WEST);

        // If row value actually on the LED matrix, update position
        if (shot_row >= 0 && shot_row <= BOARD_HEIGHT)
            shot_pos.row = shot_row;

        // If column value actually on the LED matrix, update position
        if (shot_col >= 0 && shot_col <= BOARD_WIDTH)
            shot_pos.col = shot_col;

        display_pixel_set(shot_pos.col, shot_pos.row, 1);
        display_update();
    }
    //placement is confirmed
    return shot_pos;
}

void fire(Pos_t pos)
{
    Cell_State_t board_state = board_get(pos);
    if (board_state == Ship) {
        board_set(pos, Hit);
    } else if (board_state == Empty) {
        board_set(pos, Miss);
    }
}
void win_check(void)
{

}