#include QMK_KEYBOARD_H

// デフォルトのキーマップでこれを使用することはほぼないが、一応残しておく
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{KC_D, KC_E, KC_F, KC_A, KC_U, KC_L, KC_T, KC_K, KC_E, KC_Y, KC_M, KC_A,
      KC_P, KC_B, KC_Y, KC_F, KC_I, KC_R, KC_M, KC_W, KC_A, KC_R, KC_E}}
};

uint32_t keymaps_len() {
  return sizeof(keymaps)/sizeof(uint16_t);
}
