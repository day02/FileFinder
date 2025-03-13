
#include "thread_pool.h"

ThreadPool::ThreadPool(const TaskFn task_fn, const size_t thread_count)
    : stop_flag_(false) {
  for (size_t index = 0; index < thread_count; ++index) {
    threads_.emplace_back(task_fn, std::ref(stop_flag_), index);
  }
}

ThreadPool::~ThreadPool() {
  stop();
}

void ThreadPool::stop() {
  stop_flag_ = true;
  wait();
}

void ThreadPool::wait() {
  std::lock_guard<std::mutex> lock(mtx_);
  for (auto& thread : threads_) {
    if (thread.joinable()) {
      thread.join();
    }
  }
  threads_.clear();
}
