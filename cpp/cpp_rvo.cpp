#include <iostream>

using namespace std;

class A
{
public:
  int x;
  A(int a) { x=a; cout << "A::A()" << endl; }
  ~A() { cout << "A::~A("<<x<<")" << endl; }
  A&operator=(const A&a)
  {
    cout << "A::operator=(&)" << endl;
    x=a.x;
    return *this;
  }
  A&operator=(A&&a)
  {
    cout << "A::operator=(&&)" << endl;
    x=a.x;
    return *this;
  }
  A(const A&a)
  {
    x=a.x;
    cout << "A::A(&)" << endl;
  }
  A(A&&a)
  {
    x=a.x;
    cout << "A::A(&&)" << endl;
  }
};

A non_rvo(int a)
{
  cout << "non rvo" << endl;
  return std::move(A(a));
}

A rvo(int a)
{
  cout << "rvo" << endl;
  return A(a);
}

int main(int c, char *v[])
{
    A a = non_rvo(42);
    A b = rvo(16);
    cout << a.x << " " << b.x << endl;
    return 0;
}
