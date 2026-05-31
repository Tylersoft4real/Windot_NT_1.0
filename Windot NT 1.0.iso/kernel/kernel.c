/* =====================================================================
 *  WINDOT NT 1.0 - CORE KERNEL INTERACTIVE SHELL BUILD
 *  Copyright (c) 2026 Tylersoft Corporation
 *  Lead Architect: Tyler (CEO) & Co-Developer: Mason
 * ===================================================================== */

#include "keymap.h"
#include "screen.h"

// Hardware display configurations
extern volatile char* vga_buffer;
extern int terminal_column;
extern int terminal_row;
extern unsigned char current_theme_color;

// SYSTEM COMMAND BUFFER - Holds the letters you type
char command_buffer[256];
int command_index = 0;

// Compares two text strings to check if they match
int string_compare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; // Strings do not match
        }
        i++;
    }
    return (str1[i] == str2[i]); // Returns 1 if identical
}

// Clears the text vault after a command is run
void clear_command_buffer(void) {
    for (int i = 0; i < 256; i++) {
        command_buffer[i] = '\0';
    }
    command_index = 0;
}

// EVALUATE TYPED WORDS
void process_system_command(void) {
    screen_write_char('\n'); // Move to a fresh line

    if (string_compare(command_buffer, "help")) {
        current_theme_color = 0x0E; // Yellow Text for tools list
        screen_write_string("Tylersoft Tools: help, version, system_info, crash\n");
    } 
    else if (string_compare(command_buffer, "version")) {
        current_theme_color = 0x0B; // Cyan text
        screen_write_string("Tylersoft Windot NT Kernel v1.0.0-Release (2026 Base Architecture)\n");
    } 
    else if (string_compare(command_buffer, "system_info")) {
        current_theme_color = 0x0F; // White text
        screen_write_string("--- WINDOT SYSTEM DIAGNOSTICS ---\n");
        screen_write_string("CPU Target: Intel Celeron N4020 Reference Layout (2 Threads)\n");
        screen_write_string("Physical Memory Space: 4.00 GB RAM Map Active.\n");
    } 
    else if (string_compare(command_buffer, "crash")) {
        current_theme_color = 0x4F; // Red Screen of Death Theme (White on Red)
        // Clear screen to flash your legendary custom Windot XP red alert layout
        for (int i = 0; i < 80 * 25 * 2; i += 2) {
            vga_buffer[i] = ' ';
            vga_buffer[i+1] = current_theme_color;
        }
        terminal_column = 0; terminal_row = 0;
        screen_write_string("======================================================================\n");
        screen_write_string("A critical system stop check has been induced manually.\n\n");
        screen_write_string("WINDOT_MEMORY_CORRUPTION\n\n");
        screen_write_string("Technical Information: *** STOP: 0x000000D1\n");
        screen_write_string("======================================================================\n");
        while(1); // Lock the CPU in a safe crash hold
    } 
    else if (command_index > 0) {
        current_theme_color = 0x0C; // Red text for errors
        screen_write_string("Unknown tool. Type 'help' for valid parameters.\n");
    }

    // Reset prompt layout frame
    current_theme_color = 0x0F; // Back to clean text
    screen_write_string("Windot Prompt> ");
    clear_command_buffer();
}

// DRIVER HOOK - Feeds keys typed by your keyboard driver directly into your buffer
void kernel_handle_keyboard_input(char ascii_char) {
    // If user presses ENTER key
    if (ascii_char == '\n') {
        process_system_command();
    } 
    // If user presses BACKSPACE key
    else if (ascii_char == '\b') {
        if (command_index > 0) {
            command_index--;
            command_buffer[command_index] = '\0';
            screen_write_char('\b'); // Erase letter from display
        }
    } 
    // Store standard characters until text limits are hit
    else if (command_index < 255) {
        command_buffer[command_index] = ascii_char;
        command_index++;
        screen_write_char(ascii_char); // Mirror character live onto screen
    }
}

// Auxiliary multi-character display utility
void screen_write_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        screen_write_char(str[i]);
    }
}

// THE KERNEL MAIN INITIALIZER EXPLICIT ROUTINE
void kernel_main(void) {
    current_theme_color = 0x0A; // Bright Green header theme
    
    // Clear screen space manually for pristine launch dashboard
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i+1] = current_theme_color;
    }
    terminal_column = 0; terminal_row = 0;

    screen_write_string("======================================================================\n");
    screen_write_string("   WINDOT NT 1.0 KERNEL ENGINE INITIALIZATION SUCCESSFUL\n");
    screen_write_string("   Developed by Tylersoft Corporation - Lead: Tyler (CEO) \n");
    screen_write_string("======================================================================\n\n");

    current_theme_color = 0x0F; // Swap back to default text configuration
    screen_write_string("Windot Prompt> ");
    clear_command_buffer();

    while(1) {
        // The core scheduler remains active waiting for your hardware ticks.
        // Mike can compile this code safely right now via the updated build.bat!
    }
}

