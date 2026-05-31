; =====================================================================
;  WINDOT NT 1.0 - KERNEL LOW LEVEL ASSEMBLY ENTRY POINT
;  Copyright (c) 2026 Tylersoft Corporation
; =====================================================================

global _start               ; Make the entry label visible to the linker
extern kernel_main          ; Tell the assembler that kernel_main is in your C file

section .text
_start:
    cli                     ; Clear interrupts (disable them during critical setup)
    
    ; Setup a safe stack pointer for your C code execution
    mov esp, stack_top      
    
    ; Jump straight into Tyler's main C function!
    call kernel_main

.halt_loop:
    hlt                     ; Safely halt the CPU if kernel_main ever exits
    jmp .halt_loop          ; Loop forever just in case

section .bss
align 16
stack_bottom:
    resb 16384              ; Reserve 16 Kilobytes of memory space for the stack
stack_top:
