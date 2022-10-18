/** @file    TurnEvents.c
 *  @authors Harrison Parkes
 *  @date    13th of October 2022
 *  @brief   Events that occur on every turn of the game
 *  @note    Functions implementing core events that happen in every turn of battleships
*/

#include "../drivers/navswitch.h"
#include "../drivers/led.h"
#include "TurnEvents.h"
#include "Board.h"
#include "Ship.h"
#include "game.h"

static int num_hits = 0;

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
    Cell_State_t board_state = board_get(&state_board, *shot_pos);
    
    // Conform shot position when navswitch is pushed
    if (navswitch_push_event_p(NAVSWITCH_PUSH) && !(board_state == Hit || board_state == Miss)) {
        return true;
    }

    // Read navswitch values
    int8_t shot_row = shot_pos->row - (navswitch_push_event_p(NAVSWITCH_NORTH) - navswitch_push_event_p(NAVSWITCH_SOUTH));
    int8_t shot_col = shot_pos->col + navswitch_push_event_p(NAVSWITCH_EAST) - navswitch_push_event_p(NAVSWITCH_WEST);

    *shot_pos = move_to_board(shot_row, shot_col);

    // Remove previous cross-hair and place new one
    board_wipe(&ghost_board);
    board_set(&ghost_board, *shot_pos, HIGH);

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
    Cell_State_t board_state = board_get(&oppositions_board, pos);
    if (board_state == Ship) {
        num_hits += 1;
        board_set(&state_board, pos, Hit);
        led_set(BLUE_LED, HIGH);
    } else if (board_state == Empty) {
        board_set(&state_board, pos, Miss);
    }
}

/**
 * @brief Checks to see if the game has been won on this board
 *
 * @return `true` if game has been won, otherwise `false`
 */
bool all_ships_sunk(void)
{
    return num_hits == NUM_SHIP_CELLS;
}

/**
 * @brief Sets number of ships hit to 0
 */
void reset_shot_count()
{
    num_hits = 0;
}