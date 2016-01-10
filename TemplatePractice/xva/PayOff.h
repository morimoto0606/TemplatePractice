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

		template <typename T>
		typename T::value_type operator()(const T& x) const
		{
			return static_cast<const Derived&>(*this).operator()(x);
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
			return cva::max(*(x.end() - 1) + _b, 0.0) * _a;
		}
		template <typename T>
		T operator()(const ublas::matrix_column<T>& x) const
		{
			return cva::max(*(x.end() - 1) + _b, 0.0) * _a;
		}
	private:
		double _a;
		double _b;
	};
} // namespace cva

#endif