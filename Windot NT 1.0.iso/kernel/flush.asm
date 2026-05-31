; =====================================================================
;  WINDOT NT 1.0 - CPU TABLE REGISTERS FLUSHER UTILITY
;  Copyright (c) 2026 Tylersoft Corporation
;  Lead Architects: Tyler (CEO) & Mason
; =====================================================================

global gdt_flush        ; Makes the function visible to gdt.c
global idt_flush        ; Makes the function visible to idt.c

section .text

; Loads the Global Descriptor Table pointer into the CPU
gdt_flush:
    mov eax, [esp+4]    ; Get the GDT pointer address from the C arguments
    lgdt [eax]          ; Load the GDT pointer into the CPU hardware register

    ; Reload segment registers to force the CPU to use the new GDT settings
    mov ax, 0x10        ; 0x10 is the Kernel Data Segment index in our gdt.c
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    ; Perform a far jump to clear the pre-fetch queue and load the Code Segment
    jmp 0x08:.flush_done ; 0x08 is the Kernel Code Segment index

.flush_done:
    ret                 ; Return back to gdt.c execution line

; Loads the Interrupt Descriptor Table pointer into the CPU
idt_flush:
    mov eax, [esp+4]    ; Get the IDT pointer address from the C arguments
    lidt [eax]          ; Load the IDT pointer into the CPU hardware register
    ret                 ; Return back to idt.c execution line
