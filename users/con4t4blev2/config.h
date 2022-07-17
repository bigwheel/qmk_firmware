#pragma once

// halberdでTAPPING_TERM 100になっていて原因調査にとても困った経験があるため、
// あまり美しくないが一律デフォルト値(200)へリセットしている
#undef TAPPING_TERM

#define TAPPING_TERM 200

// 最初if definedでやろうとしたが、このconfig.hがkeyboards/xxx/keymaps下の
// config.hより先に読まれるようでPC_KEYMAPが定義される前にここが評価されてしまうようだ
// https://github.com/bigwheel/qmk_firmware/blob/b703d4a3bd8f752ae012caefddf699b4e03552e6/users/con4t4blev2/config.h
// なので、マクロ関数にして評価タイミングを keymap下のコードが処理されるところまで遅延させた
#define LEFT_OF_LEFT_LANG_KEY() (MAC_KEYMAP ? KC_LALT : KC_LGUI)
