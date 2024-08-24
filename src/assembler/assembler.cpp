/* https://www.win.tue.nl/~aeb/comp/8051/set8051.html#51mov */

#include "assembler/assembler.hpp"
#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

enum InstructionSet {
  NOP,
  AJMP_PAGE0,
  LJMP_CODE_ADDR,
  ROTATE_RIGHT_A,
  INC_REGISTER,
  INC_ADDR,
  INC_INDIRECT_R0,
  INC_INDIRECT_R1,
  INC_R0,
  INC_R1,
  INC_R2,
  INC_R3,
  INC_R4,
  INC_R5,
  INC_R6,
  INC_R7,
  JBC_ADDR_REL_ADDR,
  ACALL_PAGE0,
  LCALL_CODE_ADDR,
  ROTATE_RIGHT_CARRY_A,
  DEC_A,
  DEC_ADDR,
  DEC_INDIRECT_R0,
  DEC_INDIRECT_R1,
  DEC_R0,
  DEC_R1,
  DEC_R2,
  DEC_R3,
  DEC_R4,
  DEC_R5,
  DEC_R6,
  DEC_R7,
  JB_ADDR_REL_ADDR,
  AJMP_PAGE1,
  RET,
  ROTATE_LEFT_A,
  ADD_A_DATA,
  ADD_A_ADDR,
  ADD_A_INDIRECT_R0,
  ADD_A_INDIRECT_R1,
  ADD_A_R0,
  ADD_A_R1,
  ADD_A_R2,
  ADD_A_R3,
  ADD_A_R4,
  ADD_A_R5,
  ADD_A_R6,
  ADD_A_R7,
  JNB_ADDR_REL_ADDR,
  ACALL_PAGE1,
  RETI,
  ROTATE_LEFT_CARRY_A,
  ADDC_A_DATA,
  ADDC_A_ADDR,
  ADDC_A_INDIRECT_R0,
  ADDC_A_INDIRECT_R1,
  ADDC_A_R0,
  ADDC_A_R1,
  ADDC_A_R2,
  ADDC_A_R3,
  ADDC_A_R4,
  ADDC_A_R5,
  ADDC_A_R6,
  ADDC_A_R7,
  JC_ADDR_REL_ADDR,
  AJMP_PAGE2,
  ORL_ADDR_A,
  ORL_ADDR_DATA,
  ORL_A_ADDR,
  ORL_A_INDIRECT_R0,
  ORL_A_INDIRECT_R1,
  ORL_A_R0,
  ORL_A_R1,
  ORL_A_R2,
  ORL_A_R3,
  ORL_A_R4,
  ORL_A_R5,
  ORL_A_R6,
  ORL_A_R7,
  JNC_REL_ADDR,
  ACALL_PAGE2,
  ANL_ADDR_A,
  ANL_ADDR_DATA,
  ANL_A_ADDR,
  ANL_A_INDIRECT_R0,
  ANL_A_INDIRECT_R1,
  ANL_A_R0,
  ANL_A_R1,
  ANL_A_R2,
  ANL_A_R3,
  ANL_A_R4,
  ANL_A_R5,
  ANL_A_R6,
  ANL_A_R7,
  JZ_REL_ADDR,
  AJMP_PAGE3,
  XRL_ADDR_A,
  XRL_ADDR_DATA,
  XRL_A_ADDR,
  XRL_A_INDIRECT_R0,
  XRL_A_INDIRECT_R1,
  XRL_A_R0,
  XRL_A_R1,
  XRL_A_R2,
  XRL_A_R3,
  XRL_A_R4,
  XRL_A_R5,
  XRL_A_R6,
  XRL_A_R7,
  JNZ_REL_ADDR,
  ACALL_PAGE3,
  ORL_C_BIT_ADDR,
  MOV_A_DATA,
  MOV_ADDR_DATA,
  MOV_INDIRECT_R0_DATA,
  MOV_INDIRECT_R1_DATA,
  MOV_R0_DATA,
  MOV_R1_DATA,
  MOV_R2_DATA,
  MOV_R3_DATA,
  MOV_R4_DATA,
  MOV_R5_DATA,
  MOV_R6_DATA,
  MOV_R7_DATA,
  SJMP_REL_ADDR,
  AJMP_PAGE4,
  ANL_C_BIT_ADDR,
  MOVC_A_INDIRECT_A_PC,
  DIV_AB,
  MOV_ADDR_ADDR,
  MOV_ADDR_INDIRECT_R0,
  MOV_ADDR_INDIRECT_R1,
  MOV_ADDR_R0,
  MOV_ADDR_R1,
  MOV_ADDR_R2,
  MOV_ADDR_R3,
  MOV_ADDR_R4,
  MOV_ADDR_R5,
  MOV_ADDR_R6,
  MOV_ADDR_R7,
  MOV_DPTR_DATA16,
  ACALL_PAGE4,
  MOV_BIT_ADDR_C,
  MOVC_A_INDIRECT_A_DPTR,
  SUBB_A_DATA,
  SUBB_A_ADDR,
  SUBB_A_INDIRECT_R0,
  SUBB_A_INDIRECT_R1,
  SUBB_A_R0,
  SUBB_A_R1,
  SUBB_A_R2,
  SUBB_A_R3,
  SUBB_A_R4,
  SUBB_A_R5,
  SUBB_A_R6,
  SUBB_A_R7,
  ORL_C_COMPL_BIT_ADDR,
  AJMP_PAGE5,
  MOV_C_BIT_ADDR,
  INC_DPTR,
  MUL_AB,
  MOV_INDIRECT_R0_ADDR,
  MOV_INDIRECT_R1_ADDR,
  MOV_R0_ADDR,
  MOV_R1_ADDR,
  MOV_R2_ADDR,
  MOV_R3_ADDR,
  MOV_R4_ADDR,
  MOV_R5_ADDR,
  MOV_R6_ADDR,
  MOV_R7_ADDR,
  ANL_C_COMPL_BIT_ADDR,
  ACALL_PAGE5,
  CPL_BIT_ADDR,
  CPL_C,
  CJNE_A_DATA_REL_ADDR,
  CJNE_A_ADDR_REL_ADDR,
  CJNE_INDIRECT_R0_DATA_REL_ADDR,
  CJNE_INDIRECT_R1_DATA_REL_ADDR,
  CJNE_R0_DATA_REL_ADDR,
  CJNE_R1_DATA_REL_ADDR,
  CJNE_R2_DATA_REL_ADDR,
  CJNE_R3_DATA_REL_ADDR,
  CJNE_R4_DATA_REL_ADDR,
  CJNE_R5_DATA_REL_ADDR,
  CJNE_R6_DATA_REL_ADDR,
  CJNE_R7_DATA_REL_ADDR,
  PUSH_ADDR,
  AJMP_PAGE6,
  CLR_BIT_ADDR,
  CLR_C,
  SWAP_A,
  XCH_A_INDIRECT_R0,
  XCH_A_INDIRECT_R1,
  XCH_A_R0,
  XCH_A_R1,
  XCH_A_R2,
  XCH_A_R3,
  XCH_A_R4,
  XCH_A_R5,
  XCH_A_R6,
  XCH_A_R7,
  POP_ADDR,
  ACALL_PAGE6,
  SETB_BIT_ADDR,
  SETB_C,
  DA,
  DJNZ_ADDR_REL_ADDR,
  XCHD_A_INDIRECT_R0,
  XCHD_A_INDIRECT_R1,
  DJNZ_R0_REL_ADDR,
  DJNZ_R1_REL_ADDR,
  DJNZ_R2_REL_ADDR,
  DJNZ_R3_REL_ADDR,
  DJNZ_R4_REL_ADDR,
  DJNZ_R5_REL_ADDR,
  DJNZ_R6_REL_ADDR,
  DJNZ_R7_REL_ADDR,
  MOVX_A_INDIRECT_DPTR,
  AJMP_PAGE7,
  MOVX_A_INDIRECT_R0,
  MOVX_A_INDIRECT_R1,
  CLR_A,
  MOV_A_ADDR,
  MOV_A_INDIRECT_R0,
  MOV_A_INDIRECT_R1,
  MOV_A_R0,
  MOV_A_R1,
  MOV_A_R2,
  MOV_A_R3,
  MOV_A_R4,
  MOV_A_R5,
  MOV_A_R6,
  MOV_A_R7,
  MOVX_INDIRECT_DPTR_A,
  ACALL_PAGE7,
  MOVX_INDIRECT_R0_A,
  MOVX_INDIRECT_R1_A,
  CPL_A,
  MOV_ADDR_A,
  MOV_INDIRECT_R0_A,
  MOV_INDIRECT_R1_A,
  MOV_R0_A,
  MOV_R1_A,
  MOV_R2_A,
  MOV_R3_A,
  MOV_R4_A,
  MOV_R5_A,
  MOV_R6_A,
  MOV_R7_A,
};

namespace {
std::vector<std::string> tokenize(const std::string &source) {
  std::vector<std::string> tokens{};
  std::string sub{};
  for (char c : source) {
    if (c == ' ' || c == ',') {
      tokens.push_back(sub);
      sub.clear();
    } else {
      sub.append(1, c);
    }
  }
  tokens.push_back(sub);

  return tokens;
}

std::string handle_id(const std::string &s, size_t &idx) {
  std::string id{};
  for (; idx < s.size(); idx++) {
    if (s.at(idx) == ',' || isspace(s.at(idx))) {
      break;
    }
    id.append(1, s.at(idx));
  }
  return id;
}

std::string handle_digit(const std::string &s, size_t &idx) {
  std::string value{};
  for (; idx < s.size(); idx++) {
    if (!isdigit(s.at(idx)) || isspace(s.at(idx))) {
      break;
    }
    value.append(1, s.at(idx));
  }

  return value;
}

std::string handle_literal(const std::string &s, size_t &idx) {
  std::string literal{};
  literal.append(1, s.at(idx++));
  for (; idx < s.size(); idx++) {
    if (!isdigit(s.at(idx))) {
      if (s.at(idx) == 'h' || s.at(idx) == 'b') {
        literal.append(1, s.at(idx));
      }
      break;
    }
    literal.append(1, s.at(idx));
  }

  return literal;
}

} // namespace

namespace assembler {
struct Instruction {
  std::string op{};
  std::string first{};
  std::string second{};
  std::string third{};

  std::string str() {
    return std::format("op: '{}', 1: '{}', 2: '{}', 3: '{}'", op, first, second,
                       third);
  }
};

void display_help_message() { std::cout << help_message << std::endl; }

void assemble(const std::filesystem::path &in,
              const std::filesystem::path &out) {
  std::filesystem::path input_file_path{};
  std::filesystem::path output_file_path{};
  input_file_path = in;
  if (out.empty()) {
    output_file_path = "out.bin";
  } else {
    output_file_path = out;
  }

  if (!std::filesystem::exists(input_file_path)) {
    throw std::runtime_error(
        std::format("'{}' does not exist.", input_file_path.c_str()));
  }

  std::vector<uint8_t> binary_output{};

  std::ifstream input_file{input_file_path};
  size_t line_number{1};
  for (std::string line{}; std::getline(input_file, line); line_number++) {
    std::transform(line.begin(), line.end(), line.begin(), tolower);
    Instruction instruction{};
    for (size_t i{}; i < line.size(); i++) {
      if (isalpha(line.at(i))) {
        if (instruction.op.empty()) {
          instruction.op = handle_id(line, i);
        } else if (instruction.first.empty()) {
          instruction.first = handle_id(line, i);
        } else if (instruction.second.empty()) {
          instruction.second = handle_id(line, i);
        } else if (instruction.third.empty()) {
          instruction.third = handle_id(line, i);
        }
      } else if (isdigit(line.at(i))) {
        if (instruction.first.empty()) {
          instruction.first = handle_digit(line, i);
        } else if (instruction.second.empty()) {
          instruction.second = handle_digit(line, i);
        } else if (instruction.third.empty()) {
          instruction.second = handle_digit(line, i);
        }
      } else if (line.at(i) == '#') {
        if (instruction.first.empty()) {
          throw std::runtime_error(
              std::format("{}: ({}:{}), Expected register or memory address.",
                          in.c_str(), line_number, i));
        }
        if (instruction.second.empty()) {
          instruction.second = handle_literal(line, i);
        } else if (instruction.third.empty()) {
          instruction.second = handle_literal(line, i);
        }
      }
    }

    // std::cout << instruction.str() << std::endl;
    // exit(7);

    if (instruction.op == "mov") {
      if (instruction.first == "a") {
        if (instruction.second.at(0) == '#') {
          binary_output.push_back(MOV_A_DATA);
          instruction.second.erase(instruction.second.begin());
          char suffix = *(instruction.second.end() - 1);
          uint8_t value{};
          if (isalpha(suffix)) {
            instruction.second.pop_back();
            if (suffix == 'h') {
              value = std::stoull(instruction.second, 0, 16);
            } else if (suffix == 'b') {
              value = std::stoull(instruction.second, 0, 2);
            }
          } else {
            value = std::stoull(instruction.second, 0, 10);
          }
          binary_output.push_back(value);
        } else if (instruction.second == "r0") {
          binary_output.push_back(MOV_A_R0);
        } else if (instruction.second == "r1") {
          binary_output.push_back(MOV_A_R1);
        } else if (instruction.second == "r2") {
          binary_output.push_back(MOV_A_R2);
        } else if (instruction.second == "r3") {
          binary_output.push_back(MOV_A_R3);
        } else if (instruction.second == "r4") {
          binary_output.push_back(MOV_A_R4);
        } else if (instruction.second == "r5") {
          binary_output.push_back(MOV_A_R5);
        } else if (instruction.second == "r6") {
          binary_output.push_back(MOV_A_R6);
        } else if (instruction.second == "r7") {
          binary_output.push_back(MOV_A_R7);
        }
      }
    }
  }

  for (auto instruction : binary_output) {
    std::cout << std::hex << (int)(instruction) << std::endl;
  }
}

} // namespace assembler