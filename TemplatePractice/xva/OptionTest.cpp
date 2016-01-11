#include "Test.h"
#include "Path.h"
#include "Dual.h"
#include "PayOff.h"
#include <iostream>
#include <boost/numeric/ublas/io.hpp>   
#include "AnalyticOptionFunctions.h"

namespace ublas = boost::numeric::ublas;
namespace cva {
	void europeanTest()
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

		const double a = 1.0;
		const double b = -strike;
		Dual european;
		European eurPayoff(a, b);
		for (std::size_t i = 0; i < pathNum; ++i) {
			european += eurPayoff(path.getTimewisePath(i));
		}
		european /= pathNum;
		std::cout << "europeanOptionByAD(Monte) (value, deriv) =" 
			<< european.value() << ',' <<
			european.deriv() << std::endl;
		
		Dual europeanAnalytic
			= cva::europeanFunction(
				x0, mu, sigma, a, b, dt * gridNum);
		std::cout << "europeanOptionByAD(Analytic) (value, deriv) ="
			<< europeanAnalytic.value() << ',' 
			<< europeanAnalytic.deriv() << std::endl;

		Dual europeanDelta = cva::europeanDelta(x0, mu, sigma, a, b, dt * gridNum);
		std::cout << "europeanOptionDelta(Analytic) (Delta, Gamma) ="
			<< europeanDelta.value() << ',' << 
			europeanDelta.deriv() << std::endl;
	}
}