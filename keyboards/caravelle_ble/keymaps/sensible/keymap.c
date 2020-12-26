/*
Copyright 2019 Sekigon

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

#include QMK_KEYBOARD_H
#include "app_ble_func.h"
#include <stdio.h>




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

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    KC_DISPEL,
};


extern keymap_config_t keymap_config;

enum {
  LAYER_PC,
  LAYER_MAC,
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Layer related keycodes
#define ADJUST  MO(_ADJUST)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_PC] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,        XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ESC, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,        XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,\
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
             XXXXXXX, KC_LGUI, LT(2, KC_SPC),    LALT_T(KC_MHEN),         RALT_T(KC_HENK),  LT(3, KC_ENT),    KC_RGUI, XXXXXXX \
 //         +--------+--------+------------------+----------------+      +-----------------+-----------------+--------+--------+
  ),

  [LAYER_MAC] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,        XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ESC, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,        XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,\
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
             XXXXXXX, KC_LALT, LT(2, KC_SPC),    LGUI_T(KC_LANG2),        RGUI_T(KC_LANG1), LT(3, KC_ENT),    KC_RALT, XXXXXXX \
 //         +--------+--------+------------------+----------------+      +-----------------+-----------------+--------+--------+
  ),

  [_LOWER] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,        XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DISPEL, XXXXXXX, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,        XXXXXXX, KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               XXXXXXX, _______, _______, _______,        _______, MO(4),   _______, XXXXXXX \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),

  [_RAISE] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _______, KC_GRV,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, XXXXXXX,        XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DISPEL, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _______, KC_LBRC, KC_RBRC, KC_BSLS, KC_COMM, KC_DOT,  XXXXXXX,        XXXXXXX, KC_SLSH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               XXXXXXX, _______, MO(4),   _______,        _______, _______, _______, XXXXXXX \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),

  [_ADJUST] = LAYOUT ( \
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    XXXXXXX, RESET,   DF(0),   DF(1),   ENT_DFU, ENT_SLP,                          BATT_LV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _______, AD_WO_L, ADV_ID0, ADV_ID1, ADV_ID2, ADV_ID3, XXXXXXX,        XXXXXXX, XXXXXXX, KC_LANG5,KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _______, DELBNDS, DEL_ID0, DEL_ID1, DEL_ID2, DEL_ID3, XXXXXXX,        XXXXXXX, XXXXXXX, KC_CAPS, KC_INS,  KC_KANA, KC_APP,  _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               XXXXXXX, _______, _______, _______,        _______, _______, _______, XXXXXXX \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  )
};








bool dispel_is_pressing = false;

// 参考元: https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros#super-alt-tab
bool ime_is_disabled_automatically = false;
uint16_t last_key_record_time = 0;
#define IME_DISABLED_TIME 10000




void tap_code(uint8_t code) {
    register_code(code);
    if (code == KC_CAPS) {
        // wait_ms(TAP_HOLD_CAPS_DELAY);
        wait_ms(0);
    } else {
        // wait_ms(TAP_CODE_DELAY);
    }
    unregister_code(code);
}




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





#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

#define MOD_MASK_SHIFT (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  last_key_record_time = timer_read();
  ime_is_disabled_automatically = false;


  if (keycode == KC_DISPEL) {
    dispel_is_pressing = record->event.pressed;
    return PROCESS_USUAL_BEHAVIOR;
  }





  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }

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






  return true;
}
;
