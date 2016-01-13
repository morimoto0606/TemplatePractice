#ifndef PAYOFF_H_INCLUDED
#define PAYOFF_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace cva {
	namespace ublas = boost::numeric::ublas;
	template <typename Derived>
	class PayOff {
	public:
		virtual ~PayOff() {}

		const Derived& operator()() const
		{
			return static_cast<const Derived&>(*this);
		}
	};

	class Forward : public PayOff <Forward> {
	public:
		Forward(const double& a, const double& b) : _a(a), _b(b) {}
		
		template <typename T>
		typename T::value_type operator()(const T& x) const
		{
			return *(x.end() - 1) * _a   + _b;
		}
	private:
		double _a;
		double _b;
	};

	class European : public PayOff <European> {
	public:
		European(const double& a, const double& b) : _a(a), _b(b) {}
		
		template <typename T>
		typename T::value_type operator()(const T& x) const
		{
			return cva::max(_a * *(x.end() - 1) + _b, 0.0);
		}
		template <typename T>
		T operator()(const ublas::vector<T>& x) const
		{
			return cva::max(_a * *(x.end() - 1) + _b, 0.0);
		}
	private:
		double _a;
		double _b;
	};
} // namespace cva

#endif