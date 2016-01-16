#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "function_traits.h"

namespace cva{
	template <typename T>
	typename zero_floor_traits<T>::value_type
		zeroFloor(const T& x)
	{
		return zero_floor_traits<T>::apply(x);
	}
	
	template <typename T>
	typename exp_traits<T>::value_type
		exp(const T& x)
	{
		return exp_traits<T>::apply(x);
	}

	template <typename T>
	typename log_traits<T>::value_type
		log(const T& x)
	{
		return log_traits<T>::apply(x);
	}

	template <typename T>
	typename normal_cdf_traits<T>::value_type
		normalCdf(const T& x)
	{
		return normal_cdf_traits<T>::apply(x);
	}

	template <typename T>
	typename sqrt_traits<T>::result_type sqrt(
		const T& x)
	{
		return sqrt_traits<T>::apply(x);
	}
	//template <typename T, std::size_t n>
	//typename sqrt_traits<T>::result_type sqrt(
	//	const T& x)
	//{
	//	return sqrt_traits<T>::apply(x);
	//}

	class Monomial {
	public:
		explicit Monomial(const double order) : _order(order) {}
		
		template <typename T>
		T operator()(const T& x) const
		{
			return _order == 0.0 ? 1.0 : std::pow(x, _order);
		}
		template <typename T>
		Dual<T> operator()(const Dual<T>& x) const
		{
			T value = _order == 0.0 ? 1.0 : std::pow(x.value(), _order);
			T deriv = _order * std::pow(x.value(), _order - 1) * x.deriv();
			return Dual<T>(value, deriv);
		}
	private: 
		double _order;
	};

	class Monomial2 {
	public:
		Monomial2(const double order1, const double order2)
		: _order1(order1), _order2(order2) {}

		template <typename T>
		T operator()(const T& x, const T& y) const
		{
			return std::pow(x, _order1) * std::pow(y, _order2);
		}

		template <typename T>
		Dual<T> operator()(const Dual<T>& x, const Dual<T>& y) const
		{
			T value = std::pow(x.value(), _order1) * std::pow(y.value(), _order2);
			T deriv = _order1 * std::pow(x.value(), _order1 - 1) * x.deriv * y.value()
				+ _order2 * std::pow(y.value(), _order2 - 1) * y.deriv() * x.value();
			return Dual<T>(value, deriv);
		}
	private:
		double _order1;
		double _order2;
	};
} //namespace cva
#endif