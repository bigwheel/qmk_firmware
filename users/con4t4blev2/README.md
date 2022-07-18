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

キーボードが MAC 用の場合、keyboards/xxxx/keymaps/xxxx/rules.mk へ以下を追記する。

```
define MAC_KEYMAP
```

#### 実装

[rules.mk の機能](https://github.com/qmk/qmk_firmware/blob/master/docs/ja/feature_userspace.md#rulesmk)を利用している。
