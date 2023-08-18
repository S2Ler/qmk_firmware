#include QMK_KEYBOARD_H
#include "s2ler.h"
#include "layers.h"
#include "key_codes.h"
#include <process_combo.h>

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
                tap_code16(LCTL(KC_I));
            }
            break;
        case NEW_LINE_ABOVE_COMBO:
            if (pressed) {
                tap_code16(LGUI(KC_LEFT));
                tap_code16(KC_ENTER);
                tap_code16(KC_UP);
                tap_code16(LCTL(KC_I));
            }
            break;
        default:
            break;
    }
}

// MARK: - Tap Dance
//tap_dance_action_t tap_dance_actions[] = {};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HOME_LAYER] = LAYOUT(
        LGUI(KC_TAB), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LSFT(KC_F13),
        KC_TAB,  MEH_T(KC_Q), KC_W, KC_E, KC_R, KC_T,                       KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL,
        KC_LCTL,  LSFT_T(KC_A), C_S_T(KC_S), KC_D, KC_F, KC_G,              KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        XXXXXXX, LSA_T(KC_Z), KC_X, KC_C, KC_V, KC_B,                       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
        KC_LALT, KC_DELETE,                                                 KC_LBRC, KC_RBRC,
        KC_LGUI, MO(SYMBAL_LAYER), MO(APP_LAYER),                           KC_ENT, MO(NAV_LAYER), KC_SPACE
    ),

    [SYMBAL_LAYER] = LAYOUT(
    
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,                 KC_F7,   KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        QK_BOOT, _______, KC_HOME, KC_UP,   KC_END,   KC_INS,                KC_PGUP, KC_7,  KC_8,  KC_9,   _______, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT,                KC_PGDN, KC_4,  KC_5,  KC_6,   _______, _______,
        _______, _______, _______, KC_CAPS, _______,  KC_DEL,                KC_PSCR, KC_1,  KC_2,  KC_3,   _______, _______,
                           _______, _______,                                                  KC_0, _______,
                                         _______, _______, _______,      _______, MO(MOUSE_LAYER),  _______
    
    ),

    [NAV_LAYER] = LAYOUT(
        _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,             _______, _______, KC_CIRC, _______, _______,  QK_BOOT,
        _______, _______, KC_LT,   KC_EQL,  KC_GT,   KC_GRV,              _______, KC_LBRC, KC_UNDS, KC_RBRC, _______,  _______,
        _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,             KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM,  _______,
        _______, _______, KC_ASTR, KC_COLN, KC_SLSH, _______,             _______, KC_PIPE, KC_TILD, KC_AMPR, _______,  _______,
                           _______, _______,                                                 _______, _______,
                                             _______, MO(MOUSE_LAYER), _______,   _______, _______, _______
    ),
    
    [MOUSE_LAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, DM_PLY1, DM_REC1,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                 _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, CG_TOGG,                 _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
                          _______, _______,                                                     _______, _______,                  
                                         _______, _______, _______,       _______, _______,  _______                          
    ),
    [APP_LAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, DM_PLY1, DM_REC1,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                 _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, CG_TOGG,                 _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
        _______, _______,                                                     _______, _______,
        _______, _______, _______,       _______, _______,  _______
    ),
    [ACTION_LAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, DM_PLY1, DM_REC1,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                 _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, CG_TOGG,                 _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
        _______, _______,                                                     _______, _______,
        _______, _______, _______,       _______, _______,  _______
    ),
    [NUM_LAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, DM_PLY1, DM_REC1,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                 _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, CG_TOGG,                 _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
        _______, _______,                                                     _______, _______,
        _______, _______, _______,       _______, _______,  _______
    ),
};

/* /1* change led based on layers *1/ */
/* void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) { */
/*     HSV hsv = {0, 0, RGB_MATRIX_MAXIMUM_BRIGHTNESS}; */

/*     if (hsv.v > rgb_matrix_get_val()) { */
/*         hsv.v = rgb_matrix_get_val(); */
/*     } */
/*     RGB rgb = hsv_to_rgb(hsv); */

/*     if (get_highest_layer(layer_state) > 0) { */
/*         uint8_t layer = get_highest_layer(layer_state); */

/*         for (uint8_t row = 0; row < MATRIX_ROWS; ++row) { */
/*             for (uint8_t col = 0; col < MATRIX_COLS; ++col) { */
/*                 uint8_t index = g_led_config.matrix_co[row][col]; */

/*                 if (index >= led_min && index <= led_max && index != NO_LED && */
/*                 keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) { */
/*                     rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b); // last three values are R, G, B */
/*                 } */
/*             } */
/*         } */
/*     } */
/* } */
