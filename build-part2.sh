#!/bin/bash
# Assume the risc tools already installed and exported in PATH

echo "Building Part2 ELFs..."
mkdir -p riscv-elf

echo "Building par2.s"

riscv32-unknown-elf-as part2.s -o riscv-elf/part2.o
riscv32-unknown-elf-ld riscv-elf/part2.o -o riscv-elf/part2.riscv

if [ -f part2_p2.s ]; then
    echo "Building part2_p2.s"
    riscv32-unknown-elf-as part2_p2.s -o riscv-elf/part2_p2.o
    riscv32-unknown-elf-ld riscv-elf/part2_p2.o -o riscv-elf/part2_p2.riscv
else
    echo "[WARNING] part2_p2.s not found"
fi

if [ -f part2_p3.s ]; then
    echo "Building part2_p3.s"
    riscv32-unknown-elf-as part2_p3.s -o riscv-elf/part2_p3.o
    riscv32-unknown-elf-ld riscv-elf/part2_p3.o -o riscv-elf/part2_p3.riscv
else
    echo "[WARNING] part2_p3.s not found"
fi
