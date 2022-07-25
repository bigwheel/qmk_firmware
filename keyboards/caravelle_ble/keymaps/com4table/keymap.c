#include QMK_KEYBOARD_H
#include "app_ble_func.h"
#include "auto_disable_ime.h"
#include "auto_disable_ime_timer.h"
#include "util_km.h"
#include "virtual_keycode.h"
#include <stdio.h>

enum custom_keycodes {
  AD_WO_L = COM4TABLE_SAFE_RANGE, /* Start advertising without whitelist  */
  BLE_DIS,                        /* Disable BLE HID sending              */
  BLE_EN,                         /* Enable BLE HID sending               */
  USB_DIS,                        /* Disable USB HID sending              */
  USB_EN,                         /* Enable USB HID sending               */
  DELBNDS,                        /* Delete all bonding                   */
  ADV_ID0,                        /* Start advertising to PeerID 0        */
  ADV_ID1,                        /* Start advertising to PeerID 1        */
  ADV_ID2,                        /* Start advertising to PeerID 2        */
  ADV_ID3,                        /* Start advertising to PeerID 3        */
  ADV_ID4,                        /* Start advertising to PeerID 4        */
  BATT_LV,                        /* Display battery level in milli volts */
  DEL_ID0,                        /* Delete bonding of PeerID 0           */
  DEL_ID1,                        /* Delete bonding of PeerID 1           */
  DEL_ID2,                        /* Delete bonding of PeerID 2           */
  DEL_ID3,                        /* Delete bonding of PeerID 3           */
  DEL_ID4,                        /* Delete bonding of PeerID 4           */
  ENT_DFU,                        /* Start bootloader                     */
  ENT_SLP,                        /* Deep sleep mode                      */
};

extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LPRN,        KC_RPRN, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LEFT_OF_LEFT_LANG_KEY, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,        KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RIGHT_OF_LEFT_CTRL_KEY, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
           LEFT_OF_LEFT_LANG_KEY, LEFT_LANG_KEY, KC_SPC,  MO(1),          MO(2),   KC_ENT,  RIGHT_LANG_KEY, RIGHT_OF_LEFT_CTRL_KEY \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),

  [1] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DISPEL, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,        _______, KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _______, _______, _______, _______,        _______, _______, _______, _______ \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),

  [2] = LAYOUT(
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _______, KC_GRV,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, _______,        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DISPEL, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _______, KC_LBRC, KC_RBRC, KC_BSLS, KC_COMM, KC_DOT,  _______,        _______, KC_SLSH, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _______, _______, _______, _______,        _______, _______, _______, _______ \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),

  [3] = LAYOUT ( \
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    MO(3),   AD_WO_L, ADV_ID1, ADV_ID2, ADV_ID3, ADV_ID4,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _______, DELBNDS, DEL_ID1, DEL_ID2, DEL_ID3, DEL_ID4, XXXXXXX,        XXXXXXX, KC_PAUS, KC_LANG5,KC_PSCR, KC_SLCK, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _______, BATT_LV, ENT_SLP, ENT_DFU, RESET,   XXXXXXX, XXXXXXX,        XXXXXXX, KC_APP,  KC_CAPS, KC_INS,  KC_INT2, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _______, _______, _______, _______,        _______, _______, _______, _______ \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  ),

  [4] = LAYOUT ( \
 //+--------+--------+--------+--------+--------+--------+                        +--------+--------+--------+--------+--------+--------+
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET, \
 //|--------+--------+--------+--------+--------+--------+--------+      +--------+--------+--------+--------+--------+--------+--------|
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
 //|--------+--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
                               _______, _______, _______, _______,        _______, _______, _______, _______ \
 //                           +--------+--------+--------+--------+      +--------+--------+--------+--------+
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  process_record_user_auto_disable_ime_timer();

  if (process_record_user_auto_disable_ime(keycode, record) ==
      PROCESS_OVERRIDE_BEHAVIOR)
    return PROCESS_OVERRIDE_BEHAVIOR;

  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return PROCESS_OVERRIDE_BEHAVIOR;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return PROCESS_OVERRIDE_BEHAVIOR;
    case USB_EN:
      set_usb_enabled(true);
      return PROCESS_OVERRIDE_BEHAVIOR;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return PROCESS_OVERRIDE_BEHAVIOR;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return PROCESS_OVERRIDE_BEHAVIOR;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return PROCESS_OVERRIDE_BEHAVIOR;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case ADV_ID1:
      restart_advertising_id(1);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case ADV_ID2:
      restart_advertising_id(2);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case ADV_ID3:
      restart_advertising_id(3);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case ADV_ID4:
      restart_advertising_id(4);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case DEL_ID0:
      delete_bond_id(0);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case DEL_ID1:
      delete_bond_id(1);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case DEL_ID2:
      delete_bond_id(2);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case DEL_ID3:
      delete_bond_id(3);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return PROCESS_OVERRIDE_BEHAVIOR;
    case ENT_DFU:
      bootloader_jump();
      return PROCESS_OVERRIDE_BEHAVIOR;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return PROCESS_OVERRIDE_BEHAVIOR;
    }

  }

  return PROCESS_USUAL_BEHAVIOR;
}
;
