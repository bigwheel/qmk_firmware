#include "auto_disable_ime.h"

#include QMK_KEYBOARD_H
#include "util_km.h"
#include "disable_ime.h"
#include "auto_disable_ime_keys.h"

enum custom_keycodes {
    KC_DISPEL = SAFE_RANGE, // 記号を押したときのIME無効化の挙動を打ち消す
};

bool dispel_is_pressing = false;

/*
 * 条件に当てはまるキー入力だったらIMEを無効化するキーをtapする
 */
bool process_record_user_auto_disable_ime(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_DISPEL) {
        dispel_is_pressing = record->event.pressed;
        return PROCESS_OVERRIDE_BEHAVIOR;
    }

    if (record->event.pressed && !dispel_is_pressing)
        if (
                (get_mods() & MOD_MASK_CSAG)
                ||
                exist_in_array(keycode, disabling_ime_keys, COUNT_OF(disabling_ime_keys))
           )
            // Shift SpaceだけはIME ONを維持する
            if (!((get_mods() & MOD_MASK_SHIFT) && keycode == KC_SPC)) {
                uint8_t real_mods_memory = get_mods();
                clear_mods();
                disable_ime();
                set_mods(real_mods_memory);
            }

    return PROCESS_USUAL_BEHAVIOR;
}
