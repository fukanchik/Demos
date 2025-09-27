#include <iostream>

int
main()
{
  int i=42;
  using foo = int;
  std::cout << i << std::endl;
  i.~foo();
  std::cout << i << std::endl;
  return 0;
}
