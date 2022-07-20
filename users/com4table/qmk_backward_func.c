#include "qmk_backward_func.h"

#include QMK_KEYBOARD_H

// https://github.com/qmk/qmk_firmware/blob/b835171008eaeaa992a1b8e390af8bce6f5f0b8f/quantum/action.c#L989-L995
void tap_code_delay(uint8_t code, uint16_t delay) {
  register_code(code);
  for (uint16_t i = delay; i > 0; i--) {
    wait_ms(1);
  }
  unregister_code(code);
}

// https://github.com/qmk/qmk_firmware/blob/b835171008eaeaa992a1b8e390af8bce6f5f0b8f/quantum/action.c#L1001-L1003
void tap_code(uint8_t code) {
  tap_code_delay(code,
                 code == KC_CAPS_LOCK ? TAP_HOLD_CAPS_DELAY : TAP_CODE_DELAY);
}
