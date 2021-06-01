#include "auto_disable_ime.h"

#include QMK_KEYBOARD_H
#include "disable_ime.h"

enum custom_keycodes {
  KC_DISPEL = SAFE_RANGE, // 記号を押したときのIME無効化の挙動を打ち消す
};

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
  KC_A,
  KC_B,
  KC_C,
  KC_D,
  KC_E,
  KC_F,
  KC_G,
  KC_H,
  KC_I,
  KC_J,
  KC_K,
  KC_L,
  KC_M,
  KC_N,
  KC_O,
  KC_P,
  KC_Q,
  KC_R,
  KC_S,
  KC_T,
  KC_U,
  KC_V,
  KC_W,
  KC_X,
  KC_Y,
  KC_Z,

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

#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

bool dispel_is_pressing = false;

// 参考元: https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros#super-alt-tab
bool ime_is_disabled_automatically = false;
uint16_t last_key_record_time = 0;
#define IME_DISABLED_TIME 10000

void matrix_scan_user(void) {
  if (ime_is_disabled_automatically == false)
    if (timer_elapsed(last_key_record_time) > IME_DISABLED_TIME) {
      disable_ime();
      ime_is_disabled_automatically = true;
    }
}

bool process_record_user_auto_disable_ime(uint16_t keycode, keyrecord_t *record) {
  last_key_record_time = timer_read();
  ime_is_disabled_automatically = false;

  if (keycode == KC_DISPEL) {
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
      disable_ime();
      set_mods(real_mods_memory);
    }
  }

  return PROCESS_USUAL_BEHAVIOR;
}
