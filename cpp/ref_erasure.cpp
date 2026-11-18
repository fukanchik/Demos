// requires c++14 b/c of decltype(auto)
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>

struct A {
  A() { std::cout << "A::A()" << std::endl; }
  A(const A &) { std::cout << "A::A(const A&)" << std::endl; }

  A &operator=(const A &) = delete;
  A &operator=(A &&) = delete;
};

struct B {
  B() { std::cout << "B::B()" << std::endl; }
  B(const B &) { std::cout << "B::B(const B&)" << std::endl; }

  B &operator=(const B &) = delete;
  B &operator=(B &&) = delete;
};

A &foo() {
  static A ret;

  return ret;
}

B bar() { return {}; }

template <typename T> std::string is_ref_msg() {
  if (std::is_reference<T>::value)
    return "is a reference";

  return "is not a reference";
}

template <typename T> std::string ref_type_name() {
  using U = std::remove_reference_t<T>;

  std::string ret;

  if (std::is_const<U>::value)
    ret += "const ";

  if (std::is_lvalue_reference<T>::value)
    ret += "ref ";
  else if (std::is_rvalue_reference<T>::value)
    ret += "rvalue ref ";

  ret += typeid(U).name();

  return ret;
}

#define SHOW(decl, var)                                                        \
  decl;                                                                        \
  std::cout << #decl ": " << is_ref_msg<decltype(var)>() << ", type name "     \
            << ref_type_name<decltype(var)>() << std::endl

int main() {
  SHOW(auto x1 = foo(), x1);
  SHOW(auto &x2 = foo(), x2);
  SHOW(decltype(auto) x3 = foo(), x3);
  // not an rvalue ref b/c auto&& collapses into A& since foo() returns lvalue
  // i.e. forwarding ref + lvalue -> A&.
  SHOW(auto &&x4 = foo(), x4);
  SHOW(const auto x5 = foo(), x5);
  SHOW(const auto &x6 = foo(), x6);
  // forwarding ref + rvalue -> B&& (lifetime of temporary extended)
  SHOW(auto &&x7 = bar(), x7);
  // `const auto &&` is a plain rvalue ref,
  // not a forwarding ref: binds rvalue only
  SHOW(const auto &&x8 = bar(), x8);

  return 0;
}
