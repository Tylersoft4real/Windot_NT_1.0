/* =====================================================================
 *  WINDOT NT 1.0 - KEYBOARD TRANSLATION MATRIX HEADERS
 *  Copyright (c) 2026 Tylersoft Corporation
 * ===================================================================== */

#ifndef KEYMAP_H
#define KEYMAP_H

// A complete lookup array mapping raw hardware Scan Codes (US QWERTY)
// into standard text characters for screen input loops.
const char kbd_us_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',  
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

#endif
