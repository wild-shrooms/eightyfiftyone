#include "disassembler.hpp"
#include <iostream>
#include <string_view>

namespace disassembler {
void display_help_msg() { std::cout << help_message << std::endl; }
} // namespace disassembler