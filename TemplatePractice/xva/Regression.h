#pragma once
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/function.hpp>
#include "PayOff.h"
#include "Path.h"
#include <boost/numeric/ublas/triangular.hpp> 
#include <boost/numeric/ublas/lu.hpp>     
#include <boost/numeric/ublas/io.hpp>

namespace cva {
	namespace ublas = boost::numeric::ublas;

	template <typename T>
	ublas::matrix<T> getBasisMatrix(
		const T& pathValue,
		const ublas::vector<boost::function<T(const T&)> >& functions)
	{
		const std::size_t basisNum = functions.size();
		ublas::vector<T> coeffient(basisNum, 0);
		ublas::matrix<T> basisMatrix(basisNum, basisNum, 0);
		for (std::size_t i = 0; i < basisNum; ++i) {
			for (std::size_t j = 0; j < basisNum; ++j) {
				basisMatrix(i, j)
					= (functions(i))(pathValue) * (functions(j))(pathValue);
			}
		}
		return basisMatrix;
	}

	template <typename T, typename U>
	ublas::vector<T> getPayOffBasis(
		const T& pathValue,
		const ublas::vector<T>& timewisePath,
		const PayOff<U>& payoff,
		const ublas::vector<boost::function<T(const T&)> >& functions)
	{
		const std::size_t basisNum = functions.size();
		T payoffValue = payoff(timewisePath);
		ublas::vector<T> payOffBasis(basisNum, 0);
		for (std::size_t i = 0; i < basisNum; ++i) {
			payOffBasis(i)
				= (functions(i))(pathValue) * payoffValue;
		}
		return payOffBasis;
	}
	
	template <typename T, typename U>
	ublas::vector<T> regresssion(
		std::size_t gridIndex,
		const PayOff<U>& payoff,
		const Path<T>& path,
		const ublas::vector<boost::function<T(const T&)> >& functions)
	{
		const std::size_t basisNum = functions.size();
		const std::size_t pathNum = path.pathNum();
		const std::size_t gridNum = path.gridNum();
		
		// matrix (basis(i) * basis(j))
		ublas::matrix<T> basisMatrix(basisNum, basisNum, 0);
		//vector (basis(i) *Payoff)
		ublas::vector<T> payoffBasis(basisNum, 0);

		// take expectation of basisMatrix and payoffBasis
		for (std::size_t k = 0; k< pathNum; ++k) {
			basisMatrix += getBasisMatrix(
				path.getPathValue(k, gridIndex),
				functions);
			payoffBasis += getPayOffBasis(
				path.getPathValue(k, gridIndex),
				path.getTimewisePath(k),
				payoff, functions);
		}
		basisMatrix /= pathNum;
		payoffBasis /= pathNum;

		ublas::matrix<T> originalBasis(basisMatrix);
		ublas::permutation_matrix<> pm(basisNum);

		// LU Decomposition
		ublas::matrix<T> basisInverse = ublas::identity_matrix<double>(3);
		ublas::lu_factorize(basisMatrix, pm);
		
		ublas::lu_substitute(basisMatrix, pm, basisInverse);
		ublas::vector<T> coeffient
			= ublas::prod(payoffBasis, basisInverse);

		return coeffient;
	}
}//namespace cva {