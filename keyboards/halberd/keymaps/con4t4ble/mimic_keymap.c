#include "mimic_keymap.h"

#include QMK_KEYBOARD_H
#include "util.h"
#include "keymap_jp.h"

typedef struct {
    uint16_t original_keycode;
    uint16_t without_shift;
    uint16_t with_shift;
} keycode_mapping;

keycode_mapping kms[] = {
    { KC_2,    KC_2,    JP_AT   },
    { KC_6,    KC_6,    JP_CIRC },
    { KC_7,    KC_7,    JP_AMPR },
    { KC_8,    KC_8,    JP_ASTR },
    { KC_9,    KC_9,    JP_LPRN },
    { KC_0,    KC_0,    JP_RPRN },
    { KC_MINS, KC_MINS, JP_UNDS },
    { KC_EQL,  JP_EQL,  JP_PLUS },
    { KC_LBRC, JP_LBRC, JP_LCBR },
    { KC_RBRC, JP_RBRC, JP_RCBR },
    { KC_BSLS, JP_BSLS, JP_PIPE },
    { KC_SCLN, KC_SCLN, JP_COLN },
    { KC_QUOT, JP_QUOT, JP_DQUO },
    { KC_GRV,  JP_GRV,  JP_TILD },
    // モディファイア情報付きキーコード系
    // https://docs.qmk.fm/#/ja/keycodes_us_ansi_shifted
    { KC_TILD, JP_TILD, JP_TILD },
    { KC_EXLM, JP_EXLM, JP_EXLM },
    { KC_AT  , JP_AT,   JP_AT   },
    { KC_HASH, JP_HASH, JP_HASH },
    { KC_DLR,  JP_DLR,  JP_DLR  },
    { KC_PERC, JP_PERC, JP_PERC },
    { KC_CIRC, JP_CIRC, JP_CIRC },
    { KC_AMPR, JP_AMPR, JP_AMPR },
    { KC_ASTR, JP_ASTR, JP_ASTR },
    { KC_LPRN, JP_LPRN, JP_LPRN },
    { KC_RPRN, JP_RPRN, JP_RPRN },
    { KC_UNDS, JP_UNDS, JP_UNDS },
    { KC_PLUS, JP_PLUS, JP_PLUS },
    { KC_LCBR, JP_LCBR, JP_LCBR },
    { KC_RCBR, JP_RCBR, JP_RCBR },
    { KC_PIPE, JP_PIPE, JP_PIPE },
    { KC_COLN, JP_COLN, JP_COLN },
    { KC_DQUO, JP_DQUO, JP_DQUO },
    { KC_LABK, JP_LABK, JP_LABK },
    { KC_RABK, JP_RABK, JP_RABK },
    { KC_QUES, JP_QUES, JP_QUES },
};

// 押したときのShiftの状態を保存しておく。
// mimic keymapではShiftが押された状態でそのキーを押した場合と
// Shiftが押されていない状態でそのキーを押した場合では
// キーコードが異なってくるため、
// Shift押す → ;押す → Shift離す → ;離す
// とすると
// Shift押す → ;押す(:が押される) → Shift離す → ;離す(;が離される)
// となり:が押された状態で残ってしまう。
// 以下はそれを回避するための、最後にキーを入力したときの
// Shiftの状態を保存するための配列
bool pressed_with_shifts[sizeof kms / sizeof kms[0]];

bool shift_is_pressing(void) {
    return get_mods() & MOD_MASK_SHIFT;
}

void process_mimic_key(keyrecord_t* record, keycode_mapping* km, bool* pressed_with_shift) {
    uint8_t mod_state = get_mods();

    if (record->event.pressed) {
        *pressed_with_shift = shift_is_pressing();

        del_mods(MOD_MASK_SHIFT);
        // 下記キーコードがShift状態を保持しているので、
        // Shift状態がちゃんと反映されるように↑で一旦剥がしている
        if (*pressed_with_shift)
            register_code16(km->with_shift);
        else
            register_code16(km->without_shift);
    } else {
        if (*pressed_with_shift)
            unregister_code16(km->with_shift);
        else
            unregister_code16(km->without_shift);
    }

    set_mods(mod_state);
}

bool process_record_user_mimic(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    for (int i = 0; i < sizeof pressed_with_shifts / sizeof pressed_with_shifts[0]; i++)
        uprintf("%b", pressed_with_shifts[i]);
    uprintf("\n");
#endif

  // https://docs.qmk.fm/#/feature_advanced_keycodes?id=shift-backspace-for-delete
    for (int i = 0; i < sizeof kms / sizeof kms[0]; i++)
        if (kms[i].original_keycode == keycode) {
            process_mimic_key(record, &kms[i], &pressed_with_shifts[i]);
            return PROCESS_OVERRIDE_BEHAVIOR;
        }

    return PROCESS_USUAL_BEHAVIOR;
}
