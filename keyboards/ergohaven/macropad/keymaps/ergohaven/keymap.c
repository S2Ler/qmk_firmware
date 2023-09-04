#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    //debug_matrix=true;
    debug_keyboard=true;

    //debug_mouse=true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                        KC_MUTE,
      KC_7, KC_8,       KC_9,
      KC_4, KC_5,       KC_6,
      KC_1, KC_2,       KC_3,
      KC_0, KC_DOT, KC_COMMA
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
};
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    debug_msg("OLED: init user\n");
	return OLED_ROTATION_90;
}

bool oled_task_user(void) {
    debug_msg("OLED: task user\n");
    oled_write_ln_P(PSTR("S2Ler\n"), false);
  return true;
}

#endif
