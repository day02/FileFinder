
#include <iostream>
#include <unistd.h>

#include "terminal.h"

enum class Action {
  Dump,
  Quit,
  Invalid,
};

namespace {

Action getAction(const char input) {
  switch (input) {
  case 'd':
    std::cout << "Dumping data...\n";
    return Action::Dump;
  case 'q':
    std::cout << "Quitting...\n";
    return Action::Quit;
  default:
    std::cout << "Invalid argument... \n";
    return Action::Invalid;
  }
}

bool waitForUserInterrupt(const int timeout_sec) {
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);

  struct timeval tv;
  tv.tv_sec = timeout_sec;
  tv.tv_usec = 0;

  return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

char getUserInput() {
  std::string input;
  std::getline(std::cin, input);
  return (!input.empty()) ? input[0] : ' ';
}

Action waitForUserInput(const int timeout_sec) {
  if (waitForUserInterrupt(timeout_sec)) {
    return getAction(getUserInput());
  } else {
    std::cout << "Timeout! Dumping data...\n";
    return Action::Dump;
  }
}

} // namespace

Terminal::Terminal(DumpCB dump_cb, QuitCB quit_cb, const int timeout_sec)
    : dump_cb_(std::move(dump_cb)),
      quit_cb_(std::move(quit_cb)),
      timeout_sec_(timeout_sec) {}

void Terminal::listen(const StopToken& stop_flag) const {
  while (run() && !stop_flag) {
    // forever
  };
}

bool Terminal::run() const {
  std::cout << "\nEnter 'q' to quit, 'd' to dump (timeout: " << timeout_sec_
            << " sec): \n";
  switch (const auto action = waitForUserInput(timeout_sec_); action) {
  case Action::Dump:
    dump_cb_();
    return true;
  case Action::Quit:
    quit_cb_();
    return false;
  case Action::Invalid:
  default:
    return true;
  }
}
