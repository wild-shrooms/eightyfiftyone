#pragma once

#include <string>

namespace disassembler {

constexpr std::string_view help_message{
    "Disassembler for the 8051 architecture\n"
    "Usage: disassembler [options] [file]\n"
    "Arguments:\n"
    "\t-h, --help\t\t\tDisplay the help message.\n"
    "\t-d, --disassemble <file>\tDisassemble the specified file."
    };


void display_help_msg();
} // namespace disassembler