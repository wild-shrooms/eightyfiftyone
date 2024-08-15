#include "assembler/assembler.hpp"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

std::optional<std::string> is_prefixed_with(const std::string &prefix,
                                            const std::string &str) {
  if (str.substr(0, prefix.size()) == prefix) {
    return str.substr(prefix.size());
  }
  return std::nullopt;
}

std::vector<std::string> shift_args(int32_t argc, char **argv) {
  std::vector<std::string> args{};
  argc--;
  argv++;

  for (int32_t i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  return args;
}

int main(int argc, char **argv) {
  std::vector<std::string> args = shift_args(argc, argv);

  std::filesystem::path input_file{};
  std::filesystem::path output_file{};

  for (std::size_t i{}; i < args.size(); i++) {
    auto current_arg{args.at(i)};
    if (is_prefixed_with("--", current_arg) == "help" ||
        is_prefixed_with("-", current_arg) == "h") {
      assembler::display_help_message();
      return EXIT_SUCCESS;
    } else if (is_prefixed_with("--", current_arg) == "output" ||
               is_prefixed_with("-", current_arg) == "o") {
      if (input_file.empty()) {
        std::cerr << "No input file specified." << std::endl;
        return EXIT_FAILURE;
      }
      if (i == args.size() - 1) {
        std::cerr << "Expected filename." << std::endl;
        return EXIT_FAILURE;
      } else {
        i++;
        if (output_file.empty()) {
          output_file = args.at(i);
        } else {
          std::cerr << "Cannot specify two output files." << std::endl;
          return EXIT_FAILURE;
        }
      }
    } else {
      if (input_file.empty()) {
        input_file = current_arg;
      } else {
        std::cerr << "Cannot specify two input files." << std::endl;
        return EXIT_FAILURE;
      }
    }
  }

  try {
    assembler::assemble(input_file, output_file);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}