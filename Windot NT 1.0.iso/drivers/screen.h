/* =====================================================================
 *  WINDOT NT 1.0 - VGA TEXT MODE DISPLAY DRIVER HEADERS
 *  Copyright (c) 2026 Tylersoft Corporation
 *  Lead Architects: Tyler (CEO) & Mason
 * ===================================================================== */

#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

// Dimensions for standard VGA text layout mapping
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Expose driver routines to kernel files like kernel.c
void scroll_screen(void);
void screen_write_char(char c);

#endif
