#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

using StopToken = std::atomic<bool>;

class ThreadPool {
 public:
  using TaskFn = std::function<void(const StopToken&, const size_t)>;

  explicit ThreadPool(const TaskFn task_fn, const size_t thread_count = 1);
  ~ThreadPool();

  void stop();
  void wait();

 private:
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;
  ThreadPool(ThreadPool&&) = delete;
  ThreadPool& operator=(ThreadPool&&) = delete;

  StopToken stop_flag_;
  std::vector<std::thread> threads_;
  std::mutex mtx_;
};
