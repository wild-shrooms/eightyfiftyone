#pragma once

#include <cstdint>
#include <string>
#include <vector>

class assembler {
public:
  assembler(const std::string &src_code);
  void tokenize();
  void parser();
  void generate_opcode();
  void write_output(const std::string &output_file);

  void error(const std::string &message);

private:
  std::string m_src_code{};
  std::vector<std::string> tokens{};
  std::vector<std::string> instructions{};
  std::vector<uint8_t> machine_code{};
};