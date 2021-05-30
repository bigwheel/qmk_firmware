#include QMK_KEYBOARD_H
#include "mimic_keymap.h"
#include "keymap_jp.h"

#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

typedef struct {
    uint16_t keycode;
    bool shift;
} keycode_with_shift;

typedef struct {
    uint16_t original_keycode;
    keycode_with_shift without_shift;
    keycode_with_shift with_shift;
} keycode_mapping;

keycode_mapping kms[] = {
    { KC_2,    { KC_2,    false }, { KC_LBRC, false } },
    { KC_6,    { KC_6,    false }, { KC_EQL,  false } },
    { KC_7,    { KC_7,    false }, { KC_6,    true }  },
    { KC_8,    { KC_8,    false }, { KC_QUOT, true }  },
    { KC_9,    { KC_9,    false }, { KC_8,    true }  },
    { KC_0,    { KC_0,    false }, { KC_9,    true }  },
    { KC_MINS, { KC_MINS, false }, { KC_INT1, true }  },
    { KC_EQL,  { KC_MINS, true },  { KC_SCLN, true }  },
    { KC_LBRC, { KC_RBRC, false }, { KC_RBRC, true }  },
    { KC_RBRC, { KC_NUHS, false }, { KC_NUHS, true }  },
    { KC_BSLS, { KC_INT1, false }, { KC_INT3, true }  },
    { KC_SCLN, { KC_SCLN, false }, { KC_QUOT, false } },
    { KC_QUOT, { KC_7,    true },  { KC_2,    true }  },
    { KC_GRV,  { KC_LBRC, true },  { KC_EQL,  true }  },
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

uint16_t kms2[][2] = {
    { KC_AT  , JP_AT   },
    { KC_CIRC, JP_CIRC },
    { KC_AMPR, JP_AMPR },
    { KC_ASTR, JP_ASTR },
    { KC_LPRN, JP_LPRN },
    { KC_RPRN, JP_RPRN },
    // TODO これ以外もあるはず。ただしshiftなしの入力に変化する場合はそこそこ工夫が必要かも
    // { KC_AT, JP_AT },
};

bool shift_is_pressing(void) {
    return get_mods() & MOD_MASK_SHIFT;
}

void process_pseudo_key(keyrecord_t* record, keycode_mapping* km, bool* pressed_with_shift) {
    if (record->event.pressed) {
        uint8_t mod_state = get_mods();
        {
            keycode_with_shift kws;
            if (shift_is_pressing())
                kws = km->with_shift;
            else
                kws = km->without_shift;
            *pressed_with_shift = shift_is_pressing();

            if (kws.shift)
                add_mods(MOD_MASK_SHIFT);
            else
                del_mods(MOD_MASK_SHIFT);
            register_code(kws.keycode);
        }
        set_mods(mod_state);
    } else {
        keycode_with_shift kws;
        if (*pressed_with_shift)
            kws = km->with_shift;
        else
            kws = km->without_shift;
        uprintf("%d\n", kws.keycode);

        unregister_code(kws.keycode);
    }
}

bool process_record_user_mimic(uint16_t keycode, keyrecord_t *record) {
    for (int i = 0; i < sizeof pressed_with_shifts / sizeof pressed_with_shifts[0]; i++)
        uprintf("%b", pressed_with_shifts[i]);
    uprintf("\n");

    for (int i = 0; i < sizeof kms2 / sizeof kms2[0]; i++)
        if (kms2[i][0] == keycode) {
            uprintf("%d\n", i);
            // TODO shift押しながらだとこちらもうまく動かない
            if (record->event.pressed)
                register_code16(kms2[i][1]);
            else
                unregister_code16(kms2[i][1]);
            return PROCESS_OVERRIDE_BEHAVIOR;
        }

  // https://docs.qmk.fm/#/feature_advanced_keycodes?id=shift-backspace-for-delete
    for (int i = 0; i < sizeof kms / sizeof kms[0]; i++)
        if (kms[i].original_keycode == keycode) {
            process_pseudo_key(record, &kms[i], &pressed_with_shifts[i]);
            return PROCESS_OVERRIDE_BEHAVIOR;
        }

    return PROCESS_USUAL_BEHAVIOR;
}
