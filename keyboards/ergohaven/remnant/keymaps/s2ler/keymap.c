#include QMK_KEYBOARD_H
#include "s2ler.h"
#include "layers.h"
#include "key_codes.h"
#include "features/select_word.h"
#include <process_combo.h>
#include "tap_dance/tap_dance.h"

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
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
    [HOME_LAYER] = LAYOUT(
        LGUI(KC_TAB), XXXXXXX, XXXXXXX, XXXXXXX, ACT_SELECTION_SCREENSHOT, TD(TD_SAFE_BOOT),          TD(TD_SAFE_BOOT), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ACT_SWITCH_WINDOWS,

        KC_TAB,  MEH_T(KC_Q),  KC_W, KC_E,  KC_R, KC_T,                                                KC_Y, KC_U, KC_I, KC_O, KC_P, OSL(ACTION_LAYER),
        KC_LCTL, LSFT_T(KC_A), C_S_T(KC_S), KC_D, KC_F, KC_G,                                          KC_H, KC_J, KC_K, KC_L, KC_RSFT, LSFT(KC_RSFT),
        XXXXXXX, LSA_T(KC_Z),  KC_X, KC_C,  KC_V, KC_B,                                                KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,

        KC_LALT, KC_DELETE,                                                                            KC_BSPC, KC_ESCAPE,
        QK_LGUI, TL_LOWR, MO(APP_LAYER),                                                  KC_ENT, TL_UPPR, KC_SPACE
    ),

    [SYMBAL_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),           LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), LSFT(KC_EQUAL),
        _______, KC_GRAVE, KC_QUOTE, KC_SCLN, LSFT(KC_LBRC), KC_LBRC,                  KC_RBRC, LSFT(KC_RBRC), KC_MINUS, KC_EQUAL, LSFT(KC_SCLN), LSFT(KC_QUOTE),
        _______, LSFT(KC_GRAVE), XXXXXXX, MO(NUM_LAYER), LSFT(KC_9), RSFT(KC_LSFT),    LSFT(KC_MINUS), LSFT(KC_0), LSFT(KC_COMMA), LSFT(KC_DOT), LSFT(KC_SLASH), LSFT(KC_BSLS),
                           _______, _______,                                                  _______, _______,
                                         _______, _______, _______,      _______, _______,  _______
    
    ),

    [NAV_LAYER] = LAYOUT(
        QK_REPEAT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, REINDENT, MOVE_LINE_DOWN, MOVE_LINE_UP, XXXXXXX,                KC_PGDN, LINE_START, LINE_END, KC_PGUP, SELECT_WORD,  SHOW_DOCUMENTATION,
        _______, KC_LSFT, FIND_CALLERS, NAV_BACK, NAV_FORWARD, TO_DEFINITION,          KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, NEXT_APP_WINDOW,  FILE_STRUCTURE,
        _______, LSA_T(KC_ENTER), REVEAL_IN, XXXXXXX, DELETE_LINE, NEXT_PLACEHOLDER,      PREV_TAB, PREV_WINDOW_TAB, NEXT_WINDOW_TAB, NEXT_TAB, XXXXXXX,  XCODE_ACTION_POPUP,
                           _______, _______,                                              _______, _______,
                                             _______, _______, _______,           _______, _______, _______
    ),
    
    [MOUSE_LAYER] = LAYOUT(
        RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, DM_RSTP, LGUI(KC_BTN1), KC_BTN3, KC_MUTE,           KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, XXXXXXX, XXXXXXX,
        _______, DM_PLY1, DM_REC1, KC_BTN1, KC_BTN2, KC_VOLU,                 KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
        _______, DM_PLY2, DM_REC2, XXXXXXX, MV_TO_PREV_WINDOW, KC_VOLD,       _______, MV_TO_NEXT_WINDOW, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______,                                                     ZOOM_OUT, ZOOM_IN,
                                         _______, _______, _______,       _______, _______,  _______                          
    ),
    [APP_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, APP_GIT_GUI, APP_SLACK, XXXXXXX, ACT_SNIPPETS, ACT_TODO,     XXXXXXX, APP_TERMINAL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, APP_PYCHARM, APP_BROWSER, XXXXXXX, ACT_SIRI, ACT_DICTATION,  ACT_PREV_DESKTOP, ACT_APPLICATION_WINDOWS, ACT_MISSION_CONTROL, ACT_NEXT_DESKTOP, XXXXXXX, XXXXXXX,
        XXXXXXX, APP_MAIL, APP_XCODE, XXXXXXX, XXXXXXX, ACT_CLIPBOARD,        ACT_NEW_NOTE, ACT_MAXIMIZE_WINDOW, ACT_SHOW_NOTIFICATIONS, ACT_SHOW_DESKTOP, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,                                                     _______, _______,
        _______, _______, _______,                                            _______, ACT_MENU_BAR, ACT_SHORTCAT
    ),
    [ACTION_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, ACT_RAYCAST_IMPROVE_WRITING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, ACT_RAYCAST_AI, XXXXXXX, XXXXXXX, ACT_SEARCH_FILES, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, ACT_RAYCAST_FIX_SPELLING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,                                                           XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                                                  XXXXXXX, XXXXXXX,  XXXXXXX
    ),
    [NUM_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,     KC_KP_7, KC_KP_8, KC_KP_9, KC_COMMA, KC_KP_PLUS,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_KP_COMMA, KC_KP_4, KC_KP_5, KC_KP_6, KC_0,     KC_KP_EQUAL,
        _______, XXXXXXX, KC_LCTL, XXXXXXX, KC_LGUI, XXXXXXX,                       KC_DOT,      KC_KP_1, KC_KP_2, KC_KP_3, KC_SLASH, XXXXXXX,
        XXXXXXX, XXXXXXX,                                                           _______, _______,
        XXXXXXX, XXXXXXX, _______,                                                  _______, XXXXXXX,  XXXXXXX
    ),
};

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