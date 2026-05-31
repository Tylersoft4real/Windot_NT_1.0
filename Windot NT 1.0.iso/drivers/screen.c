/* =====================================================================
 *  WINDOT NT 1.0 - VGA TEXT MODE DISPLAY DRIVER
 *  Copyright (c) 2026 Tylersoft Corporation
 *  Lead Architects: Tyler (CEO) & Mason
 * ===================================================================== */

#include <stdint.h>

// Screen dimensions for standard VGA text mode
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VGA_ADDRESS 0xB8000

// Shared variables tracked by the kernel layout
extern int terminal_column;
extern int terminal_row;
extern unsigned char current_theme_color;

// Pointer mapping directly to the video hardware memory lines
volatile uint16_t* video_memory_buffer = (volatile uint16_t*)VGA_ADDRESS;

/* Scrolls the screen text up by one full row when hitting bottom boundary */
void scroll_screen(void) {
    // Shift all text rows up by one row index
    for (int y = 0; y < SCREEN_HEIGHT - 1; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int current_index = y * SCREEN_WIDTH + x;
            int next_row_index = (y + 1) * SCREEN_WIDTH + x;
            video_memory_buffer[current_index] = video_memory_buffer[next_row_index];
        }
    }

    // Clear out the very bottom row cleanly so it is blank
    int bottom_row_start = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH;
    uint16_t blank_space = ' ' | (current_theme_color << 8);
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        video_memory_buffer[bottom_row_start + x] = blank_space;
    }

    // Set the cursor row position back to the bottom line
    terminal_row = SCREEN_HEIGHT - 1;
}

/* Internal character insertion tracking routine */
void screen_write_char(char c) {
    // Handle Newline Character logic
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
    } 
    // Handle Backspace Character logic
    else if (c == '\b') {
        if (terminal_column > 0) {
            terminal_column--;
            int index = terminal_row * SCREEN_WIDTH + terminal_column;
            video_memory_buffer[index] = ' ' | (current_theme_color << 8);
        }
    } 
    // Handle Standard Text Character logic
    else {
        int index = terminal_row * SCREEN_WIDTH + terminal_column;
        // Merge character byte with color byte into a 16-bit word
        video_memory_buffer[index] = c | (current_theme_color << 8);
        terminal_column++;
    }

    // If text cursor hits right edge, wrap around to next line
    if (terminal_column >= SCREEN_WIDTH) {
        terminal_column = 0;
        terminal_row++;
    }

    // If text cursor hits bottom edge, execute scrolling logic
    if (terminal_row >= SCREEN_HEIGHT) {
        scroll_screen();
    }
}
