#include "Test.h"
#include "Path.h"
#include "Dual.h"
#include <iostream>
#include <boost/numeric/ublas/io.hpp>   
#include "AnalyticOptionFunctions.h"
namespace ublas = boost::numeric::ublas;
namespace cva {
	void pathTest()
	{
		const Dual<double> x0(100.0, 1.0);
		const Dual<double> mu(0.2);
		const Dual<double> sigma(0.5);
		const std::size_t pathNum = 100000;
		const std::size_t gridNum = 1;
		const double dt = 1;
		const std::size_t seed = 1;
		const Path<Dual<double>> path(
			x0, mu, sigma, pathNum,
			gridNum, dt, seed);

		const double strike = 100.0;
		double logMean = 0.0;
		double logMeanSquare = 0.0;
		for (std::size_t i = 0; i < pathNum; ++i) {
			logMean += std::log(
				path.getPathValue(
					i, gridNum).value() / 100.0);
			logMeanSquare += std::pow(
				std::log(path.getPathValue(
					i, gridNum).value() / 100.0), 2.0);
		}
		logMean /= pathNum;
		const double var 
			= logMeanSquare / pathNum - std::pow(logMean, 2.0);
		std::cout << "pathTest  (logMean =mu(0.2) - sigma^2/2= 0.075), logVar (= sigma(0.5)) = " 
			<< logMean << ',' << std::sqrt(var) << std::endl;
	}
}