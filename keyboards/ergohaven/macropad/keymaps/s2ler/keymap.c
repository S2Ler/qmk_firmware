#include QMK_KEYBOARD_H
#include "layers.h"
#include "tap_dance/tap_dance.h"

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;

    //debug_mouse=true;
}


enum custom_keycodes {
    LAYER_NEXT = SAFE_RANGE,
    LAYER_PREV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MEDIA_LAYER] = LAYOUT(
        KC_MUTE,
        KC_BRID, KC_CPNL, KC_BRIU,
        KC_MYCM, KC_WSCH, KC_MAIL,
        KC_MPRV, KC_MPLY, KC_MNXT,
        TD_SAFE_BOOT, LAYER_PREV, LAYER_NEXT
        ),
    [XCODE_LAYER] = LAYOUT(
        KC_MUTE,
        KC_7, KC_8, KC_9,
        KC_4, KC_5, KC_6,
        KC_1, KC_2, KC_3,
        KC_0, _______, _______
        ),
    [F_LAYER] = LAYOUT(
        QK_BOOTLOADER,
        KC_F7, KC_F8, KC_F9,
        KC_F4, KC_F5, KC_F6,
        KC_F1, KC_F2, KC_F3,
        KC_F10, _______, _______
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_PREV:
            // Our logic will happen on presses, nothing is done on releases
            if (!record->event.pressed) {
                // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
                return false;
            }

            uint8_t this_layer = get_highest_layer(layer_state);

        // Check if we are within the range, if not quit
            if (this_layer > LAYER_CYCLE_END || this_layer < LAYER_CYCLE_START) {
                return false;
            }

            uint8_t prev_layer = this_layer - 1;
            if (prev_layer > LAYER_CYCLE_END) {
                prev_layer = LAYER_CYCLE_START;
            }
            layer_move(prev_layer);
            return false;
        case LAYER_NEXT:
            // Our logic will happen on presses, nothing is done on releases
            if (!record->event.pressed) {
                // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
                return false;
            }

            uint8_t current_layer = get_highest_layer(layer_state);

        // Check if we are within the range, if not quit
            if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
                return false;
            }

            uint8_t next_layer = current_layer + 1;
            if (next_layer > LAYER_CYCLE_END) {
                next_layer = LAYER_CYCLE_START;
            }
            layer_move(next_layer);
            return false;
        default:
            break;
    }

    return true;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MEDIA_LAYER] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [XCODE_LAYER] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    [F_LAYER] = {ENCODER_CCW_CW(KC_F11, KC_F12)},
};
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_task_user(void) {
    // Using current layer display its name on the OLED screen in first row
    oled_write_P(PSTR("L: "), false);
    switch (get_highest_layer(layer_state)) {
        case MEDIA_LAYER:
            oled_write_ln_P(PSTR("Media"), false);
            oled_write_ln_P(PSTR("Mu VU VD"), false);
            oled_write_ln_P(PSTR("BU . BD"), false);
            oled_write_ln_P(PSTR(". . ."), false);
            oled_write_ln_P(PSTR("Pre Pau Ne"), false);
            oled_write_ln_P(PSTR(". LaP LaN"), false);
            break;
        case XCODE_LAYER:
            oled_write_ln_P(PSTR("Xcode"), false);
            oled_write_ln_P(PSTR("Mu PU PD"), false);
            oled_write_ln_P(PSTR("7 8 9"), false);
            oled_write_ln_P(PSTR("4 5 6"), false);
            oled_write_ln_P(PSTR("1 2 3"), false);
            oled_write_ln_P(PSTR("0 LaP LaN"), false);
            break;
        case F_LAYER:
            oled_write_ln_P(PSTR("F Layer"), false);
            oled_write_ln_P(PSTR("R 11 12"), false);
            oled_write_ln_P(PSTR("7 8 9"), false);
            oled_write_ln_P(PSTR("4 5 6"), false);
            oled_write_ln_P(PSTR("1 2 3"), false);
            oled_write_ln_P(PSTR("10 LaP LaN"), false);
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }

    return true;
}

#endif
