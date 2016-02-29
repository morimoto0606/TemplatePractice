#ifndef VIRTUAL_H_INCLUDED
#define VIRTUAL_H_INCLUDED
#include <iostream>
namespace study {
	struct Base 
	{
		void base_foo() const
		{
			foo();
		}
		virtual void foo() const = 0;
	};

	struct Derived : public Base {
		virtual void foo() const 
		{
			std::cout << "Derived::foo" << std::endl;
		}
	};

} //study
#endif