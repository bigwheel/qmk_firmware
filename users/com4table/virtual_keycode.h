#pragma once

#include QMK_KEYBOARD_H

#ifndef MAC_KEYMAP
#    error MAC_KEYMAP macro variable is needed.
#endif

#if MAC_KEYMAP == 1
#    define LEFT_OF_LEFT_LANG_KEY KC_LGUI
#    define RIGHT_OF_LEFT_CTRL_KEY KC_LALT
#    define LEFT_LANG_KEY KC_LNG2
#    define RIGHT_LANG_KEY KC_LNG1
#else
#    define LEFT_OF_LEFT_LANG_KEY KC_LALT
#    define RIGHT_OF_LEFT_CTRL_KEY KC_LGUI
#    define LEFT_LANG_KEY KC_INT5
#    define RIGHT_LANG_KEY KC_INT4
#endif
