#pragma once

#include <filesystem>
#include <mutex>
#include <optional>
#include <queue>

class Queue {
 public:
  Queue() = default;
  void push(std::filesystem::path path);
  std::optional<std::filesystem::path> pop();

 private:
  Queue(const Queue&) = delete;
  Queue& operator=(const Queue&) = delete;
  Queue(Queue&&) = delete;
  Queue& operator=(Queue&&) = delete;

  std::queue<std::filesystem::path> queue_;
  std::mutex mtx_;
};
