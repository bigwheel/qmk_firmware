#pragma once

// halberdでTAPPING_TERM 100になっていて原因調査にとても困った経験があるため、
// あまり美しくないが一律デフォルト値(200)へリセットしている
#undef TAPPING_TERM

#define TAPPING_TERM 200

#if defined PC_KEYMAP
#    define INNER_MOD_KEY KC_LALT
#else
#    define INNER_MOD_KEY KC_LGUI
#endif
