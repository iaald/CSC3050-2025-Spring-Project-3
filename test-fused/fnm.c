#include "lib.h"

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int result = 0;

    // fnmadd.i
    asm volatile (
        ".insn r4 %[opcode], %[funct3], %[funct2], %[rd], %[rs1], %[rs2], %[rs3]\n"
        : [rd] "=r" (result)           // rd = result
        : [opcode] "i" (0x0B),
          [funct3] "i" (0x01),
          [funct2] "i" (0x00),
          [rs1] "r" (a),              // rs1 = a
          [rs2] "r" (b),              // rs2 = b
          [rs3] "r" (c)               // rs3 = c
        :
    );

    // result = - a * b + c = -1 * 2 + 3 = 1
    print_d(result);
    print_c('\n');

    int a_s = 1;
    int b_s = 2;
    int c_s = 3;
    int result_s = 0;

    // fnmsub.i
    asm volatile (
        ".insn r4 %[opcode], %[funct3], %[funct2], %[rd], %[rs1], %[rs2], %[rs3]\n"
        : [rd] "=r" (result_s)
        : [opcode] "i" (0x0B),
          [funct3] "i" (0x01),
          [funct2] "i" (0x01),
          [rs1] "r" (a_s),
          [rs2] "r" (b_s),
          [rs3] "r" (c_s)
        :
    );

    // result_s = - a * b - c = -1 * 2 - 3 = -5
    print_d(result_s);
    print_c('\n');
    
    exit_proc();
}