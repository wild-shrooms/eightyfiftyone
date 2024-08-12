#include "assembler/assembler.hpp"
#include <iostream>

namespace assembler {
void display_help_message() { std::cout << help_message << std::endl; }

void assemble(const std::filesystem::path &in) {}

void assemble(const std::filesystem::path &in,
              const std::filesystem::path &out) {}
} // namespace assembler