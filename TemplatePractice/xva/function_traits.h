#ifndef FUNCTION_TRAITS_H_INCLUDED
#define FUNCTION_TRAITS_H_INCLUDED

#include "Dual.h"
namespace cva {
	template <typename T>
	struct max_traits {
		typedef T value_type;
		typedef T result_type;
		static const result_type
			apply(const value_type& x, const double y)
		{
			return std::max(x, y);
		}
	};

	template <>
	struct max_traits <Dual>{
		typedef Dual value_type;
		typedef Dual result_type;
		static const result_type 
			apply(const value_type& x, const double y)
		{
			const double value = std::max(x.value(), y); 
			const double deriv = x.value() >= y ? x.deriv() : 0.0;
			return Dual(value, deriv);
		}
	};

	template <typename T>
	struct exp_traits {
	public:
		typedef T value_type;
		typedef T result_type;
		static const result_type apply(const value_type&x)
		{
			return std::exp(x);
		}
	};
	template <>
	struct exp_traits <Dual> {
	public:
		typedef Dual value_type;
		typedef Dual result_type;
		static const result_type apply(const value_type& x)
		{
			const double value = std::exp(x.value());
			const double deriv = x.deriv() * value;
			return Dual(deriv, value);
		}
	};
} //namespace cva
#endif