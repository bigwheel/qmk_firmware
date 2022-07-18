#include "disable_ime.h"

#include QMK_KEYBOARD_H

// sensibleキーマップは統一してレイヤー0をPC用キーマップ、レイヤー1をMac用キーマップにしている
enum layers { LAYER_PC, LAYER_MAC };

// デフォルトレイヤーに合わせて日本語入力をOFFにする
void disable_ime(void) {
#if MAC_KEYMAP == 1
    tap_code(KC_LANG2);
#else
    tap_code(KC_MHEN);
#endif
}
