#pragma once

#include QMK_KEYBOARD_H
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"

enum custom_keycodes {
    KC_DISPEL = BMP_SAFE_RANGE, // 記号を押したときのIME無効化の挙動を打ち消す
};

bool process_record_user_auto_disable_ime(uint16_t keycode, keyrecord_t *record);
