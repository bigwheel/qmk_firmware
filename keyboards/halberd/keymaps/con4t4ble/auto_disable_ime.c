#include "auto_disable_ime.h"

#include QMK_KEYBOARD_H
#include "util.h"
#include "disable_ime.h"
#include "auto_disable_ime_keys.h"

enum custom_keycodes {
    KC_DISPEL = SAFE_RANGE, // 記号を押したときのIME無効化の挙動を打ち消す
};

bool dispel_is_pressing = false;

bool exist_in_array(uint16_t elem, const uint16_t* elems, int size) {
    for (int i = 0; i < size; i++)
        if (elems[i] == elem)
            return true;
    return false;
}

bool process_record_user_auto_disable_ime(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_DISPEL) {
        dispel_is_pressing = record->event.pressed;
        return PROCESS_OVERRIDE_BEHAVIOR;
    }

    if (record->event.pressed && !dispel_is_pressing)
        if (
                exist_in_array(keycode, disabling_ime_keys, length_of_disabling_ime_keys)
                ||
                ((get_mods() & MOD_MASK_SHIFT) && exist_in_array(keycode, disabling_ime_keys_with_shift, length_of_disabling_ime_keys_with_shift))
           ) {
            uint8_t real_mods_memory = get_mods();
            clear_mods();
            disable_ime();
            set_mods(real_mods_memory);
        }

    return PROCESS_USUAL_BEHAVIOR;
}
