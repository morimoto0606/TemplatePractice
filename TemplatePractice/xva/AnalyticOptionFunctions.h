#pragma once
#include "Functions.h"
#include <boost/numeric/ublas/vector.hpp>

namespace ublas = boost::numeric::ublas;
namespace cva {
	//E[aX(t) + b]
	template <typename T>
	T forwardFunction(const T& x,
		const T& mu, const T& sigma,
		const double a,
		const double b,
		const double maturity) 
	{
		return a * x 	* cva::exp(mu	* maturity ) - b;
	}

	//E[max(aX(t) + b, 0) + c] 
	template <typename T>
	T europeanFunction(const T& x,
		const T& mu, const T& sigma,
		const double a, const double b,
		const double c,
		const double maturity) 
	{
		if (maturity == 0.0) {
			return cva::zeroFloor(a * x - b) + c;
		}
		T dplus = (cva::log(x / (b / a))
			+ (mu + sigma * sigma / 2.0) * maturity) 
			/ (sigma * std::sqrt(maturity));
		T dminus = dplus 
			- sigma * std::sqrt(maturity);
		return (x * cva::exp(mu * maturity) 
			* cva::normalCdf(dplus)
			+ cva::normalCdf(dminus) * (-b / a)) * a + c;
	}

	//d/dx E[max(aX(t) + b, 0)]
	template <typename T>
	T europeanDelta(const T& x,
		const T& mu, const T& sigma,
		const double a, const double b,
		const double maturity)
	{
		T dplus = (cva::log(x / (b / a))
			+ (mu + sigma * sigma / 2.0) * maturity)
			/ (sigma * std::sqrt(maturity));
		T dminus = dplus - sigma 
			* std::sqrt(maturity);
		
		return cva::exp(mu * maturity)
			* cva::normalCdf(dplus) * a;
	}

	//E[max(aX(t) + b1, 0)] - E[max(-aX(t) - b2, 0)]
	template <typename T>
	T riskReversal(const T& x,
		const T& mu, const T& sigma,
		const double a, const double b1,
		const double b2,
		const double maturity)
	{
		//b1 > b2 >0
		return europeanFunction(x, mu, sigma, a, b1, 0.0,maturity)
			- europeanFunction(x, mu, sigma, -a, b2, 0.0, maturity);
	}

	//   E[max(aX(t) + b1, 0)] - E[max(aX(t) + b2, 0)]
	//+E[max(aX(t) + b1, 0)] - E[max(aX(t) + b2, 0)] + c
	template <typename T>
	T mountain(const T& x,
		const T& mu, const T& sigma,
		const double a, 
		const ublas::vector<double>& strikes,
		const double c,
		const double maturity)
	{
		//b1 < b2 < b3 < b4
		return europeanFunction(x, mu, sigma, a, strikes(0), 0.0, maturity)
			- europeanFunction(x, mu, sigma, a, strikes(1), 0.0, maturity)
			- europeanFunction(x, mu, sigma, a, strikes(2), 0.0, maturity)
			+ europeanFunction(x, mu, sigma, a, strikes(3), 0.0, maturity) + c;
	}
} // namespace cva