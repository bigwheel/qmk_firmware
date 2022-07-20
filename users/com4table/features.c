#include QMK_KEYBOARD_H
#include "util_km.h"
#include "auto_disable_ime.h"
#include "auto_disable_ime_timer.h"

#ifndef CUSTOM_PROCESS_RECORD_USER
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_user_auto_disable_ime_timer();

    if (process_record_user_auto_disable_ime(keycode, record) == PROCESS_OVERRIDE_BEHAVIOR)
        return PROCESS_OVERRIDE_BEHAVIOR;
    else
        return PROCESS_USUAL_BEHAVIOR;
}
#endif

#ifndef CUSTOM_MATRIX_SCAN_USER
void matrix_scan_user(void) {
    matrix_scan_user_auto_disable_ime_timer();
}
#endif
