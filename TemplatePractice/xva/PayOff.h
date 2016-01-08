#ifndef PAYOFF_H_INCLUDED
#define PAYOFF_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace cva {
	namespace ublas = boost::numeric::ublas;
	template <typename Derived, typename T>
	class PayOff {
	public:
		virtual ~PayOff() {}
		T operator  ()(const ublas::vector<T>& x) const
		{
			return static_cast<const Derived&>(*this).operator()(x);
		}
	};

	template <typename T>
	class Forward : public PayOff <Forward<T>, T> {
	public:
		typedef T value_type;
		typedef value_type result_type;
		Forward(const value_type& a, const value_type& b) : _a(a), _b(b) {}
		result_type operator  ()(const ublas::vector<value_type>& x) const
		{
			return _a * *(x.end() - 1) + _b;
		}
	private:
		value_type _a;
		value_type _b;
	};

	template <typename T>
	class European : public PayOff <European<T>, T> {
	public:
		European(const T& a, const T& b) : _a(a), _b(b) {}
		T operator  ()(const ublas::vector<T>& x) const 
		{
			return cva::max(_a * *(x.end() - 1) + _b, 0.0);
		}
	private:
		T _a;
		T _b;
	};
} // namespace cva

#endif