#include "tap_dance.h"
#include "layers.h"
#include <quantum.h>
#include <process_tap_dance.h>

td_state_t current_dance_state(tap_dance_state_t *state);

void td_lgui_finished(tap_dance_state_t *state, void *user_data);
void td_lgui_reset(tap_dance_state_t *state, void *user_data);

void td_safe_boot_each_tap(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lgui_finished, td_lgui_reset),

    [TD_SAFE_BOOT] = ACTION_TAP_DANCE_FN_ADVANCED(td_safe_boot_each_tap, NULL, NULL),
};

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = 1,
    .state = TD_NONE
};

// MARK: Implementations

void td_lgui_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = current_dance_state(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(KC_LGUI)); break;
        case TD_DOUBLE_TAP: register_code16(LGUI(KC_TAB)); break;
        case TD_DOUBLE_HOLD: register_code16(MO(NUM_LAYER)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
//        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}

void td_lgui_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(KC_LGUI)); break;
        case TD_DOUBLE_TAP: unregister_code16(LGUI(KC_TAB)); break;
        case TD_DOUBLE_HOLD: unregister_code16(MO(NUM_LAYER)); break;
//        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void td_safe_boot_each_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        reset_keyboard();
    }
}

// MARK: Private

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
#include <print.h>

td_state_t current_dance_state(tap_dance_state_t *state) {
    if (state->count == 1) {
        println("state.count 1");
        if (state->interrupted) {
            println("state.interrupted");
            print("state.interrupted_keycode: ");
            print_val_dec(state->interrupting_keycode);
            println("");
            if (state->pressed) {
                println("state.pressed");
                // If the key is interrupted, and still pressed, then you want to send a 'SINGLE_HOLD'
                return TD_SINGLE_HOLD;
            }
            else {
                println("state.not_pressed");
                // If the key is interrupted, and not pressed, then you want to send a 'SINGLE_TAP'
                return TD_SINGLE_TAP;
            }
        }
        else {
            println("state.not_interrupted");
            if (state->pressed) {
                return TD_SINGLE_HOLD;
            }
            else {
                return TD_SINGLE_TAP;
            }
        }
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}
