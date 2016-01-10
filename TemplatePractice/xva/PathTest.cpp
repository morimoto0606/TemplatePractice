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
		const Dual x0(100.0, 1.0);
		const Dual mu(0.1);
		const Dual sigma(0.3);
		const std::size_t pathNum = 1000;
		const std::size_t gridNum = 1;
		const double dt = 1;
		const std::size_t seed = 1;
		const Path<Dual> path(x0, mu, sigma, pathNum,
			gridNum, dt, seed);

		const double strike = 100.0;
		double logMean = 0.0;
		double logMeanSquare = 0.0;
		for (std::size_t i = 0; i < pathNum; ++i) {
			logMean += std::log(path.getPathValue(i, gridNum).value() / 100.0);
			logMeanSquare += std::pow(std::log(path.getPathValue(i, gridNum).value() / 100.0), 2.0);
		}
		logMean /= pathNum;
		const double var = logMeanSquare / pathNum - std::pow(logMean, 2.0);
		std::cout << "pathTest" << logMean << ',' << var << std::endl;
	}
}