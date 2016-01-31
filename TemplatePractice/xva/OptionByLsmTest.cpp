#include "Regression.h"
#include "PayOff.h"
#include "AnalyticOptionFunctions.h"
#include "LsmFunction.h"
#include "AnalyticOptionFunctions.h"

namespace cva {
	void optionByLsmTest()
	{
		//regression double
		{
			std::cout << "OptionByLsmTest" << std::endl;
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

			std::size_t gridIndex = 2;
			Forward payoffFwd(1.0, 100.0);
			European payoffEur(1.0, 100.0);

			ublas::vector<double> coeff;
			coeff = regresssion(gridIndex, payoffFwd, path, functions);
			LsmFunction<double, double> lsmFwd(coeff, functions);
			double optionPremByLsm = lsmFwd(x0);
			double optionPremByAnalytic = forwardFunction(x0, mu, sigma, 1.0, 100.0, 0.5);
			std::cout << "ForwardByLsm = " << optionPremByLsm
				<< ',' << "ForwardByAnalytic = " << optionPremByAnalytic <<   std::endl;

			coeff = regresssion(gridIndex, payoffEur, path, functions);
			LsmFunction<double, double> lsmEur(coeff, functions);
			optionPremByLsm = lsmEur(x0);
			optionPremByAnalytic = europeanFunction(
				x0, mu, sigma, 1.0, 100.0, 0.0, 0.5);

			std::cout << "EuropeanByLsm = " << optionPremByLsm
				<< ',' << "EuropeanByAnalytic = " << optionPremByAnalytic << std::endl;
		}
	}

	void greeksByLsmTest()
	{
		//regression double
		{
			std::cout << "GreeksByLsmTest" << std::endl;
			
			ublas::vector<boost::function<double(const double&)> >  functions(3);
			for (std::size_t i = 0; i < 3; ++i) {
				functions(i) = boost::function<double(const double&)>
					(Monomial(static_cast<double>(i)));
			}
			ublas::vector<boost::function<Dual<double>(const Dual<double>&)> >  dualFunctions(3);
			for (std::size_t i = 0; i < 3; ++i) {
				dualFunctions(i) = boost::function<Dual<double>(const Dual<double>&)>
					(Monomial(static_cast<double>(i)));
			}

			const double x0(100.0);
			const double mu(0.0);
			const double sigma(0.1);
			const Dual<double> x0Dual(x0, 1.0);
			const Dual<double> muDual(mu, 0.0);
			const Dual<double> sigmaDual(sigma, 0.0);
			const std::size_t pathNum = 10000;
			const std::size_t gridNum = 2;
			const double dt = 0.5;
			const std::size_t seed = 2;
			const Path<double> path(x0, mu, sigma, pathNum,
				gridNum, dt, seed);
			const Path<Dual<double> > pathDual(x0Dual, muDual, sigmaDual, pathNum,
				gridNum, dt, seed);

			std::size_t gridIndex = 1;
			Forward payoffFwd(1.0, 100.0);
			European payoffEur(1.0, 100.0);

			ublas::vector<double> coeff;
			coeff = regresssion(gridIndex, payoffFwd, path, functions);

			LsmFunction<Dual<double>, double> lsmFwd(coeff, dualFunctions);
			Dual<double> optionPremByLsm = lsmFwd(x0Dual);
			Dual<double> optionPremByAnalytic = forwardFunction(x0Dual, muDual, sigmaDual, 1.0, -100.0, 0.5);
			std::cout << "ForwardByLsm = " << optionPremByLsm.value() << ',' << optionPremByLsm.deriv()
				<< ',' << "ForwardByAnalytic = " << optionPremByAnalytic.value() << ',' << optionPremByAnalytic.deriv() << std::endl;

			coeff = regresssion(gridIndex, payoffEur, path, functions);
			LsmFunction<Dual<double>, double> lsmEur(coeff, dualFunctions);
			optionPremByLsm = lsmEur(x0Dual);
			optionPremByAnalytic = europeanFunction(
				x0Dual, muDual, sigmaDual, 1.0, 100.0, 0.0, 0.5);

			std::cout << "EuropeanByLsm = " << optionPremByLsm.value() << ','<< optionPremByLsm.deriv()
				<< ',' << "EuropeanByAnalytic = " << optionPremByAnalytic.value() << ',' << optionPremByAnalytic.deriv() << std::endl;
		}
	}
}