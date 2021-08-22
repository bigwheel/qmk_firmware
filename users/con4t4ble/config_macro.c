#include QMK_KEYBOARD_H

const uint16_t PROGMEM combo_inputs[COMBO_COUNT][3] = {
    { KC_TAB, KC_Q, COMBO_END },
    { KC_DOT, KC_SLSH, COMBO_END },
    { KC_L, KC_SCLN, COMBO_END },
};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_inputs[0], KC_ESC),
    COMBO(combo_inputs[1], KC_LGUI),
    COMBO(combo_inputs[2], KC_LALT),
};
