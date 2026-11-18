/*
 * A const prvalue in C++ is a pure rvalue that has a const qualifier.
 *
 * Example - return value of a function declared as `const T f()`.
 *
 * Pessimizes Moves: this prevents move constructors from being selected
 * during assignment or initialization, forcing a copy instead.
 *
 * https://www.mathworks.com/help/bugfinder/ref/constreturnvaluesmaycauseunnecessarydatacopies.html
 *
 * Nothing warns about this. `-Wall`, `-Wextra` do not flag `const A bar()`.
 * GCC's -Wignored-qualifiers only fires for scalar return types.
 * clang-tidy's `readability-const-return-type` does catch it.
 */
#include <iostream>
#include <type_traits>
#include <vector>

static int counter{};

template <bool NoexceptMove> struct Demo {
  const int id;
  int mynum;

  Demo() : id{counter++}, mynum{counter - 1} {
    std::cout << "    - [" << id << "] default construct value " << mynum
              << std::endl;
  }

  ~Demo() {
    std::cout << "    - [" << id << "] destruct value ";
    if (mynum == -1) {
      std::cout << "<moved from>";
    } else {
      std::cout << mynum;
    }
    std::cout << std::endl;
  }

  Demo(const Demo &other) : id{counter++}, mynum{other.mynum} {
    std::cout << "    - [" << id << "] copy construct from [" << other.id
              << "] value " << other.mynum << std::endl;
  }
  Demo(Demo &&other) noexcept(NoexceptMove)
      : id{counter++}, mynum{other.mynum} {
    std::cout << "    - [" << id << "] move construct from [" << other.id
              << "] value " << other.mynum << std::endl;

    other.mynum = -1;
  }
  Demo &operator=(const Demo &other) {
    std::cout << "    - [" << id << "] copy assign from [" << other.id
              << "]. Old value " << mynum << " new value " << other.mynum
              << std::endl;

    mynum = other.mynum;

    return *this;
  }
  Demo &operator=(Demo &&other) noexcept {
    std::cout << "    - [" << id << "] move assign from [" << other.id
              << "]. Old value " << mynum << " new value " << other.mynum
              << std::endl;

    mynum = other.mynum;

    if (this != &other)
      other.mynum = -1;

    return *this;
  }
};

using NotThrowing = Demo<true>;
using MayThrow = Demo<false>;

static_assert(std::is_nothrow_move_constructible<NotThrowing>::value,
              "move constructor must not throw");
static_assert(!std::is_nothrow_move_constructible<MayThrow>::value,
              "move constructor may throw");

// Movable
NotThrowing foo() { return {}; }

// Problem, not movable.
// A `const NotThrowing` prvalue binds to `const NotThrowing&&`, which doesn't
// match `NotThrowing&&`, so overload resolution falls back to the
// `const NotThrowing&` copy overloads.
const NotThrowing bar() { return {}; }

static void case_1() {
  std::cout << "* CASE 1" << std::endl;
  NotThrowing a;
  std::cout << "  Should be <move assign>" << std::endl;
  a = foo();
  std::cout << "  Should be pessimized <copy assign>" << std::endl;
  a = bar();
}

static void case_2() {
  std::cout << "* CASE 2" << std::endl;
  std::vector<NotThrowing> v;
  v.reserve(2);
  std::cout << "  Move into vector" << std::endl;
  v.push_back(foo());
  std::cout << "  Copy into vector" << std::endl;
  v.push_back(bar());
}

static void case_3() {
  // Many compilers optimize this anyway, so this test case requires
  // -fno-elide-constructors in c++11. In c++17 the flag does nothing.
  std::cout << "* CASE 3" << std::endl;
  std::cout << "  c++17 guaranteed elision so no copy or move should be printed"
            << std::endl;
  NotThrowing b = bar();
}

template <typename T> static void grow(const char *message) {
  std::cout << "  " << message << std::endl;
  std::vector<T> v;

  for (int i = 0; i < 5; ++i) {
    std::cout << "   push_back #" << i << " (capacity " << v.capacity() << ")"
              << std::endl;
    v.push_back(T{});
  }
}

/*
 * `std::vector` uses `std::move_if_noexcept` when it reallocates,
 * so a move constructor that might throw makes the vector copy every element
 * when it grows if the type is copyable. If the copy constructor is deleted,
 * `std::move_if_noexcept` still moves and you lose the strong exception
 * guarantee instead.
 */
static void case_4() {
  std::cout << "* CASE 4" << std::endl;
  grow<NotThrowing>("noexcept move: reallocation should <move construct>");
  grow<MayThrow>("potentially throwing move: reallocation is pessimized to "
                 "<copy construct>");
}

int main() {
  case_1();
  case_2();
  case_3();
  case_4();

  return 0;
}
