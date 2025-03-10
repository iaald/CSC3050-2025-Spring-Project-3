# CSC3050 2025 Spring Project 3

This is a forked version of Hao He's [RISC-V Simulator](https://github.com/hehao98/RISCV-Simulator).

For project details, please refer to the PDF on BlackBoard.

## Project Structure

- `src`: Source code
- `include`: ELFIO headers
- `test-*`: Test case folders

## Useful Scripts

- `build-test.sh`: Builds ELF files for the following test cases. You can find the ELF files and objdumped files under `/riscv-elf`:
  - `build-test-basic.sh`
  - `build-test-inclass.sh`
  - `build-test-fused.sh`
- `run-simulator`: Runs all ELF files under `/riscv-elf` and outputs results to `/results`.

## Expected Results

813 cycles for `fmadd(sub).c` and 811 cycles for `fnm.c`