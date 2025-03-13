
#include <iostream>

#include "scheduler.h"

namespace fs = std::filesystem;

int usage() {
  std::cerr << "Usage: file-finder <dir> <substring1>[<substring2> "
               "[<substring3>]...]\n";
  return EXIT_FAILURE;
}

fs::path parseRootFolder(char* argv[]) {
  fs::path dir(argv[1]);
  std::cout << "Root Folder: " << dir << "\n";
  return dir;
}

Tokens parseTokens(int argc, char* argv[]) {
  Tokens tokens(argv + 2, argv + argc);

  std::cout << "Tokens: ";
  for (const auto& token : tokens) {
    std::cout << token << ", ";
  }
  std::cout << "\n";

  return tokens;
}

bool isValid(const fs::path& dir) {
  std::error_code ec;
  return fs::exists(dir, ec) && !ec && fs::is_directory(dir, ec) && !ec;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    return usage();
  }

  auto dir = parseRootFolder(argv);
  if (!isValid(dir)) {
    std::cerr << "Error: Invalid directory path: " << dir << "\n";
    return EXIT_FAILURE;
  }
  Scheduler{std::move(dir), parseTokens(argc, argv)}.waitTillCompletion();
  return EXIT_SUCCESS;
}
