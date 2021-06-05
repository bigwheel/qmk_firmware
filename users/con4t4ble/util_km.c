#include "util_km.h"

#include QMK_KEYBOARD_H
#include <stdbool.h>

bool exist_in_array(uint16_t elem, const uint16_t* elems, int size) {
    for (int i = 0; i < size; i++)
        if (elems[i] == elem)
            return true;
    return false;
}
