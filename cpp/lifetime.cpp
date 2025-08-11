/* Demo various aspects of c++ object lifetime. */
#include <iostream>

static int object_identity_counter = 0;

struct A {
  int num_created;
  A() : num_created{object_identity_counter} {
    std::cout << "A::A(" << num_created << ")" << std::endl;
    object_identity_counter++;
  }
  A(const A &other) : num_created{object_identity_counter} {
    std::cout << "A::A(const A&other=" << other.num_created
              << ", me=" << num_created << ")" << std::endl;
    object_identity_counter++;

    throw 1;
  }
  ~A() { std::cout << "A::~A(" << num_created << ")" << std::endl; }
};

int main(int c, char *v[]) {
  try {
    A a;
    A b = a;
  } catch (...) {
    std::cout << "Exception" << std::endl;
  }
  return 0;
}
