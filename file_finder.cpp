
#include <algorithm>
#include <iostream>

#include "file_finder.h"

namespace fs = std::filesystem;

namespace {

bool isMatch(const fs::path& path, const Token& token) {
  return path.filename().string() == token;
}

void search(const StopToken& stop_flag,
            const fs::path& dir,
            const Token& token,
            Queue& queue_) {
  std::error_code ec;
  for (const auto& entry : fs::recursive_directory_iterator(dir, ec)) {
    if (stop_flag) {
      return;
    }
    if (!ec && entry.is_regular_file(ec)) {
      if (auto path = entry.path(); !ec && isMatch(path, token)) {
        queue_.push(std::move(path));
      }
    }
  }
  if (ec) {
    std::cerr << "Error: Failed to crawl the dir with error: " << ec << "\n";
  }
  std::cout << "Scan Completed for token: " << token << "\n";
}

} // namespace

FileFinder::FileFinder(fs::path dir, Tokens tokens)
    : dir_(std::move(dir)),
      tokens_(std::move(tokens)),
      queue_(),
      workers_(
          [this](const StopToken& stop_flag, const size_t index) {
            search(stop_flag, dir_, tokens_[index], queue_);
          },
          tokens_.size()) {}

FileFinder::~FileFinder() {
  quit();
}

void FileFinder::dump() {
  while (auto path = queue_.pop()) {
    std::cout << "Token Matched: " << *path << "\n";
  }
}

void FileFinder::quit() {
  workers_.stop();
  dump();
}

void FileFinder::waitTillCompletion() {
  workers_.wait();
  dump();
}
