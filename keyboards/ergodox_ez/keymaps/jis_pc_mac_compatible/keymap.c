#include QMK_KEYBOARD_H
#include "version.h"

#define PC   0 // pc layer
#define SYMB 1 // symbols
#define MAC  2 // mac layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



/* Keymap 0: PC layer
 *
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |   1    |   2  |   3  |   4  |   5  |   6  | Up   | | PrScr|   7  |   8  |   9  |   0  |   -  |   ^    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | Down | |      |   Y  |   U  |   I  |   O  |   P  |   @    |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------| |------|   H  |   J  |   K  |   L  |   ;  |   :    |
 * |--------+------+------+------+------+------| LEFT | | RIGHT|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   N  |   M  |   ,  |   .  |   /  |   \    |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |  L1  | LGui | LAlt |  App | Muhen|                             |Henkan|   |  |   [  |   ]  |DF MAC|
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      |      | Home | | PgUp |Insert|
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | End  | | PgDn |      |      |
 *                               | Space|Backsp|------| |------| Del  |Enter |
 *                               |      |ace   | Esc  | |      |      |      |
 *                               `--------------------' `--------------------'
 */
[PC] = LAYOUT_ergodox(
  // left hand
  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_UP,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_DOWN,
  KC_LCTRL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LEFT,
  MO(SYMB), KC_LGUI, KC_LALT, KC_APP,  KC_MHEN,
                                                KC_TRNS, KC_HOME,
                                                         KC_END,
                                       KC_SPC,  KC_BSPC, KC_ESC,
  // right hand
  KC_PSCR,  KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  KC_TRNS,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_RIGHT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RO,
                     KC_HENK, KC_JYEN, KC_RBRC, KC_BSLS, DF(MAC),
  KC_PGUP,  KC_INS,
  KC_PGDN,
  KC_TRNS,  KC_DEL,  KC_ENT
),



/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.       ,--------------------------------------------------.
 * |   F1   |  F2  |  F3  |  F4  |  F5  |  F6  |      |       |      |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |--------+------+------+------+------+-------------|       |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |       |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |       |      |------+------+------+------+------+--------|
 * |  Reset |      |      |      |      |      |------|       |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |       |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |       |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'       `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                   |      |      |      |      |      |
 *   `----------------------------------'                                   `----------------------------------'
 *                                      ,-------------.       ,-------------.
 *                                      |      |      |       |      |      |
 *                               ,------|------|------|       |------+------+------.
 *                               |      |      |      |       |      |      |      |
 *                               |      |      |------|       |------|      |      |
 *                               |      |      |      |       |      |      |      |
 *                               `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
  // left hand
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),



/* Keymap 2: Mac layer
 *
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |   1    |   2  |   3  |   4  |   5  |   6  |  Up  | | PrScr|   7  |   8  |   9  |   0  |   -  |   ^    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | Down | |      |   Y  |   U  |   I  |   O  |   P  |   @    |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------| |------|   H  |   J  |   K  |   L  |   ;  |   :    |
 * |--------+------+------+------+------+------| LEFT | | RIGHT|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   N  |   M  |   ,  |   .  |   /  |   \    |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |  L1  | LAlt | LGui |      | Eisu |                             | Kana |   |  |   [  |   ]  |DF PC |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | App  | Home | | PgUp |Insert|
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | End  | | PgDn |      |      |
 *                               | Space|Backsp|------| |------| Del  |Enter |
 *                               |      |ace   | Esc  | |      |      |      |
 *                               `--------------------' `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[MAC] = LAYOUT_ergodox(  // layer 2 : mac
  // left hand
  KC_1,     KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_UP,
  KC_TAB,   KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,    KC_DOWN,
  KC_LCTRL, KC_A,    KC_S,     KC_D,    KC_F,    KC_G,
  KC_LSFT,  KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_LEFT,
  MO(SYMB), KC_LALT, KC_LGUI,  KC_TRNS, KC_LANG2,
                                                 KC_APP,  KC_HOME,
                                                          KC_END,
                                        KC_SPC,  KC_BSPC, KC_ESC,
  // right hand
  KC_PSCR,  KC_7,    KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,
  KC_TRNS,  KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_LBRC,
            KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_RIGHT, KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RO,
                     KC_LANG1, KC_JYEN, KC_RBRC, KC_BSLS, DF(PC),
  KC_PGUP,  KC_INS,
  KC_PGDN,
  KC_TRNS,  KC_DEL,  KC_ENT
),



};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
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
