@echo off
title Tylersoft Windot NT 1.0 Release Compiler
set BUILD_VERSION=1.0.0-Release
set CORE_ARCH=Multi-Arch x16/x32/x64 Baseline

:: Dynamically calculate current system date blocks
for /f "tokens=2 delims==" %%I in ('wmic os get localdatetime /value') do set datetime=%%I
set BUILD_YEAR=%datetime:~0,4%
set BUILD_MONTH=%datetime:~4,2%
set BUILD_DAY=%datetime:~6,2%

echo =====================================================================
echo   TYLERSOFT CORPORATION - WINDOT NT MASTER COMPILATION PIPELINE
echo =====================================================================
echo   PRODUCT DESCRIPTION: Windot New Technology Open Kernel Engine
echo   BUILD VERSION:       %BUILD_VERSION%
echo   TARGET LANDSCAPE:    %CORE_ARCH%
echo   COMPILATION TIMESTAMP: %BUILD_YEAR%/%BUILD_MONTH%/%BUILD_DAY%
echo   FOUNDER / CEO:       Tyler
echo   DEVELOPMENT CO-DEVS: Mason, Mike (Hardware Lab QA Lead)
echo =====================================================================
echo.

echo [1/4] Assembling low-level hardware modules via NASM...
nasm -f elf32 boot_entry.asm -o boot.o
if %errorlevel% neq 0 goto borked
nasm -f elf32 multiboot2_header.asm -o header.o
if %errorlevel% neq 0 goto borked
nasm -f elf32 flush.asm -o flush.o
if %errorlevel% neq 0 goto borked

echo [2/4] Compiling core C kernel source code via GCC...
gcc -m32 -c kernel.c -o kernel.o -ffreestanding -O2 -Wall
if %errorlevel% neq 0 goto borked
gcc -m32 -c gdt.c -o gdt.o -ffreestanding -O2 -Wall
if %errorlevel% neq 0 goto borked
gcc -m32 -c idt.c -o idt.o -ffreestanding -O2 -Wall
if %errorlevel% neq 0 goto borked
gcc -m32 -c screen.c -o screen.o -ffreestanding -O2 -Wall
if %errorlevel% neq 0 goto borked
gcc -m32 -c keyboard.c -o keyboard.o -ffreestanding -O2 -Wall
if %errorlevel% neq 0 goto borked
gcc -m32 -c mouse.c -o mouse.o -ffreestanding -O2 -Wall
if %errorlevel% neq 0 goto borked

echo [3/4] Binding compiled objects into binary via Linker Script...
ld -m elf_i386 -T linker.ld header.o boot.o flush.o kernel.o gdt.o idt.o screen.o keyboard.o mouse.o -o windot_kernel.bin
if %errorlevel% neq 0 goto borked

echo.
echo =====================================================================
echo   SUCCESS: Windot NT %BUILD_VERSION% Core Is Fully Compiled!
echo   Target output: windot_kernel.bin (Ready for deployment tests)
echo =====================================================================
pause
exit

:borked
echo.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo   CRITICAL COMPILATION FAULT: Pipeline broken.
echo   Check your file paths and code syntax layout variables.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
pause
