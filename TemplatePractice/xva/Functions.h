#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "function_traits.h"

namespace cva{
	template <typename T>
	typename max_traits<T>::value_type 
		max(const T& x, const double floor)
	{
		return max_traits<T>::apply(x, floor);
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

} //namespace cva
#endif