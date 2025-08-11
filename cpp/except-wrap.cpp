/* c++11. Exception-safe wrapper for almost any I/O function.
but see
https://stackoverflow.com/questions/46021734/what-is-the-reason-for-stdresult-of-deprecated-in-c17
*/
#include <cerrno>
#include <exception>
#include <iostream>
#include <type_traits>
#include <unistd.h>
#include <utility>

ssize_t fs_write_or_throw(int fd, const void *buf, size_t count);

#define str(x) #x

template <char const *fname, typename FooType, FooType func, typename... T>
typename std::result_of<FooType(T...)>::type fs_exception_wrapper(T... args) {
  try {
    return func(std::forward<T>(args)...);
  } catch (const std::exception &err) {
    std::cerr << fname << err.what() << std::endl;
    return -EIO;
  }
}

#define EXCEPTION_SAFE(name)                                                   \
  typedef decltype(&fs_##name##_or_throw) D_##name;                            \
  const char N_##name[] = str(name);                                           \
  static D_##name fs_##name =                                                  \
      &fs_exception_wrapper<N_##name, D_##name, fs_##name##_or_throw>;

EXCEPTION_SAFE(write);

ssize_t foo(int fd, const void *buf, size_t count) {
  return fs_write(fd, buf, count);
}
