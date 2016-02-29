#include <iostream>

#ifndef CRTP_INCLUDED
#define CRTP_INCLUDED

namespace CRTP {
	template <class T_Derived>
	struct Base {
		void base_foo() const {
			static_cast<const T_Derived&> (*this).foo();
		}
	};
	struct Derived : public Base<Derived>
	{
		void foo() const {
			std::cout << "foo" << std::endl;
		}
	};
	struct Derived2 : public Base<Derived2>
	{
		void foo() const {
			std::cout << "foo2" << std::endl;
		}
	};
}//CRTP {
#endif