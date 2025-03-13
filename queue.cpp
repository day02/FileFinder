
#include "queue.h"

void Queue::push(std::filesystem::path path) {
  std::lock_guard<std::mutex> lock(mtx_);
  queue_.push(std::move(path));
}

std::optional<std::filesystem::path> Queue::pop() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (queue_.empty()) {
    return std::nullopt;
  }

  auto path = std::make_optional(std::move(queue_.front()));
  queue_.pop();
  return path;
}
