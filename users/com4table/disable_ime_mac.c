#include "disable_ime.h"

#include QMK_KEYBOARD_H

void disable_ime(void) {
    tap_code(KC_LANG2);
}
