/* =====================================================================
 *  WINDOT NT 1.0 - GLOBAL DESCRIPTOR TABLE HEADERS
 *  Copyright (c) 2026 Tylersoft Corporation
 *  Lead Architects: Tyler (CEO) & Mason
 * ===================================================================== */

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// Structure defining an individual GDT entry gate
struct gdt_entry_struct {
    uint16_t limit_low;           // The lower 16 bits of the segment limit
    uint16_t base_low;            // The lower 16 bits of the base address
    uint8_t  base_middle;         // The next 8 bits of the base address
    uint8_t  access;              // Access flags determining privilege rings
    uint8_t  granularity;         // Size configurations and direction flags
    uint8_t  base_high;           // The final 8 bits of the base address
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

// Pointer structure telling the CPU where the master GDT is located
struct gdt_ptr_struct {
    uint16_t limit;               // Size of the entire table minus 1
    uint32_t base;                // The linear base memory address of the table
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

// System initialization routines for Mike to run on the super PC
void init_gdt(void);
void set_gdt_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif
