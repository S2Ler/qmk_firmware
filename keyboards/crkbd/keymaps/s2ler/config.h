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

#pragma once

/* Select hand configuration */

#define TAPPING_TERM 200

#define PERMISSIVE_HOLD
// or
//#define HOLD_ON_OTHER_KEY_PRESS

#define COMBO_TERM 50 // TODO: Try defaulting to 200
//#define MK_KINETIC_SPEED // uncomment to enable kinetic scrolling
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 7
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_MAX_SPEED 50
#define MOUSEKEY_TIME_TO_MAX 90
//#define MOUSEKEY_INITIAL_SPEED 150
//#define MOUSEKEY_BASE_SPEED 6000
//#define MOUSEKEY_ACCELERATED_SPEED 2000

#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 50
#define MOUSEKEY_WHEEL_MAX_SPEED 5
#define MOUSEKEY_WHEEL_TIME_TO_MAX 255

//#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 1
//#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 20
//#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 20
//#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8

// TODO: Might be useful
//#define STRICT_LAYER_RELEASE
//#define NO_DEBUG
//#define NO_PRINT


#define MASTER_LEFT
//#define MASTER_RIGHT
//#define EE_HANDS

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 54
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT \
        { 27, 27 }
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP  10
#    define RGBLIGHT_SAT_STEP  17
#    define RGBLIGHT_VAL_STEP  17
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
