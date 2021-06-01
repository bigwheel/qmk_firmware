#include QMK_KEYBOARD_H
#include "util.h"
#include "mimic_keymap.h"
#include "auto_disable_ime.h"
#include "auto_disable_ime_timer.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif

    process_record_user_auto_disable_ime_timer();
    /*
    if (process_record_user_auto_disable_ime(keycode, record) == PROCESS_OVERRIDE_BEHAVIOR)
        return PROCESS_OVERRIDE_BEHAVIOR;
    else
        return PROCESS_USUAL_BEHAVIOR;
        */

    if (process_record_user_mimic(keycode, record) == PROCESS_OVERRIDE_BEHAVIOR)
        return PROCESS_OVERRIDE_BEHAVIOR;
    else
        return PROCESS_USUAL_BEHAVIOR;
}

void matrix_scan_user(void) {
    matrix_scan_user_auto_disable_ime_timer();
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}
