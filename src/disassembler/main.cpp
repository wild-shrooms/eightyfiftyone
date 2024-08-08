#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

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

  return 0;
}
