# CSC3050 2025 Spring Project 3

This is a forked version of Hao He's [RISC-V Simulator](https://github.com/hehao98/RISCV-Simulator).

For project details, please refer to the PDF on BlackBoard.

## Project Compilation

```bash
# Clone the project
git clone https://github.com/EnderturtleOrz/CSC3050-2025-Spring-Project-3.git
cd CSC3050-2025-Spring-Project-3

# Make a build folder
mkdir build
cd build

# Build the project
cmake ..
make
```

## Project Structure

- `src`: Source code
- `include`: ELFIO headers
- `test-*`: Test case folders

## Useful Scripts

You can use `bash <script_name>` to run the scripts.

- `build-test.sh`: Builds ELF files for the following test cases. You can find the ELF files and objdumped files under `/riscv-elf`:
  - `build-test-basic.sh`
  - `build-test-inclass.sh`
  - `build-test-fused.sh`
- `run-simulator.sh`: Runs all ELF files under `/riscv-elf` and outputs results to `/results`;
- `run-simulator-without-data-forwarding.sh` : Run all ELF files without data forwarding.

## Expected Results

| Test case     | Data forwarding? | Cycles |
|---------------|------------------|--------|
| ackermann     | ✔️                | 480358 |
| ackermann     | ❌                | 719706 |
| fmadd / fmsub | ✔️                | 813    |
| fmadd / fmsub | ❌                | 1113   |
| fnm           | ✔️                | 811    |
| fnm           | ❌                | 1109   |
