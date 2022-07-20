#include "auto_disable_ime.h"

#include QMK_KEYBOARD_H
#include "auto_disable_ime_keys.h"
#include "disable_ime.h"
#include "qmk_backward_func.h"
#include "util_km.h"

bool dispel_is_pressing = false;

void disable_ime_then_restore_mods(void) {
    uint8_t real_mods_memory = get_mods();
    clear_mods();
    disable_ime();
    set_mods(real_mods_memory);
}

/*
 * 条件に当てはまるキー入力だったらIMEを無効化するキーをtapする
 */
bool process_record_user_auto_disable_ime(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_DISPEL) {
        dispel_is_pressing = record->event.pressed;
        return PROCESS_OVERRIDE_BEHAVIOR;
    }

    if (!record->event.pressed || dispel_is_pressing) return PROCESS_USUAL_BEHAVIOR;

    if ((get_mods() & MOD_MASK_SHIFT) && keycode >= KC_A && keycode <= KC_EXSEL &&  // 通常のキー範囲内
        !exist_in_array(keycode, not_disabling_ime_keys_with_shift, COUNT_OF(not_disabling_ime_keys_with_shift))) {
        disable_ime_then_restore_mods();
        return PROCESS_USUAL_BEHAVIOR;
    }

    if (exist_in_array(keycode, disabling_ime_keys, COUNT_OF(disabling_ime_keys))) {
        disable_ime_then_restore_mods();
        return PROCESS_USUAL_BEHAVIOR;
    }

    return PROCESS_USUAL_BEHAVIOR;
}
