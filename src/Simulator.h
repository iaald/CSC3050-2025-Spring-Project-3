/*
 * Main Body for the RISCV Simulator
 *
 * Created by He, Hao at 2019-3-11
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <cstdarg>
#include <cstdint>
#include <string>
#include <vector>

#include "BranchPredictor.h"
#include "MemoryManager.h"

namespace RISCV {

const int REGNUM = 32;
extern const char *REGNAME[32];
typedef uint32_t RegId;
enum Reg {
  REG_ZERO = 0,
  REG_RA = 1,
  REG_SP = 2,
  REG_GP = 3,
  REG_TP = 4,
  REG_T0 = 5,
  REG_T1 = 6,
  REG_T2 = 7,
  REG_S0 = 8,
  REG_S1 = 9,
  REG_A0 = 10,
  REG_A1 = 11,
  REG_A2 = 12,
  REG_A3 = 13,
  REG_A4 = 14,
  REG_A5 = 15,
  REG_A6 = 16,
  REG_A7 = 17,
  REG_S2 = 18,
  REG_S3 = 19,
  REG_S4 = 20,
  REG_S5 = 21,
  REG_S6 = 22,
  REG_S7 = 23,
  REG_S8 = 24,
  REG_S9 = 25,
  REG_S10 = 26,
  REG_S11 = 27,
  REG_T3 = 28,
  REG_T4 = 29,
  REG_T5 = 30,
  REG_T6 = 31,
};

enum InstType {
  R_TYPE,
  I_TYPE,
  S_TYPE,
  SB_TYPE,
  U_TYPE,
  UJ_TYPE,
};
enum Inst {
  LUI = 0,
  AUIPC = 1,
  JAL = 2,
  JALR = 3,
  BEQ = 4,
  BNE = 5,
  BLT = 6,
  BGE = 7,
  BLTU = 8,
  BGEU = 9,
  LB = 10,
  LH = 11,
  LW = 12,
  LBU = 13,
  LHU = 14,
  SB = 15,
  SH = 16,
  SW = 17,
  ADDI = 18,
  SLTI = 19,
  SLTIU = 20,
  XORI = 21,
  ORI = 22,
  ANDI = 23,
  SLLI = 24,
  SRLI = 25,
  SRAI = 26,
  ADD = 27,
  SUB = 28,
  SLL = 29,
  SLT = 30,
  SLTU = 31,
  XOR = 32,
  SRL = 33,
  SRA = 34,
  OR = 35,
  AND = 36,
  ECALL = 37,
  FMADD = 38,
  FMSUB = 39,
  FNMADD = 40,
  FNMSUB = 41,
  MUL = 42,
  MULH = 43,
  DIV = 44,
  REM = 45,
  UNKNOWN = -1,
};
extern const char *INSTNAME[];

// Opcode field
const int OP_REG = 0x33;
const int OP_IMM = 0x13;
const int OP_LUI = 0x37;
const int OP_BRANCH = 0x63;
const int OP_STORE = 0x23;
const int OP_LOAD = 0x03;
const int OP_SYSTEM = 0x73;
const int OP_AUIPC = 0x17;
const int OP_JAL = 0x6F;
const int OP_JALR = 0x67;
const int OP_FUSED = 0x0B;

inline bool isBranch(Inst inst) {
  if (inst == BEQ || inst == BNE || inst == BLT || inst == BGE ||
      inst == BLTU || inst == BGEU) {
    return true;
  }
  return false;
}

inline bool isJump(Inst inst) {
  if (inst == JAL || inst == JALR) {
    return true;
  }
  return false;
}

inline bool isReadMem(Inst inst) {
  if (inst == LB || inst == LH || inst == LW || inst == LBU ||
      inst == LHU) {
    return true;
  }
  return false;
}

} // namespace RISCV

class Simulator {
public:
  bool isSingleStep;
  bool verbose;
  bool shouldDumpHistory;
  bool dataforwarding;
  uint32_t pc;
  uint32_t reg[RISCV::REGNUM];
  uint32_t stackBase;
  uint32_t maximumStackSize;
  MemoryManager *memory;
  BranchPredictor *branchPredictor;

  Simulator(MemoryManager *memory, BranchPredictor *predictor);
  ~Simulator();

  void initStack(uint32_t baseaddr, uint32_t maxSize);

  void simulate();

  void dumpHistory();

  void printInfo();

  void printStatistics();

private:
  int stallCnt;
  int rstPcCnt;
  bool forwardFetcher;
  bool isJumporBranch;
  uint32_t rstPc;
  struct FReg {
    // Control Signals
    bool bubble;
    uint32_t stall;

    uint32_t pc;
    uint32_t inst;
    uint32_t len;
  } fReg, fRegNew, decodeWho;
  struct DReg {
    // Control Signals
    bool bubble;
    uint32_t stall;
    RISCV::RegId rs1, rs2, rs3;

    uint32_t pc;
    RISCV::Inst inst;
    int32_t op1;
    int32_t op2;
    int32_t op3;
    RISCV::RegId dest;
    int32_t offset;
    bool predictedBranch;
    uint32_t predictedPC; // for branch prediction module, predicted PC destination
    uint32_t anotherPC;   // another possible prediction destination
  } dReg, dRegNew;
  struct EReg {
    // Control Signals
    bool bubble;
    uint32_t stall;

    uint32_t pc;
    RISCV::Inst inst;
    int32_t op1;
    int32_t op2;
    int32_t op3;
    bool writeReg;
    RISCV::RegId destReg;
    int32_t out;
    bool writeMem;
    bool readMem;
    bool readSignExt;
    uint32_t memLen;
    bool branch;
  } eReg, eRegNew;
  struct MReg {
    // Control Signals
    bool bubble;
    uint32_t stall;

    uint32_t pc;
    RISCV::Inst inst;
    int32_t op1;
    int32_t op2;
    int32_t op3;
    int32_t out;
    bool writeReg;
    RISCV::RegId destReg;
  } mReg, mRegNew;

  // Pipeline Related Variables
  // To avoid older values(in MEM) overriding newer values(in EX)
  bool executeWriteBack;
  RISCV::RegId executeWBReg;
  bool memoryWriteBack;
  RISCV::RegId memoryWBReg;

  struct History {
    uint32_t instCount;
    uint32_t cycleCount;
    uint32_t stalledCycleCount;

    uint32_t predictedBranch; // Number of branch that is predicted successfully
    uint32_t unpredictedBranch; // Number of branch that is not predicted
                                // successfully

    uint32_t dataHazardCount;
    uint32_t controlHazardCount;
    uint32_t memoryHazardCount;

    std::vector<std::string> instRecord;
    std::vector<std::string> regRecord;

    std::string memoryDump;
  } history;

  void fetch();
  void decode();
  void excecute();
  void memoryAccess();
  void writeBack();

  int32_t handleSystemCall(int32_t op1, int32_t op2);

  std::string getRegInfoStr();
  void panic(const char *format, ...);
};

#endif
