#include QMK_KEYBOARD_H

const uint16_t PROGMEM combo_inputs[COMBO_COUNT][3] = {
    { KC_J, KC_K, COMBO_END },
    { KC_TAB, KC_Q, COMBO_END },
};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_inputs[0], KC_BSPC),
    COMBO(combo_inputs[1], KC_ESC),
    // マクロのせいか複合リテラルが使えない
    // 以下はコンパイルが通るものの解釈がうまく行っていないのか
    // 結局動かない
    // COMBO(((uint16_t [3]){ KC_ESC, KC_Q, COMBO_END }), KC_TAB)
};
