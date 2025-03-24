#/bin/bash
# Build a number of risc-v programs for running tests
# Assume the risc tools already installed and exported in PATH

mkdir -p build
cd build
cmake ..
make

mkdir -p ../results


for riscv_file in ../riscv-elf/*.riscv; do
   echo "Running $riscv_file without data forwarding"
  ./Simulator "$riscv_file" -x > "../results/$(basename "$riscv_file" .riscv).txt"
done