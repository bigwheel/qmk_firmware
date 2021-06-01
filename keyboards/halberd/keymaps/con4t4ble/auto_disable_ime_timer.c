#include "auto_disable_ime_timer.h"

#include QMK_KEYBOARD_H
#include "disable_ime.h"

#define IME_DISABLED_TIME 10000

// 参考元: https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros#super-alt-tab
bool ime_is_disabled_automatically = false;
uint16_t last_key_record_time = 0;

void matrix_scan_user_auto_disable_ime_timer(void) {
  if (ime_is_disabled_automatically == false)
    if (timer_elapsed(last_key_record_time) > IME_DISABLED_TIME) {
      disable_ime();
      ime_is_disabled_automatically = true;
    }
}

void process_record_user_auto_disable_ime_timer(void) {
  last_key_record_time = timer_read();
  ime_is_disabled_automatically = false;
}
