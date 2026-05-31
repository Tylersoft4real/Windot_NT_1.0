/* =====================================================================
 *  WINDOT NT 1.0 - HARDWARE KEYBOARD CONTROLLER INTERCEPTOR
 *  Copyright (c) 2026 Tylersoft Corporation
 * ===================================================================== */

#include <stdint.h>
#include "keymap.h"

// Read-port function for hardware I/O lines
static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Global flag to indicate when a command buffer is ready for evaluation
extern void screen_write_char(char c);

void keyboard_handler_callback(void) {
    // Read the keyboard status port (0x64) to verify data buffer is full
    if (inb(0x64) & 1) {
        // Read raw index byte from hardware key data port (0x60)
        uint8_t scancode = inb(0x60);
        
        // If a key release bit is flagged, skip evaluating it for now
        if (scancode & 0x80) {
            return;
        }
        
        // Translate scancode byte into standard char letter
        char ascii_char = kbd_us_map[scancode];
        
        // Output character onto display buffer via screen driver
        if (ascii_char != 0) {
            screen_write_char(ascii_char);
        }
    }
}
