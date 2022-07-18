#include QMK_KEYBOARD_H
#include "virtual_keycode.h"

const uint16_t PROGMEM combo_inputs0[] = {KC_TAB, KC_Q, COMBO_END};
const uint16_t PROGMEM combo_inputs1[] = {KC_COMMA, KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_inputs2[] = {KC_Z, KC_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_inputs0, KC_ESC),
    COMBO(combo_inputs1, RIGHT_OF_LEFT_CTRL_KEY),
    COMBO(combo_inputs2, RIGHT_OF_LEFT_CTRL_KEY),
};
