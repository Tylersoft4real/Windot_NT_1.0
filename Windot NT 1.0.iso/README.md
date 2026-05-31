\# Windot NT 1.0 (Kernel Base Source)

Developed by \*\*Tylersoft Corporation\*\*  

\*“When the old meets the new, and becomes chaotic in a good way.”\*



\---



\## 🚀 The Vision

Windot NT 1.0 is a highly optimized, open-source operating system kernel written completely from scratch. It is engineered from the ground up to act as a universal, free development foundation. By managing low-level hardware memory protection rings, CPU tables, and input drivers, it empowers developers around the world to quickly jump-start their own operating system projects without wading through months of low-level x86 configuration.



\## 🛠️ The Architecture Trio

To achieve true accessibility for any machine layout, Windot NT is partitioned into three target lanes:

1\. \*\*Windot NT x16 (Real Mode Baseline):\*\* Made specifically to boot fast on ancient retro machines, embedded computing targets, and legacy potato rigs.

2\. \*\*Windot NT x32 (Protected Mode Base):\*\* Perfectly tuned to handle 32-bit multitasking desktop configurations.

3\. \*\*Windot NT x64 (Long Mode Flagship):\*\* Engineered for maximum performance workloads on high-end custom supercomputers.



\---



\## 📂 Core Development Directory Tree

\* `boot\_entry.asm` — Assembly hook managing initial hardware stack creation.

\* `multiboot2\_header.asm` — GRUB / UEFI standardized system recognition file.

\* `flush.asm` — Direct-register machine controller script.

\* `kernel.c` — Principal logical evaluation system state matrix.

\* `gdt.h / gdt.c` — Segment privilege boundary registers (Rings 0-3).

\* `idt.h / idt.c` — Interrupt tracking infrastructure (Routing keys \& memory fault flags).

\* `screen.h / screen.c` — VGA display buffer manipulation utility.

\* `keymap.h / keyboard.c` — Layout matrix processing keyboard inputs.

\* `mouse.h / mouse.c` — PS/2 tracker engine following physical coordinate loops.

\* `linker.ld` — Storage layout alignment profile.

\* `build.bat` — One-click compilation pipeline file.



\---



\## 🏗️ Build Guide

1\. Pull down the repository files onto a modern machine workspace framework.

2\. Ensure you have \*\*NASM\*\*, \*\*GCC (cross-compiler)\*\*, and \*\*Binutils (ld)\*\* added to your environment paths.

3\. Double-click `build.bat` to automatically process and compile the system files.

4\. Drop the resulting `windot\_kernel.bin` target file directly into a GRUB-loaded test emulator layout.



\---



\## 👥 The Studio Dev Team

\* \*\*Tyler\*\* — Founder, CEO, and Principal Kernel Architect

\* \*\*Mason\*\* — Core Software Co-Developer

\* \*\*Mike\*\* — Hardware Lab Testing Infrastructure \& Quality Assurance Lead



