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

	template <typename T>
	T calcCvaUsingExplicitExposure(
		const ublas::vector<boost::function<
		T(const T&) > >& exposureFunctions,
		const Path<T>& path, const double dt)
	{
		T cvaValue(0.0);
		for (std::size_t pathIndex = 0; 
		pathIndex < path.pathNum(); ++pathIndex) {
			T pathwiseValue(0.0);
			for (std::size_t gridIndex = 1; 
			gridIndex <= path.gridNum(); ++gridIndex) {
				pathwiseValue += cva::zeroFloor(
					exposureFunctions(gridIndex)(
						path.getPathValue(pathIndex, gridIndex)));
			}
			cvaValue += pathwiseValue;
		}
		return cvaValue * dt;
	}

	template <typename T, typename U>
	T calcCvaUsingImplicitExposure(
		const ublas::vector<boost::function<
		T (const T&) > >& exposureFunctions,
		const Path<T>& path, const PayOff<U>& payoff,
		const double dt)
	{
		T cvaValue(0.0);
		for (std::size_t pathIndex = 0;
		pathIndex < path.pathNum(); ++pathIndex) {
			T pathwiseValue(0.0);
			for (std::size_t gridIndex = 1;
			gridIndex <= path.gridNum(); ++gridIndex) {
				if ((exposureFunctions(gridIndex)(
					path.getPathValue(pathIndex, gridIndex))).value() > 0.0) {
					pathwiseValue += 
						payoff()(path.getTimewisePath(pathIndex));
				}
			}
			cvaValue += pathwiseValue;
		}
		return cvaValue * dt;
	}

	////Path<Dual<double> > makeDualPath(
	//	const double x0, const double mu, const double sigma,
	//	const double dt, const std::size_t gridNum,
	//	const std::size_t pathNum,
	//	const shockTypeEnum shockType, const std::size_t seed)
	//{
	//	const Dual<double> x0Dual = shockType
	//		== undEnum ? Dual<double>(x0, 1.0) : Dual<double>(x0, 0.0);
	//	const Dual<double> sigmaDual = shockType
	//		== volEnum ? Dual<double>(sigma, 1.0) : Dual<double>(sigma, 0.0);
	//	const Dual<double> muDual(mu, 0.0);
	//	return Path<Dual<double> >(x0Dual, muDual,
	//		sigmaDual, pathNum, gridNum, dt, seed);
	//}

	Path<Dual<double> > makePath(
		const double x0, const double mu, const double sigma,
		const double dt, const std::size_t gridNum,
		const std::size_t pathNum,
		const shockTypeEnum shockType, const std::size_t seed)
	{
		const Dual<double> x0Dual = shockType
			== undEnum ? Dual<double>(x0, 1.0) : Dual<double>(x0, 0.0);
		const Dual<double> sigmaDual = shockType
			== volEnum ? Dual<double>(sigma,1.0) : Dual<double>(sigma, 0.0);
		const Dual<double> muDual(mu, 0.0);
		return Path<Dual<double> >(x0Dual, muDual,
			sigmaDual, pathNum, gridNum, dt, seed);
	}

	template <typename P, typename C>
	ublas::vector<boost::function<Dual<double>(
		const Dual<double>&)> > makeLsmFunctions(
			const Path<C>& path, const PayOff<P>& payoff)
	{
		// lsmFunctions(i),  i = 0, 1, ...,  gridNum 
		ublas::vector<boost::function<C (const C&)> > 
			functions(3);
		for (std::size_t i = 0; i < 3; ++i) {
			functions(i) = boost::function<C (const C&)>
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

	ublas::vector<boost::function<Dual<double>(
		const Dual<double>&)> > 
		makeAnalyticForwardExposures(
			const double mu, const double sigma,
			const std::size_t gridNum, const double maturity,
			const double fwdCoeffA, const double fwdCoeffB)
	{
		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > fwdFunctions(gridNum + 1);
		for (std::size_t gridIndex = 0; gridIndex <= gridNum; ++gridIndex) {
			const double tau = maturity
				* static_cast<double>(gridNum - gridIndex)
				/ static_cast<double>(gridNum);
			fwdFunctions(gridIndex)
				= boost::bind(forwardFunction<Dual<double> >, _1,
					Dual<double>(mu), Dual<double>(sigma),
					fwdCoeffA, fwdCoeffB, tau);
		}
		return fwdFunctions;
	}

	ublas::vector<boost::function<Dual<double>(
		const Dual<double>&)> >
		makeAnalyticEuropeanExposures(
			const double mu, const double sigma,
			const std::size_t gridNum, const double maturity,
			const double fwdCoeffA, const double fwdCoeffB)
	{
		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > eurFunctions(gridNum + 1);
		for (std::size_t gridIndex = 0; gridIndex <= gridNum; ++gridIndex) {
			const double tau = maturity
				* static_cast<double>(gridNum - gridIndex)
				/ static_cast<double>(gridNum);
			eurFunctions(gridIndex)
				= boost::bind(europeanFunction<Dual<double> >, _1,
					Dual<double>(mu), Dual<double>(sigma),
					fwdCoeffA, fwdCoeffB, tau);
		}
		return eurFunctions;
	}

	ublas::vector<boost::function<Dual<double>(
		const Dual<double>&)> >
		makeAnalyticMountainExposures(
			const double mu, const double sigma,
			const std::size_t gridNum, const double maturity,
			const double gearing, const double strike1,
			const double strike2, const double strike3, const double strike4)
	{
		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > functions(gridNum + 1);
		for (std::size_t gridIndex = 0; gridIndex <= gridNum; ++gridIndex) {
			const double tau = maturity
				* static_cast<double>(gridNum - gridIndex)
				/ static_cast<double>(gridNum);
			functions(gridIndex)
				= boost::bind(mountain<Dual<double> >, _1,
					Dual<double>(mu), Dual<double>(sigma),
					gearing, strike1, strike2, strike3, strike4, tau);
		}
		return functions;
	}

	ublas::vector<boost::function<Dual<double>(
		const Dual<double>&)> >
		makeAnalyticRiskReversalExposures(
			const double mu, const double sigma,
			const std::size_t gridNum, const double maturity,
			const double gearing, const double strike1,
			const double strike2)
	{
		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > rrFunctions(gridNum);
		for (std::size_t gridIndex = 0; gridIndex <= gridNum; ++gridIndex) {
			const double tau = maturity
				* static_cast<double>(gridNum - gridIndex)
				/ static_cast<double>(gridNum);
			rrFunctions(gridIndex)
				= boost::bind(riskReversal<Dual<double> >, _1,
					Dual<double>(mu), Dual<double>(sigma),
					gearing, strike1, strike2, tau);
		}
		return rrFunctions;
	}

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
		return cvaValue / static_cast<double>(pathNumForMonte);
	}

	//Calculate Cva By Analytic Exposure
	template <typename T>
	Dual<double> calcCvaByAnalyticExposure(
		const double x0, const double mu, const double sigma,
		const PayOff<T>& payoff, const double maturity,
		const std::size_t gridNum, const std::size_t pathNum,
		const shockTypeEnum shockType, const std::size_t seed,
		const productTypeEnum productType, const bool useImplicitMethod)
	{
		const double dt = maturity / gridNum;

		const Path<Dual<double> > pathDual = makePath<Dual<double> >(
			x0, mu, sigma, dt, gridNum, pathNum, shockType, seed);

		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > exposureFunctions;
		switch (productType) {
		case fwdEnum :
			exposureFunctions = makeAnalyticForwardExposures(
					mu, sigma, pathDual.gridNum(), maturity,
					payoff().gearing(), payoff().strike());
			break;

		case eurEnum:
			exposureFunctions = makeAnalyticEuropeanExposures(
				mu, sigma, pathDual.gridNum(), maturity,
				payoff().gearing(), payoff().strike());
			break;

		case mountainEnum:
			exposureFunctions = makeAnalyticMountainExposures(
				mu, sigma, pathDual.gridNum(), maturity,
				payoff().gearing(), payoff().strikes()(0), payoff().strikes()(1),
				payoff().strikes()(2), payoff().strikes()(3));
			break;
		}


		Dual<double> cvaValue = useImplicitMethod
			? calcCvaUsingImplicitExposure(
				exposureFunctions, pathDual, payoff, dt)
			: calcCvaUsingExplicitExposure(
				exposureFunctions, pathDual, dt);
		return cvaValue / static_cast<double>(pathNum);
	}

	Dual<double> calcCvaFwdByAnalytic(
		const double x0, const double mu, const double sigma,
		const Forward& payoff, const double maturity,
		const std::size_t gridNum, const shockTypeEnum shockType)
	{
		Dual<double> cvaValue(0.0);
		Dual<double> x0Dual = shockType == undEnum
			? Dual<double>(x0, 1.0)
			: Dual<double>(x0);
		Dual<double> sigmaDual = shockType == volEnum
			? Dual<double>(sigma, 1.0)
			: Dual<double>(sigma);
		const double strike = payoff.strike();
		const double dt = maturity / static_cast<double>(gridNum);
		for (std::size_t gridIndex = 1; gridIndex <= gridNum; ++gridIndex) {
			const double t = gridIndex * dt;
			const double tau = maturity - t;
			const double gearing = std::exp(mu * tau) * payoff.gearing();
			cvaValue += europeanFunction<Dual<double> >(x0Dual,
				Dual<double>(mu), sigmaDual, gearing, strike, t);
		}
		return cvaValue;
	}
	Dual<double> calcCvaEurByAnalytic(
		const double x0, const double mu, const double sigma,
		const European& payoff, const double maturity,
		const std::size_t gridNum, const shockTypeEnum shockType)
	{
		Dual<double> cvaValue(0.0);
		Dual<double> x0Dual = shockType == undEnum
			? Dual<double>(x0, 1.0)
			: Dual<double>(x0);
		Dual<double> sigmaDual = shockType == volEnum
			? Dual<double>(sigma, 1.0)
			: Dual<double>(sigma);

		const double strike = payoff.strike();
		const double dt = maturity / static_cast<double>(gridNum);
		for (std::size_t gridIndex = 1; gridIndex <= gridNum; ++gridIndex) {
			const double gearing = payoff.gearing();
			const double t = gridIndex * dt;
			cvaValue += europeanFunction<Dual<double> >(x0Dual,
				Dual<double>(mu), sigmaDual, gearing, strike, maturity);
		}
		return cvaValue * dt;
	}

	Dual<double> calcCvaMountainByAnalytic(
		const double x0, const double mu, const double sigma,
		const Mountain& payoff, const double maturity,
		const std::size_t gridNum, const shockTypeEnum shockType)
	{
		Dual<double> cvaValue(0.0);
		Dual<double> x0Dual = shockType == undEnum
			? Dual<double>(x0, 1.0)
			: Dual<double>(x0);
		Dual<double> sigmaDual = shockType == volEnum
			? Dual<double>(sigma, 1.0)
			: Dual<double>(sigma);

		const double strike1 = payoff.strikes()(0);
		const double strike2 = payoff.strikes()(1);
		const double strike3 = payoff.strikes()(2);
		const double strike4 = payoff.strikes()(3);

		const double dt = maturity / static_cast<double>(gridNum);
		for (std::size_t gridIndex = 1; gridIndex <= gridNum; ++gridIndex) {
			const double gearing = payoff.gearing();
			const double t = gridIndex * dt;
			cvaValue += mountain<Dual<double> >(x0Dual,
				Dual<double>(mu), sigmaDual, gearing, strike1,
				strike2, strike3, strike4, maturity);
		}
		return cvaValue * dt;
	}
}//namespace cva
