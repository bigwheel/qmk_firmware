#pragma once

#include QMK_KEYBOARD_H

// アルファベット以外で処理をすれば最初はよいかなと考えていたが
// modifier key, backspaceなど例外が多数あることを考えれば
// 結局自分で定義するのが一旦楽という結論になった。
// qmk firmware側でmodifier keyが配列で定義されていたりするようであれば
// 種別ベースなどで選択するのもありかもしれない。
const uint16_t disabling_ime_keys[] = {
    // https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes_basic#letters-and-numbers
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
    KC_ESCAPE,
    // KC_MINUS,
    KC_EQUAL,
    KC_LBRACKET,
    KC_RBRACKET,
    KC_BSLASH,
    KC_SCOLON,
    KC_QUOTE,
    KC_GRAVE,
    // KC_COMMA,
    // KC_DOT,
    KC_SLASH,

    // https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes_us_ansi_shifted.md
    KC_TILDE,
    KC_EXCLAIM,
    KC_AT,
    KC_HASH,
    KC_DOLLAR,
    KC_PERCENT,
    KC_CIRCUMFLEX,
    KC_AMPERSAND,
    KC_ASTERISK,
    KC_LEFT_PAREN,
    KC_RIGHT_PAREN,
    KC_UNDERSCORE,
    KC_PLUS,
    KC_LEFT_CURLY_BRACE,
    KC_RIGHT_CURLY_BRACE,
    KC_PIPE,
    KC_COLON,
    KC_DOUBLE_QUOTE,
    KC_LEFT_ANGLE_BRACKET,
    KC_RIGHT_ANGLE_BRACKET,
    KC_QUESTION,
};

// shiftと一緒の場合はほとんどのキーでIMEを無効化するため、逆に無効化しないキーだけ列挙する
const uint16_t not_disabling_ime_keys_with_shift[] = {
    KC_SPACE,
    KC_LEFT,
    KC_RIGHT,
    KC_UP,
    KC_DOWN,
};
