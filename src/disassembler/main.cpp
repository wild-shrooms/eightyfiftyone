#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <Disassembler.hpp>

std::vector<std::string> parse_args(int32_t argc, char **argv) {
  std::vector<std::string> args{};
  argc--;
  argv++;

  for (int32_t i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  return args;
}

int main(int argc, char **argv) {
  std::vector<std::string> args = parse_args(argc, argv);
  for (const auto &arg : args) {
    std::cout << arg << std::endl;
  }

  for (std::size_t i{}; i < args.size(); i++) {
    auto current_arg{args.at(i)};
    for (std::size_t j{}; j < current_arg.size(); j++) {
      if(current_arg.at(j++) == '-'){
        if(current_arg.at(j) == '-'){
          j++;
          if(current_arg.substr(j) =="help"){ 
            Disassembler::display_help_msg(); 
          }
        }
      }
    }
  }
  return 0;
}
