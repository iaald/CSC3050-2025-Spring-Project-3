#!/bin/bash
# Build a number of risc-v programs for running tests
# Assume the risc tools already installed and exported in PATH

echo "Building RISC-V ELFs..."
mkdir -p riscv-elf

# List of test files
tests=(
  "fmadd"
  "fmsub"
  "fnm"
)

# Compile each test file
for test in "${tests[@]}"; do
  riscv32-unknown-elf-gcc -march=rv32imf test-fused/${test}.c test-fused/lib.c -o riscv-elf/${test}.riscv
done

echo "Automatically dumping ELFs for reference"
cd riscv-elf

# Dump each ELF file
for test in "${tests[@]}"; do
  riscv32-unknown-elf-objdump -D ${test}.riscv > ${test}.s
done

cd ..