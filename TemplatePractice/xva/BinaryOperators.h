#pragma once
#include "binary_operator_traits.h"
namespace cva {
	//operators
	template <typename T1, typename T2>
	typename binary_operator_traits<T1, T2>::result_type
		operator +(const T1& lhs, const T2 rhs)
	{
		return binary_operator_traits<T1, T2>::apply(lhs, rhs);
	}
}