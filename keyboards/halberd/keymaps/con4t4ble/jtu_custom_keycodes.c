#include QMK_KEYBOARD_H
#include "jtu_custom_keycodes.h"

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

// すべてfalse(0)で初期化されることを期待しているけど
// 明示的に初期化するべきかも？
bool pressed[sizeof kms / sizeof kms[0]];

bool shift_is_pressing(void) {
    return get_mods() & MOD_MASK_SHIFT;
}

bool process_pseudo_key(keyrecord_t* record, keycode_mapping* km, bool* pressed) {
    if (record->event.pressed) {
        if (shift_is_pressing()) {
            uint8_t mod_state = get_mods();

            del_mods(MOD_MASK_SHIFT);
            register_code(KC_DEL);
            *pressed = true;

            set_mods(mod_state);
            return PROCESS_OVERRIDE_BEHAVIOR;
        }
    } else {
        if (*pressed) {


            unregister_code(KC_DEL);

            *pressed = false;
            return PROCESS_OVERRIDE_BEHAVIOR;
        }
    }
    return PROCESS_USUAL_BEHAVIOR;
}

bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record) {
  // https://docs.qmk.fm/#/feature_advanced_keycodes?id=shift-backspace-for-delete
    for (int i = 0; i < sizeof kms / sizeof kms[0]; i++)
        if (kms[i].original_keycode == keycode)
            return true;
            // return process_pseudo_key(record, &kms[i], &pressed[i]);

    return PROCESS_USUAL_BEHAVIOR;
}
