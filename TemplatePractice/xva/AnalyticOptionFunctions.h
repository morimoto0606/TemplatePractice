#pragma once
#include "Functions.h"

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

	//E[max(aX(t) + b, 0)]
	template <typename T>
	T europeanFunction(const T& x,
		const T& mu, const T& sigma,
		const double a, const double b,
		const double maturity) 
	{
		if (maturity == 0.0) {
			return cva::zeroFloor(a * x - b);
		}
		T dplus = (cva::log(x / (b / a))
			+ (mu + sigma * sigma / 2.0) * maturity) 
			/ (sigma * std::sqrt(maturity));
		T dminus = dplus 
			- sigma * std::sqrt(maturity);
		return (x * cva::exp(mu * maturity) 
			* cva::normalCdf(dplus)
			+ cva::normalCdf(dminus) * (-b / a)) * a;
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
		return europeanFunction(x, mu, sigma, a, b1, maturity)
			- europeanFunction(x, mu, sigma, -a, b2, maturity);
	}

	//   E[max(aX(t) + b1, 0)] - E[max(aX(t) + b2, 0)]
	//+E[max(aX(t) + b1, 0)] - E[max(aX(t) + b2, 0)]
	template <typename T>
	T mountain(const T& x,
		const T& mu, const T& sigma,
		const double a, const double b1,
		const double b2, const double b3, 
		const double b4,
		const double maturity)
	{
		//b1 < b2 < b3 < b4
		return europeanFunction(x, mu, sigma, a, b1, maturity)
			- europeanFunction(x, mu, sigma, a, b2, maturity)
			- europeanFunction(x, mu, sigma, a, b3, maturity)
			+ europeanFunction(x, mu, sigma, a, b4, maturity);
	}
} // namespace cva