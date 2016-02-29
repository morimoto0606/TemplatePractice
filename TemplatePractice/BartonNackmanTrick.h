#ifndef BARTONNACKMANTRICK_H_INCLUDED
#define BARTONNACKMANTRICK_H_INCLUDED

namespace Trick {
	template <typename T_Derived>
	class Base {
	public:
		virtual ~Base() {}
	private:
		friend bool operator!= (const T_Derived& lhs, const T_Derived& rhs) 
		{
			return !lhs.operator== (rhs);
		}
	};

	class Derived : public Base<Derived>
	{
	public:
		explicit Derived(const int id) : _id(id) {}
		bool operator== (const Derived& rhs) const 
		{
			return _id == rhs._id;
		}
	private:
		int _id;
	};
} //namespace Trick {
#endif