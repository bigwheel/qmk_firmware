# con4t4ble v2 keymap

con4t4ble のコンセプトを受け継ぎながら、発生した問題点を改善したもの。

## 機能

### OS 間のキー配置差分吸収

PC と MAC 間のキー配置の差分を吸収する機能。
以下のキーを OS に合わせたキーコードへ変更する。

-   Windows キー(Command キー)
-   Alt キー(Option キー)
-   変換キー(かなキー)
-   無変換キー(英数キー)

#### 使い方

そのキーボードを使いたい OS に合わせて

```c
#include "virtual_keycode_pc.h"
```

または

```c
#include "virtual_keycode_mac.h"
```

のどちらかを keymap.c に記述する。
