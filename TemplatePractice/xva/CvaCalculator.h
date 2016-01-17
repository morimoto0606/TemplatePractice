#pragma once
#include <iostream>
#include "Dual.h"
#include "AnalyticOptionFunctions.h"
#include "Path.h"
#include "PayOff.h"
#include "Regression.h"
#include "LsmFunction.h"
#include <boost/bind.hpp>

namespace cva {
	namespace ublas = boost::numeric::ublas;
	enum shockTypeEnum { undEnum = 0, volEnum = 1 };
	enum productTypeEnum { fwdEnum = 0, eurEnum = 1, rrEnum =2};

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
			for (std::size_t gridIndex = 0; 
			gridIndex < path.gridNum() - 1; ++gridIndex) {
				pathwiseValue += cva::zeroFloor(
					exposureFunctions(gridIndex + 1)(
						path.getPathValue(pathIndex, gridIndex + 1)));
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
			for (std::size_t gridIndex = 0;
			gridIndex < path.gridNum() - 1; ++gridIndex) {
				if ((exposureFunctions(gridIndex + 1)(
					path.getPathValue(pathIndex, gridIndex + 1))).value() > 0.0) {
					pathwiseValue += 
						payoff()(path.getTimewisePath(pathIndex));
				}
			}
			cvaValue += pathwiseValue;
		}
		return cvaValue * dt;
	}

	Path<Dual<double> > makeDualPath(
		const double x0, const double mu, const double sigma,
		const double dt, const std::size_t gridNum,
		const std::size_t pathNum,
		const shockTypeEnum shockType, const std::size_t seed)
	{
		const Dual<double> x0Dual = shockType
			== undEnum ? Dual<double>(x0, 1.0) : Dual<double>(x0, 0.0);
		const Dual<double> sigmaDual = shockType
			== volEnum ? Dual<double>(sigma, 0.0) : Dual<double>(sigma, 0.0);
		const Dual<double> muDual(mu, 0.0);
		return Path<Dual<double> >(x0Dual, muDual,
			sigmaDual, pathNum, gridNum, dt, seed);
	}

	template <typename T>
	ublas::vector<boost::function<Dual<double>(
		const Dual<double>&)> > makeLsmFunctions(
			const Path<double>& path, const PayOff<T>& payoff)
	{
		// lsmFunctions(i),  i = 0, 1, ...,  gridNum 
		ublas::vector<boost::function<double(const double&)> >  functions(3);
		for (std::size_t i = 0; i < 3; ++i) {
			functions(i) = boost::function<double(const double&)>
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
			lsmFunctions(path.gridNum());
		for (std::size_t gridIndex = 0; gridIndex < path.gridNum(); ++gridIndex) {
			ublas::vector<double> coeff;
			coeff = regresssion(gridIndex, payoff, path, functions);
			lsmFunctions(gridIndex)
				= LsmFunction<Dual<double>, double>(coeff, dualFunctions);
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
			const Dual<double>&)> > fwdFunctions(gridNum);
		for (std::size_t gridIndex = 0; gridIndex < gridNum; ++gridIndex) {
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
			const Dual<double>&)> > eurFunctions(gridNum);
		for (std::size_t gridIndex = 0; gridIndex < gridNum; ++gridIndex) {
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
		makeAnalyticRiskReversalExposures(
			const double mu, const double sigma,
			const std::size_t gridNum, const double maturity,
			const double gearing, const double strike1,
			const double strike2)
	{
		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > rrFunctions(gridNum);
		for (std::size_t gridIndex = 0; gridIndex < gridNum; ++gridIndex) {
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
	template <typename T>
	Dual<double> calcCvaByRegression(
		const double x0, const double mu, const double sigma,
		const PayOff<T>& payoff, const double maturity,
		const std::size_t gridNum, const std::size_t pathNum,
		const std::size_t dualPathNum,
		const shockTypeEnum shockType, const std::size_t seed,
		const bool useImplicitMethod)
	{
		const double dt = maturity / gridNum;
		const Path<double> path(x0, mu, sigma,
			pathNum, gridNum, dt, seed);

		const Path<Dual<double> > pathDual = makeDualPath(
			x0, mu, sigma, dt, gridNum, dualPathNum, shockType, seed);

		ublas::vector<boost::function<Dual<double>(
			const Dual<double>&)> > lsmFunctions =
			makeLsmFunctions(path, payoff);
	
		Dual<double> cvaValue = useImplicitMethod
			? calcCvaUsingImplicitExposure(lsmFunctions, pathDual, payoff, dt)
			: calcCvaUsingExplicitExposure(lsmFunctions, pathDual, dt);
		return cvaValue / static_cast<double>(pathNum);
	}

	//Calculate Cva By Analytic Exposure
	template <typename T>
	Dual<double> calcCvaByAnalytic(
		const double x0, const double mu, const double sigma,
		const PayOff<T>& payoff, const double maturity,
		const std::size_t gridNum, const std::size_t pathNum,
		const std::size_t dualPathNum,
		const shockTypeEnum shockType, const std::size_t seed,
		const productTypeEnum productType, const bool useImplicitMethod)
	{
		const double dt = maturity / gridNum;

		const Path<Dual<double> > pathDual = makeDualPath(
			x0, mu, sigma, dt, gridNum, dualPathNum, shockType, seed);

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

		//case rrEnum:
		//	exposureFunctions = makeAnalyticRiskReversalExposures(
		//		mu, sigma, pathDual.gridNum(), maturity,
		//		payoff().gearing(), payoff().strike1(), pyoff()(strike2));
		//	break;
		}


		Dual<double> cvaValue = useImplicitMethod
			? calcCvaUsingImplicitExposure(
				exposureFunctions, pathDual, payoff, dt)
			: calcCvaUsingExplicitExposure(
				exposureFunctions, pathDual, dt);
		return cvaValue / static_cast<double>(pathNum);
	}
}
