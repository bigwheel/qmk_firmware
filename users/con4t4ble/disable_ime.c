#include "disable_ime.h"

#include QMK_KEYBOARD_H

// sensibleキーマップは統一してレイヤー0をPC用キーマップ、レイヤー1をMac用キーマップにしている
enum layers {
  LAYER_PC,
  LAYER_MAC
};

// デフォルトレイヤーに合わせて日本語入力をOFFにする
void disable_ime(void) {
  switch (biton32(default_layer_state)) {
    case LAYER_PC:
      tap_code(KC_INT5);
      break;
    case LAYER_MAC:
      tap_code(KC_LNG2);
      break;
    default:
      SEND_STRING("ILLEGAL STATE!");
  }
}
