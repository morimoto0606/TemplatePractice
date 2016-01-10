#pragma once
#include "Functions.h"

namespace cva {
	//E[aX(t) + b]
	template <typename T>
	T forwardFunction(const T& x,
		const T& mu, const T& sigma,
		const double b,
		const double maturity) 
	{
		return a * x * cva::exp((mu - sigma * sigma / 2.0) * maturity ) + b;
	}

	//E[max(aX(t) + b, 0)]
	template <typename T>
	T europeanFunction(const T& x,
		const T& mu, const T& sigma,
		const double a, const double b,
		const double maturity) 
	{
		T dplus = (cva::log(x / (-(b / a)))
			+ (mu + sigma * sigma / 2.0) * maturity) 
			/ (sigma * std::sqrt(maturity));
		T dminus = dplus - sigma * std::sqrt(maturity);
		return (x * cva::exp(mu * maturity) * cva::normalCdf(dplus)
			+ cva::normalCdf(dminus) * (b / a)) * a;
	}

	//d/dx E[max(aX(t) + b, 0)]
	template <typename T>
	T europeanDelta(const T& x,
		const T& mu, const T& sigma,
		const double a, const double b,
		const double maturity)
	{
		T dplus = (cva::log(x / (-(b / a)))
			+ (mu + sigma * sigma / 2.0) * maturity)
			/ (sigma * std::sqrt(maturity));
		T dminus = dplus - sigma * std::sqrt(maturity);
		return cva::exp(mu * maturity) * cva::normalCdf(dplus) * a;
	}

} // namespace cva