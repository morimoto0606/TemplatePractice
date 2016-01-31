#pragma once

#include <iostream>
#include "Dual.h"
#include "AnalyticOptionFunctions.h"
#include "Path.h"
#include "PayOff.h"
#include "Regression.h"
#include "LsmFunction.h"
#include <boost/bind.hpp>
#include "PathMaker.h"

namespace cva {
	namespace ublas = boost::numeric::ublas;

	//Calculate Cva By Regression Exposure	
	template <typename P, typename C>
	Dual<double> calcCvaByRegressionExposure(
		const double x0, const double mu, const double sigma,
		const PayOff<P>& payoff, const double maturity,
		const std::size_t gridNum, const std::size_t pathNumForRegression,
		const std::size_t pathNumForMonte,
		const shockTypeEnum shockType, const std::size_t seed,
		const bool useImplicitMethod, const bool isCoeffShock)
	{
		const double dt = maturity / gridNum;
		const Path<C> pathForRegression
			= makePath<C>(x0, mu, sigma, dt, gridNum,
				pathNumForRegression, shockType, seed);

		const Path<Dual<double> > pathForMonte
			= makePath<Dual<double> >(x0, mu, sigma, dt, gridNum,
				pathNumForMonte, shockType, seed);

		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > lsmFunctions =
			makeLsmFunctions(pathForRegression, payoff);

		Dual<double> cvaValue = useImplicitMethod
			? calcCvaUsingImplicitExposure(lsmFunctions, pathForMonte, payoff, dt)
			: calcCvaUsingExplicitExposure(lsmFunctions, pathForMonte, dt);
		return cvaValue;
	}

	template <typename P, typename C>
	ublas::vector<boost::function<Dual<double>(
		const Dual<double>&)> > makeLsmFunctions(
			const Path<C>& path, const PayOff<P>& payoff)
	{
		// lsmFunctions(i),  i = 0, 1, ...,  gridNum 
		ublas::vector<boost::function<C(const C&)> >
			functions(3);
		for (std::size_t i = 0; i < 3; ++i) {
			functions(i) = boost::function<C(const C&)>
				(Monomial(static_cast<double>(i)));
		}
		ublas::vector<boost::function<
			Dual<double>(const Dual<double>&)> >  dualFunctions(3);
		for (std::size_t i = 0; i < 3; ++i) {
			dualFunctions(i) = boost::function<
				Dual<double>(const Dual<double>&)>
				(Monomial(static_cast<double>(i)));
		}

		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> >
			lsmFunctions(path.gridNum() + 1);
		for (std::size_t gridIndex = 0; gridIndex <= path.gridNum(); ++gridIndex) {
			ublas::vector<C> coeff;
			coeff = regresssion(gridIndex, payoff, path, functions);
			lsmFunctions(gridIndex)
				= LsmFunction<Dual<double>, C>(
					coeff, dualFunctions);
		}
		return lsmFunctions;
	}
} //namespace cva {
