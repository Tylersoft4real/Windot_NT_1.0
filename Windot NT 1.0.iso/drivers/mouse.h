/* =====================================================================
 *  WINDOT NT 1.0 - CORE PS/2 MOUSE CONTROLLER HEADERS
 *  Copyright (c) 2026 Tylersoft Corporation
 * ===================================================================== */

#ifndef MOUSE_H
#define MOUSE_H

#include <stdint.h>

// Tracking variables for coordinate maps across screen dimensions
extern int32_t mouse_x;
extern int32_t mouse_y;
extern uint8_t mouse_left_click;
extern uint8_t mouse_right_click;

// Initialization routines for compilation tracking
void init_mouse(void);
void mouse_handler_callback(void) [1];

#endif
