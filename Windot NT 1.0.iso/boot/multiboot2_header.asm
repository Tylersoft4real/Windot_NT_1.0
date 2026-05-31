; =====================================================================
;  WINDOT NT 1.0 - OFFICIAL MULTIBOOT2 HEADER SPECIFICATION
;  Copyright (c) 2026 Tylersoft Corporation
;  Target: x86_64 / GRUB UEFI Bootloaders
; =====================================================================

section .multiboot_header
align 8

header_start:
    dd 0xe85250d6                        ; Magic number for Multiboot2 [2]
    dd 0                                 ; Architecture: 0 = i386 / x86_64 Protected Mode [2]
    dd header_end - header_start         ; Header length [2]
    
    ; Checksum validation formula [2]
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; OPTIONAL TAG: Request console graphics/framebuffer details (if needed later)
align 8
    dw 5                                 ; Tag type 5: Framebuffer request
    dw 0                                 ; Flags (0 = optional)
    dd 20                                ; Tag size (20 bytes)
    dd 1024                              ; Preferred width
    dd 768                               ; Preferred height
    dd 32                                ; Preferred color depth (32-bit color)

    ; MANDATORY END TAG: Tells GRUB the header is complete [2]
align 8
    dw 0                                 ; Tag type 0 [2]
    dw 0                                 ; Flags 0 [2]
    dd 8                                 ; Tag size (8 bytes) [2]
header_end:
