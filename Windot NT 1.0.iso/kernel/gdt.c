/* =====================================================================
 *  WINDOT NT 1.0 - GLOBAL DESCRIPTOR TABLE INITIALIZATION
 *  Copyright (c) 2026 Tylersoft Corporation
 * ===================================================================== */

#include "gdt.h"

// Declare 5 distinct segment rows for your custom kernel layout
gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

// External assembly routine that tells the CPU to reload segment registers
extern void gdt_flush(uint32_t);

// Populates an individual segment block within the table matrix
void set_gdt_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

// Registers and links your kernel segments into the CPU core data lines
void init_gdt(void) {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    // Gate 0: The mandatory Null Segment required by Intel processors
    set_gdt_gate(0, 0, 0, 0, 0);
    
    // Gate 1: Kernel Code Segment (Flat 4GB memory map, Ring 0 execution)
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    
    // Gate 2: Kernel Data Segment (Flat 4GB memory map, Ring 0 system data)
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    // Gate 3: User Space Code Segment (Ring 3 privileges for Tylersoft Explorer)
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    
    // Gate 4: User Space Data Segment (Ring 3 privileges for third party apps)
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // Flush the table into your processor core registers
    gdt_flush((uint32_t)&gdt_ptr);
}
