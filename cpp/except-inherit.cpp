#include <iostream>
#include <stdexcept>

struct e1 : std::exception {};
struct e2 : std::exception {};
struct e3 : e1, e2 {};
struct e4 : virtual e1, e2 {};

int main() {
  try {
    throw e3();
  } catch (std::exception &e) {
    std::cerr << "Handler 1" << std::endl;
  } catch (...) {
    std::cerr << "Handler 2" << std::endl;
  }

  try {
	  throw e4();
  } catch (std::exception &e) {
    std::cerr << "Handler 3" << std::endl;
  } catch (...) {
    std::cerr << "Handler 4" << std::endl;
  }
}
