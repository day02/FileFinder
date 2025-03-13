#pragma once

#include <atomic>
#include <functional>

#include "thread_pool.h"

class Terminal {
 public:
  using DumpCB = std::function<void()>;
  using QuitCB = std::function<void()>;

  explicit Terminal(DumpCB dump_cb, QuitCB quit_cb, const int timeout_sec = 2);

  void listen(const StopToken& stop_flag) const;

 private:
  bool run() const;

  DumpCB dump_cb_;
  QuitCB quit_cb_;
  int timeout_sec_;
};
