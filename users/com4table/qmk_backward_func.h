#pragma once

#include QMK_KEYBOARD_H

enum hid_keyboard_keypad_usage_legacy2 {
  // https://github.com/qmk/qmk_firmware/blob/e7931289918221081cbe2a7ea5df27a5d86324db/quantum/keycode.h#L461
  KC_LEFT_SHIFT = 0xE1,
  // https://github.com/qmk/qmk_firmware/blob/e7931289918221081cbe2a7ea5df27a5d86324db/quantum/keycode.h#L465
  KC_RIGHT_SHIFT = 0xE5,
};

// https://github.com/qmk/qmk_firmware/blob/b835171008eaeaa992a1b8e390af8bce6f5f0b8f/quantum/keycode.h#L44
#define MOD_BIT(code) (1 << MOD_INDEX(code))
#define MOD_MASK_SHIFT (MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_RIGHT_SHIFT))

// https://github.com/qmk/qmk_firmware/blob/e7931289918221081cbe2a7ea5df27a5d86324db/quantum/keycode.h#L295
enum hid_keyboard_keypad_usage_legacy { KC_CAPS_LOCK = 0x39 };

// https://github.com/qmk/qmk_firmware/blob/b835171008eaeaa992a1b8e390af8bce6f5f0b8f/quantum/action.h#L31-L36
#define TAP_CODE_DELAY 0
#define TAP_HOLD_CAPS_DELAY 80

// https://github.com/qmk/qmk_firmware/blob/b835171008eaeaa992a1b8e390af8bce6f5f0b8f/quantum/action.c#L989-L995
void tap_code_delay(uint8_t code, uint16_t delay);

// https://github.com/qmk/qmk_firmware/blob/b835171008eaeaa992a1b8e390af8bce6f5f0b8f/quantum/action.c#L1001-L1003
void tap_code(uint8_t code);
