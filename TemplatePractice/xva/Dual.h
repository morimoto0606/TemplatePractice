#ifndef DUAL_H_INCLUDED
#define DUAL_H_INCLUDED
#include "type_traits.h"
namespace cva {
	class Dual {
	public:
		Dual() : _value(0.0), _deriv(0.0) {}
		explicit Dual(const double value)
		: _value(value), _deriv(0.0) {}
		
		Dual(const double value, const double deriv) 
		: _value(value), _deriv(deriv) {}
		
		double value() const {
			return _value;
		}
		double deriv() const {
			return _deriv;
		}
		
		template <typename T>
		Dual& operator+=(const T& rhs)
		{
			_value += type_traits<Dual, T>::apply(rhs)._value;
			_deriv += type_traits<Dual, T>::apply(rhs)._deriv;
			return *this;
		}

		template <typename T>
		Dual operator +(const T& rhs) const
		{
			return Dual(_value + type_traits<Dual, T>::apply(rhs)._value,
				_deriv + type_traits<Dual, T>::apply(rhs)._deriv);
		}

		template <typename T>
		const Dual operator -(const T& rhs) const
		{
			return Dual(_value - type_traits<Dual, T>::apply(rhs)._value,
				_deriv - type_traits<Dual, T>::apply(rhs)._deriv);
		}
		
		template <typename T>
		Dual operator *(const T& rhs) const
		{
			double value = type_traits<Dual, T>::apply(rhs).value();
			double deriv = type_traits<Dual, T>::apply(rhs).deriv();

			return Dual(_value * value,	_deriv * value + _value * deriv);
		}

		template <typename T>
		const Dual operator /(const T& rhs) const
		{
			double value = type_traits<Dual, T>::apply(rhs).value();
			double deriv = type_traits<Dual, T>::apply(rhs).deriv();
			return Dual(_value / value,	(_deriv * value
				- _value * deriv)	/ (value * value));
		}
	private:
		double _value;
		double _deriv;
	};

	//template <typename T>
	//T max(const T& d, const double floor)
	//{
	//	double value = std::max(d.value(), floor);
	//	double deriv = d.value() > floor ? d.deriv() : 0.0;
	//	return T(value, deriv);
	//}
	//template <>
	//double max(const double& d, const double floor)
	//{
	//	return std::max(d, floor);
	//}
	//Dual exp(const Dual& d)
	//{
	//	return Dual(std::exp(d.value()), d.deriv() * std::exp(d.value()));
	//}
	//
	

} //namespace cva
#endif