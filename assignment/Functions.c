//
// Created by Harry on 2/10/22.
//

#include "../drivers/navswitch.h"
#include "../drivers/display.h"
#include "../utils/tinygl.h"
#include "../drivers/led.h"
#include "Functions.h"
#include "Board.h"
#include "Ship.h"


/**
 * @brief converts a Pos_t to an tinygl_point_t
 *
 * @param pos Pos_t object to convert
 * @return tinygl_point_t object
 */
static inline tinygl_point_t pos_to_point(Pos_t pos)
{
    return (tinygl_point_t){pos.row, pos.col};
}

/**
 * @brief checks to see if the current position of `ship` overlaps with the position of any other ships
 *
 * @param ship the ship to check the position of
 * @return `true` if ship does not overlap, otherwise `false`
 */
static bool placement_is_valid(Ship_t ship)
{
    Pos_t current_pos;
    for (uint8_t i = 0; i < ship.length; i++) {

        if (ship.placed_horizontally)
            current_pos = (Pos_t){ship.start_pos.row + i, ship.start_pos.col};
        else
            current_pos = (Pos_t){ship.start_pos.row, ship.start_pos.col + i};

        if (board_get(current_pos) != Empty) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Sets the position of `ship` into the cells of the game board
 *
 * DO NOT CALL THIS FUNCTION IF THE SHIP'S POSITION HAS NOT BEEN VALIDATED
 *
 * @param ship The ship to be placed on the board
 */
static void set_ship(Ship_t ship)
{
    Pos_t current_pos;
    for (uint8_t i = 0; i < ship.length; i++) {

        if (ship.placed_horizontally)
            current_pos = (Pos_t){ship.start_pos.row + i, ship.start_pos.col};
        else
            current_pos = (Pos_t){ship.start_pos.row, ship.start_pos.col + i};

        board_set(current_pos, Ship);
    }
}

/**
 * @brief Controls the placing of an individual ship onto the board
 *
 * This function must be called repeatedly untill all ships have been placed
 *
 * @param ship The ship to be placed on the board
 */
static bool place_ship(Ship_t ship)
{
    // While navswitch isn't pushed in
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        if (placement_is_valid(ship)) {
            set_ship(ship);
            return true;
        }
    }

    // Read navswitch values
    int8_t ship_start_row = ship.start_pos.row - (navswitch_push_event_p(NAVSWITCH_NORTH) - navswitch_push_event_p(NAVSWITCH_SOUTH));
    int8_t ship_start_col = ship.start_pos.col + navswitch_push_event_p(NAVSWITCH_EAST) - navswitch_push_event_p(NAVSWITCH_WEST);

    ship.start_pos = move_to_board(ship_start_row, ship_start_col);

    Pos_t ship_end = ship_end_pos(ship);
    // If ship tail not on the LED matrix...
    if (!is_on_board(ship_end))
        return false;

//    display_pixel_set(ship.start_pos.col, ship.start_pos.row, 1);
    tinygl_draw_line(pos_to_point(ship.start_pos), pos_to_point(ship_end), 1);
    return false;
}

/**
 * @brief Controlls the placement of all `NUM_SHIPS` ships
 *
 * @return `true` if all ships have been placed, otherwise `false`
 */
bool place_ships(void)
{
    static uint8_t ships_placed = 0;

    ships_placed += place_ship(ships[ships_placed]);

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