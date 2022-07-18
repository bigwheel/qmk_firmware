#!/usr/bin/env bash

set -eux

echo $1
basename $1
dirname $1
keymap_path=$(dirname $1)/keymap.c
rm $keymap_path
cat $(dirname $1)/head_of_keymap.c.tmpl > $keymap_path
qmk json2c $1 >> $keymap_path
