/* memset(&object,...) destroys vtbl. */
#include <iostream>
#include <cstring>

struct A
{
  virtual void foo();
  virtual ~A();
};

void A::foo()
{
  std::cout << "A::foo()" << std::endl;
}

A::~A()
{
  std::cout << "A::~A()" << std::endl;
}

struct B final: A
{
  void foo() override;
  ~B() override;
};

void B::foo()
{
  std::cout << "B::foo()" << std::endl;
}

B::~B()
{
  std::cout << "B::~B()" << std::endl;
}

int
main(int argc, char *argv[])
{
  A* a = new B;

  memset(a, 0, sizeof(B));

  a->foo();
  return 0;
}
