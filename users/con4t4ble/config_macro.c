#include QMK_KEYBOARD_H

const uint16_t PROGMEM combo_inputs0[] = { KC_TAB, KC_Q, COMBO_END };
const uint16_t PROGMEM combo_inputs1[] = { KC_COMMA, KC_DOT, KC_SLSH, COMBO_END };
const uint16_t PROGMEM combo_inputs2[] = { KC_L, KC_SCLN, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_inputs0, KC_ESC),
    COMBO(combo_inputs1, KC_LGUI),
    COMBO(combo_inputs2, KC_LALT),
};
