#ifdef STDAUTOPTR
#include <memory>
#else
namespace std
{
  template<typename _Tp1>
    struct auto_ptr_ref
    {
      _Tp1* _M_ptr;
      
      explicit
      auto_ptr_ref(_Tp1* __p): _M_ptr(__p) { }
    };

template<typename _Tp>
class auto_ptr
{
private:
  _Tp* _M_ptr;
public:
  typedef _Tp element_type;

  explicit auto_ptr(element_type * a = 0) throw()
    : _M_ptr(a)
  {
  }

  explicit auto_ptr(auto_ptr & __a) throw() : _M_ptr(__a.release()) { }
      template<typename _Tp1>
      auto_ptr(auto_ptr<_Tp1>& __a) throw() : _M_ptr(__a.release()) { }
      auto_ptr&
      operator=(auto_ptr& __a) throw()
      {
	reset(__a.release());
	return *this;
      }
      template<typename _Tp1>
        auto_ptr&
        operator=(auto_ptr<_Tp1>& __a) throw()
        {
	  reset(__a.release());
	  return *this;
	}
      element_type&
      operator*() const throw() 
      {
	return *_M_ptr; 
      }
      element_type*
      operator->() const throw() 
      {
	return _M_ptr; 
      }
      element_type*
      get() const throw() { return _M_ptr; }
      element_type*
      release() throw()
      {
	element_type* __tmp = _M_ptr;
	_M_ptr = 0;
	return __tmp;
      }
      void
      reset(element_type* __p = 0) throw()
      {
	if (__p != _M_ptr)
	  {
	    delete _M_ptr;
	    _M_ptr = __p;
	  }
      }
      auto_ptr(auto_ptr_ref<element_type> __ref) throw()
      : _M_ptr(__ref._M_ptr) { }
      
      auto_ptr&
      operator=(auto_ptr_ref<element_type> __ref) throw()
      {
	if (__ref._M_ptr != this->get())
	  {
	    delete _M_ptr;
	    _M_ptr = __ref._M_ptr;
	  }
	return *this;
      }
      
      template<typename _Tp1>
        operator auto_ptr_ref<_Tp1>() throw()
        { return auto_ptr_ref<_Tp1>(this->release()); }

      template<typename _Tp1>
        operator auto_ptr<_Tp1>() throw()
        { return auto_ptr<_Tp1>(this->release()); }

  ~auto_ptr()
  {
    delete _M_ptr;
  }
};
  template<>
    class auto_ptr<void>
    {
    public:
      typedef void element_type;
    };
};
#endif

class A;

void foo(A*a)
{
  //delete a;
  //std::R<A> del(a);
  std::auto_ptr<A> del(a);
}

int main()
{
}
