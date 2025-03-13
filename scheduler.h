#pragma once

#include "file_finder.h"

class Scheduler {
 public:
  explicit Scheduler(std::filesystem::path dir, Tokens tokens);
  ~Scheduler();

  void waitTillCompletion();

 private:
  Scheduler(const Scheduler&) = delete;
  Scheduler& operator=(const Scheduler&) = delete;
  Scheduler(Scheduler&&) = delete;
  Scheduler& operator=(Scheduler&&) = delete;

  FileFinder file_finder_;
  ThreadPool terminal_worker_;
};
