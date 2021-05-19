/* Copyright 2021 k.bigwheel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"
#include <stdbool.h>

#include "./auto_disable_ime.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CUSTOM_KEYCODE_START = BMP_SAFE_RANGE,
};

const key_string_map_t custom_keys_user = {
    .start_kc    = CUSTOM_KEYCODE_START,
    .end_kc      = CUSTOM_KEYCODE_START,
    .key_strings = "\0"
};

// デフォルトのキーマップでこれを使用することはほぼないが、一応残しておく
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{KC_D, KC_E, KC_F, KC_A, KC_U, KC_L, KC_T, KC_K, KC_E, KC_Y, KC_M, KC_A,
      KC_P, KC_B, KC_Y, KC_F, KC_I, KC_R, KC_M, KC_W, KC_A, KC_R, KC_E}}
};

uint32_t keymaps_len() {
  return sizeof(keymaps)/sizeof(uint16_t);
}

#define PROCESS_OVERRIDE_BEHAVIOR (false)
#define PROCESS_USUAL_BEHAVIOR (true)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_user_auto_disable_ime();

    if (process_record_user_bmp(keycode, record) == PROCESS_OVERRIDE_BEHAVIOR)
        return PROCESS_OVERRIDE_BEHAVIOR;

    return PROCESS_USUAL_BEHAVIOR;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    matrix_scan_user_auto_disable_ime();
}

void led_set_user(uint8_t usb_led) {
}
