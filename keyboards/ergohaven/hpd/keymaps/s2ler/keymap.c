#include QMK_KEYBOARD_H
#include "s2ler.h"
#include "layers.h"
#include "features/select_word.h"
#include <process_combo.h>
#include <process_tap_dance.h>
#include "tap_dance/tap_dance.h"
#include <raw_hid.h>
#include <leader.h>

#define LANG_COUNT 2

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
//    debug_matrix=true;
//    debug_keyboard=true;
//    debug_mouse=true;
}

// MARK: - Combos

enum combo_events {
    NEW_LINE_COMBO,
    NEW_LINE_ABOVE_COMBO,
};

const uint16_t PROGMEM new_line_combo[] = {KC_F, KC_ENTER, COMBO_END};
const uint16_t PROGMEM new_line_above_combo[] = {KC_D, KC_ENTER, COMBO_END};

void tap_new_line(void) {
    tap_code16(LGUI(KC_RIGHT));
    tap_code16(KC_ENTER);
}

void tap_new_line_above(void) {
    tap_code16(LGUI(KC_LEFT));
    tap_code16(KC_ENTER);
    tap_code16(KC_UP);
}

combo_t key_combos[] = {
    [NEW_LINE_COMBO] = COMBO_ACTION(new_line_combo),
    [NEW_LINE_ABOVE_COMBO] = COMBO_ACTION(new_line_above_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case NEW_LINE_COMBO:
            if (pressed) {
                tap_new_line();
            }
            break;
        case NEW_LINE_ABOVE_COMBO:
            if (pressed) {
                tap_new_line_above();
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
        LGUI(KC_TAB), XXXXXXX, SH_RAW_PASTER, REDO, ACT_SELECTION_SCREENSHOT, TD(TD_SAFE_BOOT),     TD(TD_SAFE_BOOT), LANG_SWITCH, XXXXXXX, XXXXXXX, XXXXXXX, ACT_SWITCH_WINDOWS,

        KC_TAB,  KC_Q,  KC_W, KC_E,  KC_R, KC_T,                                                    KC_Y, KC_U, KC_I, KC_O, KC_P, OSL(ACTION_LAYER),
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,                                                      KC_H, KC_J, KC_K, KC_L, LSFT_T(KC_ESC), LSFT(KC_RSFT),
        KC_LSFT, KC_Z,  KC_X, KC_C,  KC_V, KC_B,                                                    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
        KC_LALT, KC_DELETE, QK_LGUI, TL_LOWR, MO(APP_LAYER), XXXXXXX,                               XXXXXXX, KC_ENT, TL_UPPR, KC_SPACE, KC_BSPC, QK_LEAD

    ),

    [SYMBAL_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                  LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), LSFT(KC_EQUAL),
        _______, KC_GRAVE, LSFT(KC_QUOTE), KC_SCLN, LSFT(KC_LBRC), KC_LBRC,                   KC_RBRC, LSFT(KC_RBRC), KC_MINUS, KC_EQUAL, LSFT(KC_SCLN), XXXXXXX,
        _______, LSFT(KC_GRAVE), KC_QUOTE, MO(NUM_LAYER), LSFT(KC_9), XXXXXXX,                LSFT(KC_MINUS), LSFT(KC_0), LSFT(KC_COMMA), LSFT(KC_DOT), LSFT(KC_SLASH), LSFT(KC_BSLS),
        _______, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______,  _______, _______
    ),

    [NAV_LAYER] = LAYOUT(
        QK_REPEAT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, RS_CENTER_HALF, XXXXXXX,                       RS_LEFT_HALF, RS_BOTTOM_HALF, RS_TOP_HALF, RS_RIGHT_HALF, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, REINDENT, MOVE_LINE_DOWN, MOVE_LINE_UP, XXXXXXX,                KC_PGDN, LINE_START, LINE_END, KC_PGUP, SELECT_WORD,  SHOW_DOCUMENTATION,
        _______, KC_LSFT, FIND_CALLERS, NAV_BACK, NAV_FORWARD, TO_DEFINITION,          KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, NEXT_APP_WINDOW,  FILE_STRUCTURE,
        _______, LSA_T(KC_ENTER), REVEAL_IN, SH_RENAME, DELETE_LINE, NEXT_PLACEHOLDER,      PREV_TAB, PREV_WINDOW_TAB, NEXT_WINDOW_TAB, NEXT_TAB, XXXXXXX,  XCODE_ACTION_POPUP,
        _______, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______,  _______, _______
    ),

    [MOUSE_LAYER] = LAYOUT(
        RGB_TOG, QK_MAGIC_SWAP_CTL_GUI, QK_MAGIC_UNSWAP_CTL_GUI, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, DM_RSTP, LGUI(KC_BTN1), KC_BTN3, KC_MUTE,           KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, XXXXXXX, XXXXXXX,
        _______, DM_PLY1, DM_REC1, KC_BTN1, KC_BTN2, KC_VOLU,                 KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
        _______, DM_PLY2, DM_REC2, XXXXXXX, MV_TO_PREV_WINDOW, KC_VOLD,       _______, MV_TO_NEXT_WINDOW, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______,  _______, _______, _______, _______,                _______, ZOOM_IN, ZOOM_OUT, _______, _______,  _______
    ),
    [APP_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, SAF_PERSONAL, SAF_YANDEX, SAF_YANDEX_APP_METRICA, SAF_ALIKE, XXXXXXX,
        XXXXXXX, APP_GIT_GUI, APP_SLACK, XXXXXXX, ACT_SNIPPETS, ACT_TODO,     XXXXXXX, APP_TERMINAL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, APP_PYCHARM, APP_BROWSER, XXXXXXX, ACT_SIRI, ACT_DICTATION,  ACT_PREV_DESKTOP, ACT_APPLICATION_WINDOWS, ACT_MISSION_CONTROL, ACT_NEXT_DESKTOP, XXXXXXX, XXXXXXX,
        XXXXXXX, APP_MAIL, APP_XCODE, XXXXXXX, XXXXXXX, ACT_CLIPBOARD,        ACT_NEW_NOTE, ACT_MAXIMIZE_WINDOW, ACT_SHOW_NOTIFICATIONS, ACT_SHOW_DESKTOP, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, _______, _______, _______, _______,                 _______, _______, _______, ACT_MENU_BAR, ACT_SHORTCAT, _______

    ),
    [ACTION_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, ACT_RAYCAST_IMPROVE_WRITING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, ACT_RAYCAST_AI, XXXXXXX, XXXXXXX, ACT_SEARCH_FILES, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, ACT_RAYCAST_FIX_SPELLING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX
    ),
    [NUM_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,     KC_7, KC_8, KC_9, KC_COMMA, KC_KP_PLUS,
        _______, MO(F_LAYER), XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,                   KC_KP_COMMA, KC_4, KC_5, KC_6, KC_0,     KC_KP_EQUAL,
        _______, KC_LSFT, KC_LCTL, XXXXXXX, KC_LGUI, XXXXXXX,                       KC_DOT, KC_1, KC_2, KC_3, KC_SLASH, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,                       _______, _______, _______, XXXXXXX,  XXXXXXX, _______
    ),
    [F_LAYER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_F7, KC_F8, KC_F9, KC_F11, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,                       XXXXXXX, KC_F4, KC_F5, KC_F6, KC_F10,     XXXXXXX,
        _______, _______, _______, XXXXXXX, _______, XXXXXXX,                       XXXXXXX, KC_F1, KC_F2, KC_F3, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,                       XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX
    ),
};

bool process_record_user(const uint16_t keycode, keyrecord_t *record) {
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

uint8_t get_language_idx() {
    return 1;
}

void set_language_idx(uint8_t lang_idx) {
    //
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    print("#raw_hid_receive#\n");
    // 1 byte = report id
    // 2 byte = cmd

    if (length < 2) {
        print("raw_hid_receive: Unsupported report");
        return;
    }

    uint8_t report_id = data[0];
    uint8_t cmd_id = data[1];

    if (report_id == 1) {
        switch (cmd_id) {
            case 1: {
                uint8_t lang_idx = get_language_idx();
                print("raw_hid_receive: Get language idx: ");
                debug_hex(lang_idx);
                print("\n");
                uint8_t response[] = {1, 1, lang_idx};
                raw_hid_send(response, sizeof(response));
                break;
            }
            case 2: {
                uint8_t layer_idx = get_highest_layer(layer_state);
                print("raw_hid_receive: Get active layer idx: ");
                debug_hex(layer_idx);
                print("\n");
                uint8_t response[] = {1, 2, layer_idx};
                raw_hid_send(response, sizeof(response));
                break;
            }
            default:
                print("raw_hid_receive: Unsupported cmd");
                break;
        }
    } else if (report_id == 2) {
        switch (cmd_id) {
            case 1: {
                if (length < 3) {
                    print("raw_hid_receive: Set language error: invalid length");
                    uint8_t response[] = {3, 1, 1};
                    raw_hid_send(response, sizeof(response));
                    return;
                }

                uint8_t lang_idx = data[2];
                if (lang_idx >= LANG_COUNT) {
                    print("raw_hid_receive: Set language error: invalid lang_idx");
                    uint8_t response[] = {3, 1, 2};
                    raw_hid_send(response, sizeof(response));
                    return;
                }

                set_language_idx(lang_idx);
                print("raw_hid_receive: Set language idx: ");
                debug_hex(lang_idx);
                print("\n");
                uint8_t response[] = {2, 1, lang_idx};
                raw_hid_send(response, sizeof(response));
                break;
            }
            case 2: {
                if (length < 3) {
                    print("raw_hid_receive: Set active layer error: invalid length");
                    uint8_t response[] = {3, 2, 1};
                    raw_hid_send(response, sizeof(response));
                    return;
                }

                uint8_t layer_idx = data[2];
                if (layer_idx >= LAYERS_COUNT) {
                    print("raw_hid_receive: Set active layer error: invalid layer_idx");
                    uint8_t response[] = {3, 2, 2};
                    raw_hid_send(response, sizeof(response));
                    return;
                }

                layer_move(layer_idx);
                print("raw_hid_receive: Set active layer idx: ");
                debug_hex(layer_idx);
                print("\n");
                uint8_t response[] = {2, 2, layer_idx};
                raw_hid_send(response, sizeof(response));
                break;
            }
            default: {
                uint8_t response[] = {3, 255, 255};
                raw_hid_send(response, sizeof(response));
                print("raw_hid_receive: Unsupported cmd");
            }
                break;
        }
    } else {
        uint8_t response[] = {3, 255, 255};
        raw_hid_send(response, sizeof(response));
        print("raw_hid_receive: Unsupported report");
    }

    for (int i = 0; i < length; i++) {
        debug_hex(data[i]);
        print(" ");
    }

    print("\n");
}

// MARK: Leader key

void leader_start_user(void) {

}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        tap_new_line();
    }
    else if (leader_sequence_one_key(KC_D)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        tap_new_line_above();
    }
    else if (leader_sequence_two_keys(KC_G, KC_A)) {
        send_string("git add -p && git commit --amend --no-edit && git push --force");
    }
    else if (leader_sequence_three_keys(KC_G, KC_H, KC_P)) {
        send_string("gh-pr-then-open");
    }
    else if (leader_sequence_one_key(KC_O)) {
        tap_code16(QK_LSFT | QK_LGUI | KC_O);
    }
}