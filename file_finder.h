#pragma once

#include <string>

#include "queue.h"
#include "thread_pool.h"

using Token = std::string;
using Tokens = std::vector<Token>;

class FileFinder {
 public:
  explicit FileFinder(std::filesystem::path dir, Tokens tokens);
  ~FileFinder();

  void dump();
  void quit();
  void waitTillCompletion();

 private:
  FileFinder(const FileFinder&) = delete;
  FileFinder& operator=(const FileFinder&) = delete;
  FileFinder(FileFinder&&) = delete;
  FileFinder& operator=(FileFinder&&) = delete;

  std::filesystem::path dir_;
  Tokens tokens_;
  Queue queue_;
  ThreadPool workers_;
};
