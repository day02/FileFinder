
#include "scheduler.h"
#include "terminal.h"

Scheduler::Scheduler(std::filesystem::path dir, Tokens tokens)
    : file_finder_(std::move(dir), std::move(tokens)),
      terminal_worker_([this](const StopToken& stop_flag, const size_t) {
        Terminal{[this]() { file_finder_.dump(); },
                 [this]() { file_finder_.quit(); }}
            .listen(stop_flag);
      }) {}

Scheduler::~Scheduler() {
  waitTillCompletion();
  terminal_worker_.stop();
}

void Scheduler::waitTillCompletion() {
  file_finder_.waitTillCompletion();
}
