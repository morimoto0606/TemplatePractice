#include "Regression.h"
#include "Test.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include "Dual.h"


namespace cva {

	double h0(const double& x) {
		return 1.0;
	}
	double h1(const double& x) {
		return x;
	}
	double h2(const double x) {
		return x * x;
	}

	Dual w0(const Dual& x) {
		return Dual(1.0);
	}
	Dual w1(const Dual& x) {
		return x;
	}
	Dual w2(const Dual x) {
		return x * x;
	}

	void regressionTest()
	{

		{
			ublas::vector<boost::function<double(const double&)> >  functions(3);
			boost::function<double(const double&)> function0 = &h0;
			boost::function<double(const double&)> function1 = &h1;
			boost::function<double(const double&)> function2 = &h2;
			functions(0) = function0;
			functions(1) = function1;
			functions(2) = function2;

			const double x0(100.0);
			const double mu(0.1);
			const double sigma(0.3);
			const std::size_t pathNum = 1000;
			const std::size_t gridNum = 2;
			const double dt = 0.5;
			const std::size_t seed = 2;
			const Path<double> path(x0, mu, sigma, pathNum,
				gridNum, dt, seed);

			std::size_t gridIndex = 1;
			European payoff(1.0, -1.0);


			ublas::matrix<double> z = getBasisMatrix(2.0, functions);
			ublas::vector<double> coeff = regresssion(gridIndex, payoff, path,
				functions);
		}

		{
			ublas::vector<boost::function<Dual(const Dual&)> >  dualFunctions(3);
			boost::function<Dual(const Dual&)> dualFunction0 = &w0;
			boost::function<Dual(const Dual&)> dualFunction1 = &w1;
			boost::function<Dual(const Dual&)> dualFunction2 = &w2;
			dualFunctions(0) = dualFunction0;
			dualFunctions(1) = dualFunction1;
			dualFunctions(2) = dualFunction2;

			const Dual x0(100.0, 1.0);
			const Dual mu(0.1);
			const Dual sigma(0.3);
			const std::size_t pathNum = 1000;
			const std::size_t gridNum = 2;
			const double dt = 0.5;
			const std::size_t seed = 2;
			const Path<Dual> dualPath(x0, mu, sigma, pathNum,
				gridNum, dt, seed);

			std::size_t gridIndex = 1;
			European payoff(1.0, -1.0);
			//ublas::vector<Dual> coeff = regresssion(gridIndex, payoff, dualPath,
			//	dualFunctions);

		}
	}
}