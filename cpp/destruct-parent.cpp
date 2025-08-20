/* Call parent and field destructors on throw within constructor. */
#include <iostream>

struct A
{
	A() { std::cout << "A::A()" << std::endl; }

	~A() { std::cout << "A::~A()" << std::endl; }
};

struct Parent
{
	Parent() { std::cout << "Parent::Parent()" << std::endl; }

	~Parent() { std::cout << "Parent::~Parent()" << std::endl; }
};

struct B : Parent
{
	A a;

	B()
	{
		std::cout << "B::B()" << std::endl;
		throw 154;
	}

	~B() { std::cout << "B::~B()" << std::endl; }
};

int
main(int argc, char *argv[])
{
	try
	{
		B b;
	}
	catch (int v)
	{
		std::cerr << "Exception " << v << std::endl;
	}
	return 0;
}
