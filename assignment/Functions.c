//
// Created by Harry on 2/10/22.
//

#include "../drivers/navswitch.h"
#include "GhostBoard.h"
#include "Functions.h"
#include "Board.h"
#include "Ship.h"

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

        if (ship.placed_horizontally)
            current_pos = (Pos_t){ship.start_pos.row, ship.start_pos.col + i};
        else
            current_pos = (Pos_t){ship.start_pos.row + i, ship.start_pos.col};

        if (board_get(current_pos) != Empty) {
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

        if (ship.placed_horizontally)
            current_pos = (Pos_t){ship.start_pos.row , ship.start_pos.col + i};
        else
            current_pos = (Pos_t){ship.start_pos.row + i, ship.start_pos.col};

        if (!ghost_mode) {
            board_set(current_pos, Ship);
        } else {
            ghost_set(current_pos, 1);
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
    }

//    // Read navswitch values
    int8_t ship_delta_row = -(navswitch_push_event_p(NAVSWITCH_NORTH) - navswitch_push_event_p(NAVSWITCH_SOUTH));
    int8_t ship_delta_col =   navswitch_push_event_p(NAVSWITCH_EAST)  - navswitch_push_event_p(NAVSWITCH_WEST);

    //Ensure the ship is actually on the grid
    shift_ship(ship, ship_delta_row, ship_delta_col);

    ghost_wipe();
    set_ship(*ship, true);

    return false;
}

/**
 * @brief Controls the placement of all `NUM_SHIPS` ships
 *
 * @return `true` if all ships have been placed, otherwise `false`
 */
bool place_ships(void)
{
    static uint8_t ships_placed = 0;

    // Ship counter is incremented if place_ship returns true
    ships_placed += place_ship(&(ships[ships_placed]));

    return ships_placed == NUM_SHIPS;
}

/**
 * @brief Allows player to choose where to fire their missile
 *
 * Croshair begins at top left corner, and is moved with the navswitch
 * pressing the navswitch down confirms the position to fire at
 *
 * @return The position selected by the user
 */
bool take_aim(Pos_t* shot_pos)
{
    // While navswitch isn't pushed in
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        return true;
    }

    // Read navswitch values
    int8_t shot_row = shot_pos->row - (navswitch_push_event_p(NAVSWITCH_NORTH) - navswitch_push_event_p(NAVSWITCH_SOUTH));
    int8_t shot_col = shot_pos->col + navswitch_push_event_p(NAVSWITCH_EAST) - navswitch_push_event_p(NAVSWITCH_WEST);

    *shot_pos = move_to_board(shot_row, shot_col);


    ghost_wipe();
    ghost_set(*shot_pos, true);

    return false;
}


/**
 * @brief "Fires" a "missile" at the oppositions game board
 *
 * Gets the current state of the oppositions board at the given position
 * and updates the state accordingly
 *
 * @param pos The position on the opposition's board to fire at
 */
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