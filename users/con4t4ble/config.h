#pragma once

// halberdはなぜかキーボード組み込み設定でTAPPING_TERM 100という
// 超絶シビア設定になっている(´・ω・｀)ので一度設定を取り除く
#undef TAPPING_TERM

#define TAPPING_TERM 200

#define COMBO_COUNT  3
