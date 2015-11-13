#include <string>
#include <iostream>
#include <memory>

class A
{
public:
  A() : str("hello"){}
  ~A(){
    std::cout << "A::~A()" << std::endl;
  }
  void bar()
  {
    std::cout << "A::bar()" << std::endl;
  }

  std::string str;
};

A*foo()
{
  return new A;
}

void bar(const std::auto_ptr<A>&a)
{
  a->bar();
}
