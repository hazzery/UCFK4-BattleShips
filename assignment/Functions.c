//
// Created by Harry on 2/10/22.
// Edited by Dominic
//

#include "../drivers/avr/ir_uart.h"
#include "../drivers/navswitch.h"
#include "../drivers/button.h"
#include "../drivers/led.h"
#include "../utils/pacer.h"
#include "Functions.h"
#include "Board.h"
#include "Ship.h"

extern bool is_player_one;
static int num_hits = 0;

#define DISPLAY_FREQUENCY 300
#define TANSFER_FREQUENCY 100

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
            board_set(&ghost_board, current_pos, 1);
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
        ship->placed_horizontally = !ship->placed_horizontally;

        Pos_t tail = ship_end_pos(*ship);

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

    board_wipe(&ghost_board);
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


    board_wipe(&ghost_board);
    board_set(&ghost_board, *shot_pos, true);

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
    Cell_State_t board_state = board_get(&state_board, pos);
    if (board_state == Ship) {
        num_hits += 1;
        board_set(&state_board, pos, Hit);
        led_set(LED1, 1);
    } else if (board_state == Empty) {
        board_set(&state_board, pos, Miss);
    }
}

/**
 * @brief player one select and swaps game board information
 * 
 * waits until a player pushes the button and assigns them as player one
 * compresses player board and sends to other player before recieving
 * other players board and vice versa if player 2
 */
void swap_board_data(void)
{
    bool playerSeleceted = false;
    while (!playerSeleceted) {
        button_update();
        if (button_push_event_p(BUTTON1)) {
            ir_uart_putc('1');
            is_player_one = true;
            playerSeleceted = true;
        } else if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == '1') {
                led_set(LED1, 1);
                is_player_one = false;
                playerSeleceted = true;
            }
        }
    }

    uint8_t compressed_board[5];
    compress_board(state_board, compressed_board);

    uint8_t oppositions_compressed_board[5];

    pacer_init(TANSFER_FREQUENCY);
    bool board_recieved = false;

    if (is_player_one) {
        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
            while (!ir_uart_write_ready_p()) continue;
            ir_uart_putc(compressed_board[col]);
            pacer_wait();
        }
        while (!board_recieved) {
            while (!ir_uart_read_ready_p()) continue;
            for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
                oppositions_compressed_board[col] = ir_uart_getc();
                pacer_wait();
            }
            board_recieved = true;
        }
    } else {
        while (!board_recieved) {
            while (!ir_uart_read_ready_p()) continue;
            for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
                oppositions_compressed_board[col] = ir_uart_getc();
                pacer_wait();
            }
            board_recieved = true;
        }
        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
            while (!ir_uart_write_ready_p()) continue;
            ir_uart_putc(compressed_board[col]);
            pacer_wait();
        }

    }

    pacer_init(DISPLAY_FREQUENCY);
    uncompress_board(oppositions_compressed_board, &oppositions_board);
}

/**
 * @brief Checks to see if the game has been won, on this board
 *
 * @return `true` if game has been won, otherwise `false`
 */
bool win_check(void)
{
    return num_hits == NUM_SHIP_CELLS;
}

/**
 * @brief Sends signal to the opposition to tell them the game has been won
 */
void win_signal(void)
{
    while (!ir_uart_write_ready_p()) continue;

    ir_uart_putc('W');
}