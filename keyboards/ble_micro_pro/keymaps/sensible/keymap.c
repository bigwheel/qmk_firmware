/* Copyright 2019 sekigon-gonnoc
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

const key_string_map_t custom_keys_user = {};

// デフォルトのキーマップでこれを使用することはほぼないが、一応残しておく
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{
    KC_D, KC_E, KC_F, KC_A, KC_U, KC_L, KC_T,
        KC_K, KC_E, KC_Y, KC_M, KC_A, KC_P,
        KC_B, KC_Y,
        KC_F, KC_I, KC_R, KC_M, KC_W, KC_A, KC_R, KC_E
    }}
};

uint32_t keymaps_len() {
  return 23;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (process_record_user_bmp(keycode, record) == false)
    return PROCESS_OVERRIDE_BEHAVIOR;

  switch (keycode) {
    case KC_ESCAPE:
      if (record->event.pressed) {
        // TODO: 横着しているので、現在のDEFAULT LAYERを参照してどちらを押すか判定すること
        tap_code(KC_MHEN);
        tap_code(KC_LANG2);
      }
      break;
  }

  return true;
}
