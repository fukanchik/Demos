/*
 * Return-value-optimization demo.
 *
 * Compare normal build and build with -fno-elide-constructors
 * `-std=c++17 -fno-elide-constructors -Wall -Wextra`
 * to see which elisions are guaranteed and which are optional.
 * -Wall warns about pessimized moves (it includes -Wpessimizing-move).
 *
 * for s in c++11 c++17; do
 *   g++ -std=$s rvo.cpp && ./a.out
 *   g++ -std=$s -fno-elide-constructors rvo.cpp && ./a.out
 * done
 * # only the intended -Wpessimizing-move warnings
 * g++ -std=c++17 -Wall -Wextra rvo.cpp
 *
 */
#include <iostream>
#include <utility>

class A {
public:
  int x;

  explicit A(int a) : x{a} { std::cout << "  A::A(" << a << ")" << std::endl; }

  ~A() { std::cout << "  A::~A(" << x << ")" << std::endl; }

  A(const A &a) : x{a.x} {
    std::cout << "  A::A(&a=" << a.x << ")" << std::endl;
  }

  A(A &&a) noexcept : x{a.x} {
    std::cout << "  A::A(&&a=" << a.x << ")" << std::endl;

    a.x = -1;
  }

  A &operator=(const A &a) {
    std::cout << "  A::operator=(&a=" << a.x << ")" << std::endl;

    x = a.x;

    return *this;
  }

  A &operator=(A &&a) noexcept {
    std::cout << "  A::operator=(&&a=" << a.x << ")" << std::endl;

    x = a.x;
    a.x = -1;

    return *this;
  }
};

static A rvo_prvalue(int a) {
  // normal build: ctor (optional)
  // c++11 no-elide: ctor, move, move
  // c++17 no-elide: ctor (guaranteed)
  return A(a);
}

static A pessimize_temporary(int a) {
  // normal build: ctor, move
  // c++11 no-elide: ctor, move, move
  // c++17 no-elide: ctor, move
  // clang warns about this, gcc does not
  return std::move(A(a));
}

static A pessimize_local(int a) {
  // normal build: ctor, move
  // c++11 no-elide: ctor, move, move
  // c++17 no-elide: ctor, move
  A ret{a};
  return std::move(ret);
}

static A nrvo(int a) {
  // normal build: ctor
  // c++11 no-elide: ctor, move, move
  // c++17 no-elide: ctor, move
  A ret{a};
  return ret;
}

static A no_nrvo_two_locals(bool val, int a) {
  // normal build: ctor, ctor, move
  // c++11 no-elide: ctor, ctor, move, move
  // c++17 no-elide: ctor, ctor, move
  A ret1{a};
  A ret2{a + 11};

  if (val)
    return ret1;
  else
    return ret2;
}

static A no_nrvo_ternary(bool val, int a) {
  // normal build: ctor, ctor, copy
  // c++11 no-elide: ctor, ctor, copy, move
  // c++17 no-elide: ctor, ctor, copy
  A ret1{a};
  A ret2{a + 11};

  return val ? ret1 : ret2;
}

static A no_nrvo_param(A p) {
  // normal build: ctor, move
  // c++11 no-elide: ctor, move, move, move
  // c++17 no-elide: ctor, move
  return p;
}

static A no_nrvo_ternary_move(bool val, int a) {
  // std::move turns the copy in no_nrvo_ternary into a move
  // normal build: ctor, ctor, move
  // c++11 no-elide: ctor, ctor, move, move
  // c++17 no-elide: ctor, ctor, move
  A ret1{a};
  A ret2{a + 11};

  return val ? std::move(ret1) : std::move(ret2);
}

static A no_nrvo_two_locals_move(bool val, int a) {
  // output is the same as no_nrvo_two_locals. std::move is redundant here
  // normal build: ctor, ctor, move
  // c++11 no-elide: ctor, ctor, move, move
  // c++17 no-elide: ctor, ctor, move
  A ret1{a};
  A ret2{a + 11};

  if (val)
    return std::move(ret1);
  else
    return std::move(ret2);
}

#define DEMO(...)                                                              \
  do {                                                                         \
    std::cout << "* " #__VA_ARGS__ << std::endl;                               \
    A demo_result = __VA_ARGS__;                                               \
    std::cout << "  result: " << demo_result.x << std::endl;                   \
  } while (0)

int main(int argc, char **) {
  DEMO(rvo_prvalue(1));
  DEMO(pessimize_temporary(2));
  DEMO(pessimize_local(3));
  DEMO(nrvo(4));
  DEMO(no_nrvo_two_locals(argc > 17, 5));
  DEMO(no_nrvo_ternary(argc > 42, 6));
  DEMO(no_nrvo_param(A{7}));
  DEMO(no_nrvo_ternary_move(argc > 100, 8));
  DEMO(no_nrvo_two_locals_move(argc > 3, 9));

  {
    std::cout << "* elision doesn't apply to move-assign" << std::endl;
    A b{10};
    b = rvo_prvalue(11);
  }

  return 0;
}
