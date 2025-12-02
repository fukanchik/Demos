// https://softwareengineering.stackexchange.com/questions/384738/why-does-the-base-class-need-to-have-a-virtual-destructor-here-if-the-derived-cl
#include <iostream>

struct Parent
{
  virtual void foo() = 0;
  ~Parent()
  {
    std::cout << "Parent::~Parent()" << std::endl;
  }
};

struct ShouldBeDeleted
{
  int *leaks;
  ShouldBeDeleted() :leaks(new int){}
  ~ShouldBeDeleted()
  {
    delete leaks;
    std::cout << "ShouldBeDeleted::~ShouldBeDeleted(): " << std::endl;
  }
};

struct Derived: Parent
{
  ShouldBeDeleted should;
  void foo() override {std::cout << "Derived::foo()" << std::endl;}
  virtual ~Derived()
  {
    std::cout << "Derived::~Derived(): " << std::endl;
  }
};

int
main()
{
  std::cout << "First" << std::endl;
  Parent *obj1 = new Derived;
  obj1->foo();
  delete obj1;
  std::cout << "Second" << std::endl;
  Derived *obj2 = new Derived;
  obj2->foo();
  delete obj2;

  return 0;
}

