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

#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

// アルファベット以外で処理をすれば最初はよいかなと考えていたが
// modifier key, backspaceなど例外が多数あることを考えれば
// 結局自分で定義するのが一旦楽という結論になった。
// qmk firmware側でmodifier keyが配列で定義されていたりするようであれば
// 種別ベースなどで選択するのもありかもしれない。
const uint16_t leave_ime_on_keys[] = {
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
  KC_GRAVE,
  KC_MINUS,
  KC_EQUAL,
  KC_LBRACKET,
  KC_RBRACKET,
  KC_BSLASH,
  KC_SCOLON,
  KC_QUOTE,
  KC_COMMA,
  KC_DOT,
  KC_SLASH,
  KC_ESCAPE
};
const int length_of_leave_ime_on_keys = sizeof leave_ime_on_keys / sizeof leave_ime_on_keys[0];

// sensibleキーマップは統一してレイヤー0をPC用キーマップ、レイヤー1をMac用キーマップにしている
enum layers {
  LAYER_PC,
  LAYER_MAC
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (process_record_user_bmp(keycode, record) == false)
    return PROCESS_OVERRIDE_BEHAVIOR;

  for (int i = 0; i < length_of_leave_ime_on_keys; i++) {
    if (leave_ime_on_keys[i] == keycode) {
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
          case LAYER_PC:
            tap_code(KC_MHEN);
            break;
          case LAYER_MAC:
            tap_code(KC_LANG2);
            break;
          default:
            SEND_STRING("ILLEGAL STATE!");
            return false;
        }
      }
      break;
    }
  }

  return true;
}
