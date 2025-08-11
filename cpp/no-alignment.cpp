/* g++/clang++ intrinsics do not align on x86. This fails on strlen. */
#include <string>

int main() {
  __asm__("pushf\norl $0x40000,(%rsp)\npopf");

  std::string s{"asdf"};

  return 0;
}
