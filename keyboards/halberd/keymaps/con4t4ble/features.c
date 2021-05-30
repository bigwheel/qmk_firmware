#include QMK_KEYBOARD_H
#include "mimic_keymap.h"

#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif

    if (process_record_user_mimic(keycode, record) == PROCESS_OVERRIDE_BEHAVIOR)
        return PROCESS_OVERRIDE_BEHAVIOR;
    else
        return PROCESS_USUAL_BEHAVIOR;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}
