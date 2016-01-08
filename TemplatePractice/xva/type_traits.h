#ifndef DUAL_TRAITS_H_INCLUDED
#define DUAL_TRAITS_H_INCLUDED

namespace cva {
	template <typename T, typename V>
	struct type_traits {
		typedef T result_type;
		typedef V value_type;
		static const result_type apply(const V& x) 
		{
			return T(x);
		}
	};

	template <typename T>
	struct type_traits<T, T> {
		typedef T result_type;
		typedef T value_type;
		static result_type apply(const T& x)
		{
			return x;
		}
	};
} //namespace cva 
#endif