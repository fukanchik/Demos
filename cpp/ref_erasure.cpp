#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct A
{
A(){
cout << "A::A()" << endl;
}
A(const A&other)
:v{other.v}
{
cout << "A::A(const A&)" << endl;
}
A&operator=(const A&other)
{
cout << "A::operator=(constA&)" << endl;
v=other.v;
return *this;
}
int v = 12;
};

A& foo()
{
  static A ret;

  return ret;
}

int main(){
  auto x1 = foo();
  auto& x2 = foo();
  cout << "auto x1=foo(); is reference: "<<std::is_reference<decltype(x1)>::value << " type name=" << typeid(x1).name() << endl;
  cout << "auto& x2=foo(); is reference: "<<std::is_reference<decltype(x2)>::value << " type name=" << typeid(x2).name() << endl;
}
