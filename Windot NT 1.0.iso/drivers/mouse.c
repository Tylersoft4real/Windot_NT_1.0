/* =====================================================================
 *  WINDOT NT 1.0 - HARDWARE MOUSE PS/2 HARDWARE DRIVER
 *  Copyright (c) 2026 Tylersoft Corporation
 *  Lead Architects: Tyler (CEO) & Mason
 * ===================================================================== */

#include "mouse.h"

// Define legacy 8042 keyboard/mouse controller hardware I/O ports
#define MOUSE_DATA_PORT   0x60
#define MOUSE_STATUS_PORT 0x64
#define MOUSE_COMMAND_BIT 0xD4

int32_t mouse_x = 40; // Default pointer x starting grid position
int32_t mouse_y = 12; // Default pointer y starting grid position
uint8_t mouse_left_click = 0;
uint8_t mouse_right_click = 0;

static uint8_t mouse_cycle = 0;
static int8_t  mouse_packet[3];

// Output helper to command signals out to physical ports
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Wait routine for hardware command loops
void mouse_wait(uint8_t type) {
    uint32_t timeout = 100000;
    if (type == 0) {
        while (timeout-- && (inb(MOUSE_STATUS_PORT) & 1) == 0); // Wait for read ready
    } else {
        while (timeout-- && (inb(MOUSE_STATUS_PORT) & 2));     // Wait for write ready
    }
}

// Tells the motherboard to activate the aux mouse lines
void init_mouse(void) {
    uint8_t status;

    mouse_wait(1);
    outb(MOUSE_STATUS_PORT, 0xA8); // Enable secondary auxiliary device (mouse) [1]

    mouse_wait(1);
    outb(MOUSE_STATUS_PORT, 0x20); // Read current controller command byte
    mouse_wait(0);
    status = (inb(MOUSE_DATA_PORT) | 2); // Set bit 1 to activate mouse IRQ12 interrupt line [1]
    
    mouse_wait(1);
    outb(MOUSE_STATUS_PORT, 0x60); // Write back updated command configuration
    mouse_wait(1);
    outb(MOUSE_DATA_PORT, status);

    // Command mouse device to start streaming packet packages
    mouse_wait(1);
    outb(MOUSE_STATUS_PORT, MOUSE_COMMAND_BIT);
    mouse_wait(1);
    outb(MOUSE_DATA_PORT, 0xF4); // Enable packet streaming command [1]
    mouse_wait(0);
    inb(MOUSE_DATA_PORT); // Discard acknowledgment byte response
}

// Low-level processing routine running on every hardware tick movement [1]
void mouse_handler_callback(void) {
    uint8_t status = inb(MOUSE_STATUS_PORT);
    
    // Check if the incoming hardware data belongs to auxiliary mouse line [1]
    if ((status & 1) && (status & 0x20)) {
        mouse_packet[mouse_cycle++] = inb(MOUSE_DATA_PORT);

        if (mouse_cycle == 3) { // Complete 3-byte movement packet received [1]
            mouse_cycle = 0;

            // Extract click conditions from the header data byte flags [1]
            mouse_left_click  = mouse_packet[0] & 1;
            mouse_right_click = (mouse_packet[0] >> 1) & 1;

            // Extract directional offset adjustments tracking X and Y grids [1]
            int32_t x_offset = mouse_packet[1];
            int32_t y_offset = mouse_packet[2];

            // Update global position tracking variables
            mouse_x += x_offset;
            mouse_y -= y_offset; // Reverse Y alignment parameters for standard layouts [1]

            // Boundary checks to contain mouse within normal monitor limits (80x25 grid) [1]
            if (mouse_x < 0)  mouse_x = 0;
            if (mouse_x >= 80) mouse_x = 79;
            if (mouse_y < 0)  mouse_y = 0;
            if (mouse_y >= 25) mouse_y = 24;
        }
    }
}
