#/bin/bash
# Build a number of risc-v programs for running tests
# Assume the risc tools already installed and exported in PATH

mkdir -p build
cd build
cmake ..
make

mkdir -p ../results-without-data-forwarding


for riscv_file in ../riscv-elf/*.riscv; do
   echo "Running $riscv_file without data forwarding"
   # For test_syscall.riscv, we need to send "1\na" to stdin
    if [ "$(basename "$riscv_file" .riscv)" == "test_syscall" ]; then
        echo -e "1\na" | ./Simulator "$riscv_file" -x > "../results-without-data-forwarding/$(basename "$riscv_file" .riscv).txt"
        continue
    fi
  ./Simulator "$riscv_file" -x > "../results-without-data-forwarding/$(basename "$riscv_file" .riscv).txt"
done