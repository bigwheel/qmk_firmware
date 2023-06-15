#include QMK_KEYBOARD_H

// sensibleキーマップは統一してレイヤー0をPC用キーマップ、レイヤー1をMac用キーマップにしている
enum layers {
  LAYER_PC,
  LAYER_MAC
};

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  KC_DISPEL = EZ_SAFE_RANGE
#else
  KC_DISPEL = SAFE_RANGE
#endif
};

#include "./keymap.h"

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
  KC_LBRC,
  KC_RBRC,
  KC_BSLS,
  KC_SCLN,
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
  KC_LBRC,
  KC_RBRC,
  KC_BSLS,
  KC_SCLN,
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

// デフォルトレイヤーに合わせて日本語入力をOFFにする
void off_ime(void) {
  switch (biton32(default_layer_state)) {
    case LAYER_PC:
      tap_code(KC_INT5);
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
      off_ime();
      set_mods(real_mods_memory);
    }
  }

  return PROCESS_USUAL_BEHAVIOR;
}


// 以下default keymapからコピー

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
