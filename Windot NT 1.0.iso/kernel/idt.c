/* =====================================================================
 *  WINDOT NT 1.0 - INTERRUPT DESCRIPTOR TABLE INITIALIZATION
 *  Copyright (c) 2026 Tylersoft Corporation
 * ===================================================================== */

#include "idt.h"
#include <string.h>

// Declare an array of 256 unique hardware and software lines
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

// External assembly script route that fires the CPU load instruction
extern void idt_flush(uint32_t);

// Populates an individual interrupt intercept point
void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low  = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel       = sel;
    idt_entries[num].always0   = 0;
    idt_entries[num].flags     = flags;
}

// Flushes the compiled interrupt mappings directly into the processor
void init_idt(void) {
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    // Clear memory channels cleanly before mapping hardware lines
    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    // Set Gate 0: Divide by Zero Fatal Error Handler (Redirects to a system pause)
    set_idt_gate(0, 0, 0x08, 0x8E); 
    
    // Set Gate 33: Keyboard Hardware Controller Route Line
    set_idt_gate(33, 0, 0x08, 0x8E);

    // Load active maps into the computer hardware CPU chips
    idt_flush((uint32_t)&idt_ptr);
}
