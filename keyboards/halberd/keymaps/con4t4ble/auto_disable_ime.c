#include "auto_disable_ime.h"

#include QMK_KEYBOARD_H
#include "disable_ime.h"
#include "auto_disable_ime_keys.h"

enum custom_keycodes {
  KC_DISPEL = SAFE_RANGE, // 記号を押したときのIME無効化の挙動を打ち消す
};

#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

bool dispel_is_pressing = false;

bool process_record_user_auto_disable_ime(uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_DISPEL) {
    dispel_is_pressing = record->event.pressed;
    return PROCESS_USUAL_BEHAVIOR;
  }

  if (!dispel_is_pressing) {
    bool leave_ime_on = false;
    for (int i = 0; i < length_of_leave_ime_on_keys; i++)
      if (leave_ime_on_keys[i] == keycode) {
        leave_ime_on = true;
        break;
      }
    // https://www.reddit.com/r/olkb/comments/covpq3/problem_checking_for_modifier_key_on_custom_key/
    if (get_mods() & MOD_MASK_SHIFT)
      for (int i = 0; i < length_of_leave_ime_on_keys_with_shift; i++)
        if (leave_ime_on_keys_with_shift[i] == keycode) {
          leave_ime_on = true;
          break;
        }

    if (leave_ime_on && record->event.pressed) {
      uint8_t real_mods_memory = get_mods();
      clear_mods();
      disable_ime();
      set_mods(real_mods_memory);
    }
  }

  return PROCESS_USUAL_BEHAVIOR;
}
