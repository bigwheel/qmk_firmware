#pragma once

#include QMK_KEYBOARD_H
#include "bmp.h"
#include <stdbool.h>

// 参考元:
// https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros#super-alt-tab
bool     ime_is_disabled_automatically = false;
uint16_t last_key_record_time          = 0;
#define IME_DISABLED_TIME 10000

// sensibleキーマップは統一してレイヤー0をPC用キーマップ、レイヤー1をMac用キーマップにしている
enum layers {
    LAYER_PC,
    LAYER_MAC
};

// デフォルトレイヤーに合わせて日本語入力をOFFにする
void off_ime() {
    switch (biton32(default_layer_state)) {
        case LAYER_PC:
            tap_code(KC_MHEN);
            break;
        case LAYER_MAC:
            tap_code(KC_LANG2);
            break;
        default:
            SEND_STRING("ILLEGAL STATE!");
    }
}

void process_record_user_auto_disable_ime(void) {
    last_key_record_time          = timer_read();
    ime_is_disabled_automatically = false;
}

void matrix_scan_user_auto_disable_ime(void) {
    if (ime_is_disabled_automatically == false)
        if (timer_elapsed(last_key_record_time) > IME_DISABLED_TIME) {
            off_ime();
            ime_is_disabled_automatically = true;
        }
}
