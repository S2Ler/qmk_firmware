//
// Created by Alike on 20.08.23.
//

#pragma once
#include "stdint.h"

enum {
    TD_LGUI,
    TD_SAFE_BOOT
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    uint8_t is_press_action;
    td_state_t state;
} td_tap_t;

