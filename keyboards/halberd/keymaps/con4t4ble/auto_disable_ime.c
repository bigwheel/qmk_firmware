#include "auto_disable_ime.h"

#include QMK_KEYBOARD_H
#include "util.h"
#include "disable_ime.h"
#include "auto_disable_ime_keys.h"

enum custom_keycodes {
    KC_DISPEL = SAFE_RANGE, // 記号を押したときのIME無効化の挙動を打ち消す
};

bool dispel_is_pressing = false;

// TODO あとで以下のところの処理をこの関数へ置き換える
bool exist_in_array(uint16_t elem, uint16_t* elems, int size) {
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

    if (!dispel_is_pressing) {
        bool disabling_ime = false;
        for (int i = 0; i < length_of_disabling_ime_keys; i++)
            if (disabling_ime_keys[i] == keycode) {
                disabling_ime = true;
                break;
            }
        // https://www.reddit.com/r/olkb/comments/covpq3/problem_checking_for_modifier_key_on_custom_key/
        if (get_mods() & MOD_MASK_SHIFT)
            for (int i = 0; i < length_of_disabling_ime_keys_with_shift; i++)
                if (disabling_ime_keys_with_shift[i] == keycode) {
                    disabling_ime = true;
                    break;
                }

        if (disabling_ime && record->event.pressed) {
            uint8_t real_mods_memory = get_mods();
            clear_mods();
            disable_ime();
            set_mods(real_mods_memory);
        }
    }

    return PROCESS_USUAL_BEHAVIOR;
}
