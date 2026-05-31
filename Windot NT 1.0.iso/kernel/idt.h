/* =====================================================================
 *  WINDOT NT 1.0 - INTERRUPT DESCRIPTOR TABLE HEADERS
 *  Copyright (c) 2026 Tylersoft Corporation
 * ===================================================================== */

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// Structure defining an individual IDT gate entry
struct idt_entry_struct {
    uint16_t base_low;            // The lower 16 bits of the target function pointer
    uint16_t sel;                 // Kernel segment selector pointing back to GDT
    uint8_t  always0;             // Reserved spacing byte, must remain 0
    uint8_t  flags;               // Type and attribute flags (presence, privilege level)
    uint16_t base_high;           // The upper 16 bits of the target function pointer
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// Pointer structure mapping table array rules to physical registers
struct idt_ptr_struct {
    uint16_t limit;               // Total size of the active table minus 1
    uint32_t base;                // The linear base memory address of the table array
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

// System initialization routines for Mason to verify
void init_idt(void);
void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

#endif
