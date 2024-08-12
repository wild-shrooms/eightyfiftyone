#pragma once

#include <filesystem>

namespace assembler {

constexpr std::string_view help_message{
    "Assembler for the 8051 architecture\n"
    "Usage: 8051-assembler [file] [options]\n"
    "Arguments:\n"
    "\t-h, --help\t\tDisplay the help message.\n"
    "\t-o, --output\t\tOutput binary to specified file.\n"};

void display_help_message();
void assemble(const std::filesystem::path &in,
              const std::filesystem::path &out);
} // namespace assembler