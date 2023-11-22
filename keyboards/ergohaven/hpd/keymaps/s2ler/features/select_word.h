#pragma once

#include "quantum.h"

/// Process select word feature.
/// Usage example:
/// ```c
/// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
///    if (!process_select_word(keycode, record, SELECT_WORD)) { return false; }
///    // ... other code
/// }
/// ```
bool process_select_word(uint16_t keycode, keyrecord_t* record,
                         uint16_t sel_keycode);
