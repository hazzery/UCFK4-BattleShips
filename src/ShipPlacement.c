/** @file    ShipPlacement.c
 *  @authors Harrison Parkes
 *  @date    13th of October 2022
 *  @brief   Ship placement functionality
 *  @note    All functions implementing the ability to place ships on the game board
*/

#include "avr/system.h"
#include "navswitch.h"
#include "button.h"
#include "include/ShipPlacement.h"
#include "include/Board.h"
#include "include/Ship.h"

/**
 * @brief Moves the start position of a ship by a given amount
 *
 * @param ship A pointer to the ship to be shifted
 * @param delta_row The number of rows to shift by (can be negative)
 * @param delta_col The number of columns to shift by (can be negative)
 */
void shift_ship(Ship_t* ship, int8_t delta_row, int8_t delta_col)
{
    Pos_t ship_tail = ship_end_pos(*ship);

    int8_t new_row = ship_tail.row + delta_row;
    if (new_row < 0 || new_row > BOARD_HEIGHT - 1) {
        return;
    }

    int8_t new_col = ship_tail.col + delta_col;
    if (new_col < 0 || new_col > BOARD_WIDTH - 1) {
        return;
    }

    new_row = ship->start_pos.row + delta_row;
    if (new_row < 0 || new_row > BOARD_HEIGHT - 1) {
        return;
    }

    new_col = ship->start_pos.col + delta_col;
    if (new_col < 0 || new_col > BOARD_WIDTH - 1) {
        return;
    }

    // Only change the ship's position if shift
    // doesn't move it off of the matrix
    ship->start_pos = (Pos_t){.row = new_row, .col = new_col};
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

        if (ship.placed_horizontally) {// Ship exists in one row, spanning multiple columns
            current_pos = (Pos_t) {ship.start_pos.row, ship.start_pos.col + i};
        } else {// Ship exists in one column, spanning multiple rows
            current_pos = (Pos_t) {ship.start_pos.row + i, ship.start_pos.col};
        }

        // Placement is invalid if position is already occupied
        if (board_get(&state_board, current_pos) != Empty) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Sets the position of `ship` into the cells of the game board
 *
 * DO NOT CALL THIS FUNCTION WITHOUT GHOST MODE
 * IF THE SHIP'S POSITION HAS NOT BEEN VALIDATED
 *
 * @param ship The ship to be placed on the board
 */
static void set_ship(Ship_t ship, bool ghost_mode)
{
    Pos_t current_pos;
    for (uint8_t i = 0; i < ship.length; i++) {

        if (ship.placed_horizontally) { // Ship exists in one row, spanning multiple columns
            current_pos = (Pos_t) {ship.start_pos.row, ship.start_pos.col + i};
        } else { // Ship exists in one column, spanning multiple rows
            current_pos = (Pos_t) {ship.start_pos.row + i, ship.start_pos.col};
        }

        if (!ghost_mode) {
            board_set(&state_board, current_pos, Ship);
        } else {
            board_set(&ghost_board, current_pos, Ship);
        }
    }
}

/**
 * @brief Controls the placing of an individual ship onto the board
 *
 * This function must be called repeatedly until all ships have been placed
 *
 * @param ship The ship to be placed on the board
 */
static bool place_ship(Ship_t* ship)
{
    // Confirm ship placement on navswitch push
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        if (placement_is_valid(*ship)) {
            set_ship(*ship, false);
            return true;
        }
    } else if (button_push_event_p(BUTTON1)) {
        // Rotate ship placement axis on Button1 press
        ship->placed_horizontally = !ship->placed_horizontally;

        Pos_t tail = ship_end_pos(*ship);

        // Force the ship to stay on the board
        if (tail.col >= BOARD_WIDTH) {
            ship->start_pos.col -= tail.col - (BOARD_WIDTH - 1);
        } else if (tail.row >= BOARD_HEIGHT) {
            ship->start_pos.row -= tail.row - (BOARD_HEIGHT - 1);
        }
    }

    // Read navswitch values
    int8_t delta_row = -(navswitch_push_event_p(NAVSWITCH_NORTH) - navswitch_push_event_p(NAVSWITCH_SOUTH));
    int8_t delta_col =   navswitch_push_event_p(NAVSWITCH_EAST)  - navswitch_push_event_p(NAVSWITCH_WEST);

    //Ensure the ship is actually on the grid
    shift_ship(ship, delta_row, delta_col);

    // Remove the previous placement of the ship and replace it with the new one
    board_wipe(&ghost_board);
    set_ship(*ship, true);

    return false;
}

/**
 * @brief Controls the placement of all `NUM_SHIPS` ships
 *
 * @param reset true to reset ship counter for new game
 * @return `true` if all ships have been placed, otherwise `false`
 */
bool place_ships(bool reset)
{
    static uint8_t ships_placed = 0;
    if (reset) {
        ships_placed = 0;
    } else {
        // Ship counter is incremented if place_ship returns true
        ships_placed += place_ship(&(ships[ships_placed]));
    }

    return ships_placed == NUM_SHIPS;
}