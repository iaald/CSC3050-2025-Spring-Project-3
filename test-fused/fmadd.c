#include "lib.h"

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int result = 0;

    // fmadd.i
    asm volatile (
        ".insn r4 %[opcode], %[funct3], %[funct2], %[rd], %[rs1], %[rs2], %[rs3]\n"
        : [rd] "=r" (result)
        : [opcode] "i" (0x0B),
          [funct3] "i" (0x00),
          [funct2] "i" (0x00),
          [rs1] "r" (a),
          [rs2] "r" (b),
          [rs3] "r" (c)
        :
    );

    // result = a * b + c = 1 * 2 + 3 = 5
    print_d(result);
    print_c('\n');

    unsigned a_u = 1;
    unsigned b_u = 2;
    unsigned c_u = 3;
    unsigned result_u = 0;

    // fmadd.u
    asm volatile (
        ".insn r4 %[opcode], %[funct3], %[funct2], %[rd], %[rs1], %[rs2], %[rs3]\n"
        : [rd] "=r" (result_u)
        : [opcode] "i" (0x0B),
          [funct3] "i" (0x00),
          [funct2] "i" (0x01),
          [rs1] "r" (a_u),
          [rs2] "r" (b_u),
          [rs3] "r" (c_u)
        :
    );

    // result_u = a_u * b_u + c_u = 1 * 2 + 3 = 5
    print_d(result_u);
    print_c('\n');

    exit_proc();
}