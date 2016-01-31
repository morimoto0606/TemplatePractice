#include "CvaCalculator.h"
#include "AnalyticExposure.h"

namespace cva {

	void calcCvaByAnalyticExposureTest()
	{
		std::cout << "CvaCalculatorTest" << std::endl;
		Forward payoff(1.0, 100.0);

		Dual<double> cvaFwdAnalyticEx =
			calcCvaByAnalyticExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1,
				productTypeEnum::eurEnum, false);
		std::cout << "cvaByAnalyticForwardExplict = " << cvaFwdAnalyticEx.value()
			<< ',' << "cvaByAnalyticForwardExplict deriv = " << cvaFwdAnalyticEx.deriv() << std::endl;

		Dual<double> cvaFwdAnalyticIm =
			calcCvaByAnalyticExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1,
				productTypeEnum::eurEnum, true);

		std::cout << "CvaCalculatorTest" << std::endl;
		European payoffE(1.0, 100.0);

			Dual<double> cvaEurAnalyticEx =
				calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoffE, 10.0, 10, 1000, shockTypeEnum::undEnum, 1,
					productTypeEnum::eurEnum, false);
			std::cout << "cvaByAnalyticEuropeanExplict = " << cvaEurAnalyticEx.value()
				<< ',' << "cvaByAnalyticEuropeanExplict deriv = " << cvaEurAnalyticEx.deriv() << std::endl;

			Dual<double> cvaEurAnalyticIm =
				calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoffE, 10.0, 10, 1000, shockTypeEnum::undEnum, 1,
					productTypeEnum::eurEnum, true);
			std::cout << "cvaByAnalyticEuropeanImplict= " << cvaEurAnalyticIm.value()
				<< ',' << "cvaByAnalyticEuropeanImplict deriv = " << cvaEurAnalyticIm.deriv() << std::endl;
	}//	void calcCvaEurTest()


	void cvaForwardAnalyticExposureTest(const double gearing,
		const double strike, std::size_t pathNum, const std::size_t seedLoop,
		const std::size_t pathLoop)
	{
		Forward payoff(gearing, strike);

		std::cout << "Forward convergence test : analyticExposure" << std::endl;
		std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;

		for (std::size_t seed = 1; seed <= seedLoop; ++seed) {
			std::size_t pathNum = 1000;
			for (std::size_t i = 1; i <= pathLoop; ++i) {
				Dual<double> valEUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					fwdEnum, false);
				Dual<double> valESigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					fwdEnum, false);
				Dual<double> valIUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					fwdEnum, true);
				Dual<double> valISigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					fwdEnum, true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}// cvaForwardAnalyticExposure

	void cvaEuropeanAnalyticExposureTest(const double gearing,
		const double strike, const double payoffShift, 
		std::size_t pathNum, const std::size_t seedLoop,
		const std::size_t pathLoop)
	{
		European payoff(gearing, strike, payoffShift);
		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "European convergence test : analyticExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= 8; ++i) {
				Dual<double> valEUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					eurEnum, false);
				Dual<double> valESigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					eurEnum, false);
				Dual<double> valIUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					eurEnum, true);
				Dual<double> valISigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					eurEnum, true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//	void cvaEuropeanAnalyticExposure

	void cvaMountainAnalyticExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4,
		const double payoffShift,
		const double maturity, const std::size_t gridNum, 
		std::size_t pathNum, const std::size_t seedLoop,
		const std::size_t pathLoop)
	{
		Mountain payoff(gearing, strike1, strike2, strike3, strike4, payoffShift);
		std::cout << "Mountain convergence test : analyticExposure" << std::endl;
		std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
		for (std::size_t seed = 1; seed <= seedLoop; ++seed) {
			for (std::size_t i = 1; i <= pathLoop; ++i) {
				Dual<double> valEUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, undEnum, seed,
					mountainEnum, false);
				Dual<double> valESigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, volEnum, seed,
					mountainEnum, false);
				Dual<double> valIUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, undEnum, seed,
					mountainEnum, true);
				Dual<double> valISigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, volEnum, seed,
					mountainEnum, true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//	void cvaMountainAnalyticExposure

} //namespace cva