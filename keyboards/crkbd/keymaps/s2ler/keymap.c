/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "s2ler.h"
#include "layers.h"
#include "features/select_word.h"
#include <process_combo.h>
#include <process_tap_dance.h>
#include "tap_dance/tap_dance.h"
#include <raw_hid.h>

enum custom_keycodes {
    MACRO_1 = SAFE_RANGE,
};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=false;
    debug_keyboard=true;
    //debug_mouse=true;
}


// MARK: - Combos

enum combo_events {
    NEW_LINE_COMBO,
    NEW_LINE_ABOVE_COMBO,
};

const uint16_t PROGMEM new_line_combo[] = {KC_F, KC_ENTER, COMBO_END};
const uint16_t PROGMEM new_line_above_combo[] = {KC_D, KC_ENTER, COMBO_END};

combo_t key_combos[] = {
    [NEW_LINE_COMBO] = COMBO_ACTION(new_line_combo),
    [NEW_LINE_ABOVE_COMBO] = COMBO_ACTION(new_line_above_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case NEW_LINE_COMBO:
            if (pressed) {
                tap_code16(LGUI(KC_RIGHT));
                tap_code16(KC_ENTER);
            }
            break;
        case NEW_LINE_ABOVE_COMBO:
            if (pressed) {
                tap_code16(LGUI(KC_LEFT));
                tap_code16(KC_ENTER);
                tap_code16(KC_UP);
            }
            break;
        default:
            break;
    }
}

// MARK: - Layout

enum custom_codes {
    SELECT_LINE = SAFE_RANGE,
    DELETE_LINE,
    SELECT_WORD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HOME_LAYER] = LAYOUT_split_3x6_3(
        KC_TAB,    MEH_T(KC_Q),    KC_W,    KC_E,    KC_R,    KC_T,                   KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
        KC_LCTL,    LSFT_T(KC_A),    KC_S,    KC_D,    KC_F,    KC_G,                 KC_H,    KC_J,    KC_K,    KC_L, LSFT_T(KC_ESC), LSFT(KC_RSFT),
        KC_LALT,    LSA_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                  KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_BSLS,
        KC_LGUI, TL_LOWR,  MO(APP_LAYER),                                                   KC_ENT, TL_UPPR, KC_SPACE
        ),

    [SYMBAL_LAYER] = LAYOUT_split_3x6_3(
        _______, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                  LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), LSFT(KC_EQUAL),
        _______, KC_GRAVE, KC_QUOTE, KC_SCLN, LSFT(KC_LBRC), KC_LBRC,                         KC_RBRC, LSFT(KC_RBRC), KC_MINUS, KC_EQUAL, LSFT(KC_SCLN), XXXXXXX,
        _______, LSFT(KC_GRAVE), LSFT(KC_QUOTE), MO(NUM_LAYER), LSFT(KC_9), RSFT(KC_LSFT),    LSFT(KC_MINUS), LSFT(KC_0), LSFT(KC_COMMA), LSFT(KC_DOT), LSFT(KC_SLASH), LSFT(KC_BSLS),
        _______, _______,  _______,     _______, _______, _______
        ),

    [NAV_LAYER] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, REINDENT, MOVE_LINE_DOWN, MOVE_LINE_UP, XXXXXXX,                KC_PGDN, LINE_START, LINE_END, KC_PGUP, SELECT_WORD,  SHOW_DOCUMENTATION,
        _______, KC_LSFT, FIND_CALLERS, NAV_BACK, NAV_FORWARD, TO_DEFINITION,          KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, NEXT_APP_WINDOW,  FILE_STRUCTURE,
        _______, LSA_T(KC_ENTER), REVEAL_IN, XXXXXXX, DELETE_LINE, NEXT_PLACEHOLDER,      PREV_TAB, PREV_WINDOW_TAB, NEXT_WINDOW_TAB, NEXT_TAB, XXXXXXX,  XCODE_ACTION_POPUP,
        _______, _______,  _______,     _______, _______, _______
        ),

    [MOUSE_LAYER] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, DM_RSTP, LGUI(KC_BTN1), KC_BTN3, KC_MUTE,           KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, XXXXXXX, XXXXXXX,
        _______, DM_PLY1, DM_REC1, KC_BTN1, KC_BTN2, KC_VOLU,                 KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
        _______, DM_PLY2, DM_REC2, XXXXXXX, MV_TO_PREV_WINDOW, KC_VOLD,       _______, MV_TO_NEXT_WINDOW, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______,  _______,     _______, _______, _______
        ),
    [APP_LAYER] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
        _______, _______,  _______,     _______, _______, _______
        ),
    [ACTION_LAYER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
        _______, _______,  _______,                                                _______, _______, _______
        ),
    [NUM_LAYER] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,     KC_7, KC_8, KC_9, KC_COMMA, KC_KP_PLUS,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_KP_COMMA, KC_4, KC_5, KC_6, KC_0,     KC_KP_EQUAL,
        _______, KC_LSFT, KC_LCTL, XXXXXXX, KC_LGUI, XXXXXXX,                 KC_DOT,      KC_1, KC_2, KC_3, KC_SLASH, XXXXXXX,
        _______, _______,  _______,                                                 _______, _______, _______
        )
};


#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Home"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Symbal"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case 4:
            oled_write_ln_P(PSTR("App"), false);
            break;
        case 5:
            oled_write_ln_P(PSTR("Action"), false);
            break;
        case 6:
            oled_write_ln_P(PSTR("Number"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}


#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_select_word(keycode, record, SELECT_WORD)) { return false; }

    switch (keycode) {
        case SELECT_LINE:
            if (record->event.pressed) {
                tap_code16(LINE_END);
                tap_code16( SELECT_LINE_START);
                return false;
            }
            break;
        case DELETE_LINE:
            if (record->event.pressed) {
                tap_code16(LINE_START);
                tap_code16( KILL_TO_LINE_END);
                return false;
            }
            break;
        default:
            break;
    }

    return true;
}


// MARK: Raw HID

void raw_hid_receive(uint8_t *data, uint8_t length) {
    print("raw_hid_receive: ");

    for (int i = 0; i < length; i++) {
        debug_hex(data[i]);
        print(" ");
    }

    print("\n");
}