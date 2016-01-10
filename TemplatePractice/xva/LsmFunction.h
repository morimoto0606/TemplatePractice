#pragma once
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>

namespace cva {
	namespace ublas = boost::numeric::ublas;
	template <typename T, typename U>
	class LsmFunction {
	public:
		typedef T value_type;
		typedef U coeffcient_type;
		typedef std::size_t size_type;
		typedef value_type result_type;
		LsmFunction(const ublas::vector<coeffcient_type>& coeffs,
			const ublas::vector <boost::function<result_type (const value_type&)> >&
			basisFunctions) : _coefficients(coeffs), _basisFunctions(basisFunctions) {}
		
		result_type operator()(const value_type& x) const
		{
			ublas::vector<double> value(_coefficients.size(), 0.0);
			for (std::size_t i = 0; i < _coefficients.size(); ++i) {
				value(i) = (_basisFunctions(i))(x);
			}
			return ublas::inner_prod(_coefficients, value);
		}
	private:
		ublas::vector<coeffcient_type> _coefficients;
		ublas::vector <boost::function<
			value_type (const value_type&)> >_basisFunctions;
	};
}//namespace cva