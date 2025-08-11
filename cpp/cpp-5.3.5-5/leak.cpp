#include <iostream>
#include <memory>

/*
 * 5.3.5 Delete
 *
 * 5. If the object being deleted has incomplete class type at the point of deletion
 *    and the complete class has anon-trivial destructor or a deallocation function,
 *    the behavior is undefined.
 *
 * GCC:
 *    note: neither the destructor nor the class-specific operator delete will be called,
 *    even if they are declared when the class is defined
 * MSVC:
 *    warning C4150: deletion of pointer to incomplete type 'A'; no destructor called
 */

//delete: warning

//std::auto_ptr: silent memory leak

//std::shared_ptr: valid application of ‘sizeof’ to incomplete type ‘A’
//    static_assert( sizeof(_Tp1) > 0, "incomplete type" );

//std::unique_ptr: invalid application of ‘sizeof’ to incomplete type ‘A’
//  static_assert(sizeof(_Tp)>0, "incomplete type" );

class A;

A* foo();
void bar(const std::auto_ptr<A>&a);
//void bar(const A *a);

class B
{
public:
  B() : a(foo()) {}

  void baz()
  {
    bar(a);
  }

  ~B()
  {
    //delete a;
  }

  //A *a;

  std::auto_ptr<A> a;

};

int main()
{
  B b;

  b.baz();
}
