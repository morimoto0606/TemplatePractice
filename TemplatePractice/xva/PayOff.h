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
		double gearing() const { return _a; }
		double strike() const { return _b; }

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
			return cva::zeroFloor(_a * *(x.end() - 1) + _b);
		}
		template <typename T>
		T operator()(const ublas::vector<T>& x) const
		{
			return cva::zeroFloor(_a * *(x.end() - 1) + _b);
		}
		double gearing() const { return _a; }
		double strike() const { return _b; }

	private:
		double _a;
		double _b;
	};

	class RiskReversal : public PayOff <RiskReversal> {
	public:
		RiskReversal(const double& gearing, const double& strike1,
			const double& strike2) 
		: _gearing(gearing), _strike1(strike1), _strike2(strike2) {}

		template <typename T>
		typename T::value_type operator()(const T& x) const
		{
			return cva::zeroFloor(_gearing * *(x.end() - 1) - _strike1)
				- cva::zeroFloor(_strike2 -_gearing * *(x.end() - 1));
		}
		double gearing() const { return _gearing; }
		double strike1() const { return _strike1; }
		double strike2() const { return _strike2; }

	private:
		double _gearing;
		double _strike1;
		double _strike2;
	};
} // namespace cva

#endif