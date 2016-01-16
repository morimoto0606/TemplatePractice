#include "Regression.h"
#include "Test.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include "Dual.h"


namespace cva {

	void regressionTest()
	{
		//regression double
		{
			ublas::vector<boost::function<double(const double&)> >  functions(3);
			for (std::size_t i = 0; i < 3; ++i) {
				functions(i) = boost::function<double(const double&)>
					(Monomial(static_cast<double>(i)));
			}

			const double x0(100.0);
			const double mu(0.0);
			const double sigma(0.1);
			const std::size_t pathNum = 10000;
			const std::size_t gridNum = 2;
			const double dt = 0.5;
			const std::size_t seed = 2;
			const Path<double> path(x0, mu, sigma, pathNum,
				gridNum, dt, seed);

			std::size_t gridIndex = 1;
			Forward payoffFwd(1.0, -100.0);
			European payoffEur(1.0, -100.0);


			//ublas::matrix<double> z = getBasisMatrix(2.0, functions);
			ublas::vector<double> coeff;
			coeff = regresssion(gridIndex, payoffFwd, path,	functions);
			std::cout << "Regression payoff = Forward, mu = 0, sigma = 0.3 " << coeff << std::endl;
			coeff = regresssion(gridIndex, payoffEur, path, functions);
			std::cout << "Regression payoff = European, mu = 0, sigma = 0.3 " << coeff << std::endl;
		}

		////regression Dual<double>
		//{
		//	ublas::vector<boost::function<Dual<double>(const Dual<double>&)> >  dualFunctions(3);
		//	for (std::size_t i = 0; i < 3; ++i) {
		//		dualFunctions(i) = boost::function<Dual<double>(const Dual<double>&)>
		//			(Monomial(static_cast<double>(i)));
		//	}
		//	const Dual<double> x0(100.0, 1.0);
		//	const Dual<double> mu(0.1);
		//	const Dual<double> sigma(0.3);
		//	const std::size_t pathNum = 1000;
		//	const std::size_t gridNum = 2;
		//	const double dt = 0.5;
		//	const std::size_t seed = 2;
		//	const Path<Dual<double>> dualPath(x0, mu, sigma, pathNum,
		//		gridNum, dt, seed);

		//	std::size_t gridIndex = 1;
		//	European payoff(1.0, -1.0);
		//	ublas::matrix<Dual<double> > z = getBasisMatrix(Dual<double>(2.0, 1.0), dualFunctions);
		//
		//	ublas::vector<Dual<double> > coeff = regresssion(gridIndex, payoff, dualPath,
		//		dualFunctions);

		//}
	}
}