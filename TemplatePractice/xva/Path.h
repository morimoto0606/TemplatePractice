#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/random.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Dual.h"

namespace cva {
	namespace ublas = boost::numeric::ublas;
	template <typename T>
	class Path {
	public:
		typedef T value_type;
		typedef std::size_t size_type;
		Path(const value_type& x0, const value_type& mu,
			const value_type& sigma, const size_type pathNum,
			const size_type gridNum, const double dt,
			const size_type seed)
		{
			boost::mt19937 gen(seed);
			boost::normal_distribution<double> dist(0.0, 1.0);
			boost::variate_generator < boost::mt19937,
				boost::normal_distribution<double >> rand(gen, dist);
			ublas::matrix<value_type> bm(pathNum, gridNum);
			_pathMatrix.resize(pathNum, gridNum);
			
			//log x(j+1) = log x(j)  + (mu - sigma^2/2) dt + sigma dw
		}
	private :
		T _x0;
		T _mu;
		T _sigma;

		ublas::matrix<T> _pathMatrix;
	};
} //namespace cva
#endif