// If no matching handler is found, the function std::terminate() is called;
// whether or not the stack is unwound before this call to std::terminate()
// is implementation-defined (15.5.1).
#include <iostream>
#include <exception>
#include <memory>

class X
{
public:
X(){std::cout << "X::X()" << std::endl;}
~X(){std::cout << "X::~X()" << std::endl;}
};

int main()
{
 std::unique_ptr p = std::make_unique<X>();
throw std::exception();
return 0;
}
