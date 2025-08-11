/* Unsigned integer overflow is not UB. */
#include <atomic>
#include <iostream>
#include <limits>
using namespace std;

int main() {
  atomic<uint64_t> val{std::numeric_limits<uint64_t>::max()};
  int64_t inc = -1;
  cout << val.fetch_add(inc) << endl;
}
