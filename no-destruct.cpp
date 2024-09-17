// If no matching handler is found, the function std::terminate() is called;
// whether or not the stack is unwound before this call to std::terminate()
// is implementation-defined (15.5.1).
#include <exception>
#include <iostream>
#include <memory>

class X {
  int x;

public:
  X(int a) : x(a) { std::cout << "X::X(" << x << ")" << std::endl; }
  ~X() { std::cout << "X::~X(" << x << ")" << std::endl; }
};

int main() {
  X x{42};
  std::unique_ptr p = std::make_unique<X>(11);
  throw std::exception();
}
