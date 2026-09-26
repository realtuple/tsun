#include <iostream>
#include <fstream>
#include <string>

namespace {

std::string read_file(std::string_view path) {
  std::ifstream file(std::string{path}.data());
  std::string   utf8_str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  return utf8_str;
}

}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Invalid arguments\n";
    return 1;
  }

  // NOLINTNEXTLINE
  std::string code = read_file(argv[1]);
}
