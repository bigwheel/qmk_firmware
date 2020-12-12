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
#include <stdbool.h>

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  DISPEL = BMP_SAFE_RANGE, // 記号を押したときのIME無効化の挙動を打ち消す
};

const key_string_map_t custom_keys_user = {
  .start_kc = DISPEL,
  .end_kc = DISPEL,
  .key_strings = "DISPEL\0"
};

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

// アルファベット以外で処理をすれば最初はよいかなと考えていたが
// modifier key, backspaceなど例外が多数あることを考えれば
// 結局自分で定義するのが一旦楽という結論になった。
// qmk firmware側でmodifier keyが配列で定義されていたりするようであれば
// 種別ベースなどで選択するのもありかもしれない。
const uint16_t leave_ime_on_keys[] = {
  // https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes_basic#letters-and-numbers
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
  KC_ESCAPE,
  // KC_MINUS,
  KC_EQUAL,
  KC_LBRACKET,
  KC_RBRACKET,
  KC_BSLASH,
  KC_SCOLON,
  KC_QUOTE,
  KC_GRAVE,
  // KC_COMMA,
  // KC_DOT,
  KC_SLASH,

  // https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes_us_ansi_shifted.md
  KC_TILDE,
  KC_EXCLAIM,
  KC_AT,
  KC_HASH,
  KC_DOLLAR,
  KC_PERCENT,
  KC_CIRCUMFLEX,
  KC_AMPERSAND,
  KC_ASTERISK,
  KC_LEFT_PAREN,
  KC_RIGHT_PAREN,
  KC_UNDERSCORE,
  KC_PLUS,
  KC_LEFT_CURLY_BRACE,
  KC_RIGHT_CURLY_BRACE,
  KC_PIPE,
  KC_COLON,
  KC_DOUBLE_QUOTE,
  KC_LEFT_ANGLE_BRACKET,
  KC_RIGHT_ANGLE_BRACKET,
  KC_QUESTION
};
const int length_of_leave_ime_on_keys = sizeof leave_ime_on_keys / sizeof leave_ime_on_keys[0];

const uint16_t leave_ime_on_keys_with_shift[] = {
  // https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes_basic#letters-and-numbers
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
  KC_ESCAPE,
  KC_MINUS,
  KC_EQUAL,
  KC_LBRACKET,
  KC_RBRACKET,
  KC_BSLASH,
  KC_SCOLON,
  KC_QUOTE,
  KC_GRAVE,
  KC_COMMA,
  KC_DOT,
  KC_SLASH,

  // https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes_us_ansi_shifted.md
  KC_TILDE,
  KC_EXCLAIM,
  KC_AT,
  KC_HASH,
  KC_DOLLAR,
  KC_PERCENT,
  KC_CIRCUMFLEX,
  KC_AMPERSAND,
  KC_ASTERISK,
  KC_LEFT_PAREN,
  KC_RIGHT_PAREN,
  KC_UNDERSCORE,
  KC_PLUS,
  KC_LEFT_CURLY_BRACE,
  KC_RIGHT_CURLY_BRACE,
  KC_PIPE,
  KC_COLON,
  KC_DOUBLE_QUOTE,
  KC_LEFT_ANGLE_BRACKET,
  KC_RIGHT_ANGLE_BRACKET,
  KC_QUESTION
};
const int length_of_leave_ime_on_keys_with_shift =
   sizeof leave_ime_on_keys_with_shift / sizeof leave_ime_on_keys_with_shift[0];

// sensibleキーマップは統一してレイヤー0をPC用キーマップ、レイヤー1をMac用キーマップにしている
enum layers {
  LAYER_PC,
  LAYER_MAC
};

#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

bool dispel_is_pressing = false;

// 参考元: https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros#super-alt-tab
bool ime_is_disabled_automatically = false;
uint16_t last_key_record_time = 0;
#define IME_DISABLED_TIME 10000

// デフォルトレイヤーに合わせて日本語入力をOFFにする
void off_ime() {
  switch (biton32(default_layer_state)) {
    case LAYER_PC:
      tap_code(KC_MHEN);
      break;
    case LAYER_MAC:
      tap_code(KC_LANG2);
      break;
    default:
      SEND_STRING("ILLEGAL STATE!");
  }
}

void matrix_scan_user(void) {
  if (ime_is_disabled_automatically == false)
    if (timer_elapsed(last_key_record_time) > IME_DISABLED_TIME) {
      off_ime();
      ime_is_disabled_automatically = true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  last_key_record_time = timer_read();
  ime_is_disabled_automatically = false;

  if (process_record_user_bmp(keycode, record) == PROCESS_OVERRIDE_BEHAVIOR)
    return PROCESS_OVERRIDE_BEHAVIOR;

  if (keycode == DISPEL) {
    dispel_is_pressing = record->event.pressed;
    return PROCESS_USUAL_BEHAVIOR;
  }

  if (!dispel_is_pressing) {
    bool leave_ime_on = false;
    for (int i = 0; i < length_of_leave_ime_on_keys; i++)
      if (leave_ime_on_keys[i] == keycode) {
        leave_ime_on = true;
        break;
      }
    // https://www.reddit.com/r/olkb/comments/covpq3/problem_checking_for_modifier_key_on_custom_key/
    if (get_mods() & MOD_MASK_SHIFT)
      for (int i = 0; i < length_of_leave_ime_on_keys_with_shift; i++)
        if (leave_ime_on_keys_with_shift[i] == keycode) {
          leave_ime_on = true;
          break;
        }

    if (leave_ime_on && record->event.pressed) {
      uint8_t real_mods_memory = get_mods();
      clear_mods();
      off_ime();
      set_mods(real_mods_memory);
    }
  }

  return PROCESS_USUAL_BEHAVIOR;
}
