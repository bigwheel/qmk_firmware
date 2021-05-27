#include QMK_KEYBOARD_H
#include "jtu_custom_keycodes.h"

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
    { JU_2, { KC_2, false }, { KC_LBRC, false } },
    { JU_6, { KC_EQL, false }, { KC_6, false } },
    { JU_7, { KC_6, true }, { KC_7, false } },
    { JU_8, { KC_QUOT, true }, { KC_8, false } },
    { JU_9, { KC_8, true }, { KC_9, false } },
    { JU_0, { KC_9, true }, { KC_0, false } },
    { JU_MINS, { KC_INT1, true }, { KC_MINS, false } },
    { JU_EQL, { KC_SCLN, true }, { KC_MINS, true } },
    { JU_LBRC, { KC_RBRC, true }, { KC_RBRC, false } },
    { JU_RBRC, { KC_NUHS, true }, { KC_NUHS, false } },
    { JU_BSLS, { KC_INT3, true }, { KC_INT1, false } },
    { JU_SCLN, { KC_QUOT, false }, { KC_SCLN, false } },
    { JU_QUOT, { KC_2, true }, { KC_7, true } },
    { JU_GRV, { KC_EQL, true }, { KC_LBRC, true } },
};


bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false;
  static bool rshift = false;

  for (int i = 0; i < sizeof kms / sizeof kms[0]; i++) {
      if (kms[i].original_keycode == keycode) {
          if (record->event.pressed) {
              lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
              rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
              if (lshift || rshift) {
                  if (lshift) unregister_code(KC_LSFT);
                  if (rshift) unregister_code(KC_RSFT);

                  if (kms[i].with_shift.shift)
                      register_code(KC_LSFT);

                  register_code(kms[i].with_shift.keycode);
                  unregister_code(kms[i].with_shift.keycode);

                  if (kms[i].with_shift.shift)
                      unregister_code(KC_LSFT);

                  if (lshift) register_code(KC_LSFT);
                  if (rshift) register_code(KC_RSFT);
              } else {
                  if (kms[i].without_shift.shift)
                      register_code(KC_LSFT);

                  register_code(kms[i].without_shift.keycode);
                  unregister_code(kms[i].without_shift.keycode);

                  if (kms[i].without_shift.shift)
                      unregister_code(KC_LSFT);
              }
              return false;
          }
      }
  }


  switch (keycode) {
    case JU_CAPS:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        register_code(KC_CAPS);
        unregister_code(KC_CAPS);
        unregister_code(KC_LSFT);
      }
      return false;
  }
  return true;
}
