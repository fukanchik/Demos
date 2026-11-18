#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A {
  A() { cout << "A::A()" << endl; }
  A(const A &other) : v{other.v} { cout << "A::A(const A&)" << endl; }
  A &operator=(const A &other) {
    cout << "A::operator=(constA&)" << endl;
    v = other.v;
    return *this;
  }
  int v = 12;
};

A &foo() {
  static A ret;

  return ret;
}

template <typename T> std::string is_ref_msg() {
  const bool is_ref = std::is_reference<T>::value;

  if (is_ref)
    return "is a reference";

  return "is not a reference";
}

int main() {
  auto x1 = foo();
  auto &x2 = foo();

  cout << "auto x1=foo(); is a reference: " << is_ref_msg<decltype(x1)>()
       << " type name=" << typeid(x1).name() << endl;
  cout << "auto& x2=foo(); is a reference: " << is_ref_msg<decltype(x2)>()
       << " type name=" << typeid(x2).name() << endl;
}
