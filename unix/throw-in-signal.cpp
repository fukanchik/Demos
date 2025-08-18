/* Throw exception from within a signal handler. */
#include <cstring>
#include <iostream>
#include <signal.h>
#include <unistd.h>

void signal_handler(int n) {
  ::write(1, "Signal handler\n", 6);
  throw 1;
}

int main() {

  struct sigaction sigIntHandler;
  memset(&sigIntHandler, 0, sizeof(struct sigaction));
  sigIntHandler.sa_handler = signal_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  try {
    pause();
  } catch (int v) {
    std::cerr << "VAL " << v << std::endl;
  }
  return 0;
}
