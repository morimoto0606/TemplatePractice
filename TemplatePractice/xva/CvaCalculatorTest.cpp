#include "Test.h"
#include "CvaCalculator.h"

namespace cva {

	//Forward 
	void 	calcCvaFwdTest()
	{
		std::cout << "CvaCalculatorTest" << std::endl;
		Forward payoff(1.0, 100.0);

		Dual<double> cvaExplicit =
			calcCvaByRegressionExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1, false);
		std::cout << "cvaExplicit = " << cvaExplicit.value()
			<< ',' << "cvaExplicit deriv = " << cvaExplicit.deriv() << std::endl;

		Dual<double> cvaImplicit =
			calcCvaByRegressionExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1, true);
		std::cout << "cvaImplict = " << cvaImplicit.value()
			<< ',' << "cvaImplicit deriv = " << cvaImplicit.deriv() << std::endl;

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
	}//	void 	calcCvaFwdTest()


	void cvaForwardAnalyticExposureTest(const double gearing,
		const double strike)
	{
		Forward payoff(gearing, strike);

		std::cout << "Forward convergence test : analyticExposure" << std::endl;
		std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;

		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			for (std::size_t i = 1; i <= 8; ++i) {
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

	void cvaForwardRegressionExposureTest(const double gearing,
		const double strike)
	{
		Forward payoff(gearing, strike);
		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "Forward convergence test : RegressionExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= 8; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					false);
				Dual<double> valESigma = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					false);
				Dual<double> valIUnd = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					true);
				Dual<double> valISigma = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//cvaForwardRegressionExposure

	void cvaForwardTrueValueTest(const double gearing,
		const double strike)
	{
		std::cout << "Cva Forward True Value" << std::endl;
		Forward payoffFwd(gearing, strike);
		Dual<double> fwdDelta = calcCvaFwdByAnalytic(100, 0.0, 0.3,
			payoffFwd, 10.0, 10, undEnum);
		Dual<double> fwdVega = calcCvaFwdByAnalytic(100, 0.0, 0.3,
			payoffFwd, 10.0, 10, volEnum);
		std::cout << fwdDelta.value() << ',' << fwdDelta.deriv() <<
			',' << fwdVega.deriv() << std::endl;

	} //	cvaForwardTrueValue

	//European
	void calcCvaEurTest()
	{
		std::cout << "CvaCalculatorTest" << std::endl;
		European payoff(1.0, 100.0);

		Dual<double> cvaExplicit =
			calcCvaByRegressionExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1, false);
		std::cout << "cvaExplicit = " << cvaExplicit.value()
			<< ',' << "cvaExplicit deriv = " << cvaExplicit.deriv() << std::endl;

		Dual<double> cvaImplicit =
			calcCvaByRegressionExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1, true);
		std::cout << "cvaImplict = " << cvaImplicit.value()
			<< ',' << "cvaImplicit deriv = " << cvaImplicit.deriv() << std::endl;

		Dual<double> cvaEurAnalyticEx =
			calcCvaByAnalyticExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1,
				productTypeEnum::eurEnum, false);
		std::cout << "cvaByAnalyticEuropeanExplict = " << cvaEurAnalyticEx.value()
			<< ',' << "cvaByAnalyticEuropeanExplict deriv = " << cvaEurAnalyticEx.deriv() << std::endl;

		Dual<double> cvaEurAnalyticIm =
			calcCvaByAnalyticExposure(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, shockTypeEnum::undEnum, 1,
				productTypeEnum::eurEnum, true);
		std::cout << "cvaByAnalyticEuropeanImplict= " << cvaEurAnalyticIm.value()
			<< ',' << "cvaByAnalyticEuropeanImplict deriv = " << cvaEurAnalyticIm.deriv() << std::endl;
	}//	void calcCvaEurTest()


	void cvaEuropeanAnalyticExposureTest(const double gearing,
		const double strike)
	{
		European payoff(gearing, strike);
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

	void cvaEuropeanRegressionExposureTest(const double gearing,
		const double strike)
	{
		European payoff(gearing, strike);
		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "European convergence test : RegressionExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= 8; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					false);
				Dual<double> valESigma = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					false);
				Dual<double> valIUnd = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					true);
				Dual<double> valISigma = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//void cvaEuropeanRegressionExposure

	void cvaEuropeanTrueValueTest(const double gearing,
		const double strike)
	{
		std::cout << "Cva European True Value" << std::endl;
		European payoffEur(gearing, strike);
		Dual<double> eurDelta = calcCvaEurByAnalytic(100, 0.0, 0.3,
			payoffEur, 10.0, 10, undEnum);
		Dual<double> eurVega = calcCvaEurByAnalytic(100, 0.0, 0.3,
			payoffEur, 10.0, 10, volEnum);
		std::cout << eurDelta.value() << ',' << eurDelta.deriv() <<
			',' << eurVega.deriv() << std::endl;
	} //	cvaEuropeanTrueValue


	void cvaMountainAnalyticExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4)
	{
		Mountain payoff(gearing, strike1, strike2, strike3, strike4);
		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "Mountain convergence test : analyticExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= 8; ++i) {
				Dual<double> valEUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					mountainEnum, false);
				Dual<double> valESigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					mountainEnum, false);
				Dual<double> valIUnd = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					mountainEnum, true);
				Dual<double> valISigma = calcCvaByAnalyticExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					mountainEnum, true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//	void cvaMountainAnalyticExposure

	void cvaMountainRegressionExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4)
	{
		Mountain payoff(gearing, strike1, strike2, strike3, strike4);
		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "Mountain convergence test : RegressionExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= 8; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					false);
				Dual<double> valESigma = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					false);
				Dual<double> valIUnd = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, undEnum, seed,
					true);
				Dual<double> valISigma = calcCvaByRegressionExposure(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, volEnum, seed,
					true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//void cvaEuropeanRegressionExposure

	void cvaMountainTrueValueTest(const double gearing,
		const double strike1, const double strike2, 
		const double strike3, const double strike4)
	{
		std::cout << "Cva Mountain True Value" << std::endl;
		Mountain payoff(gearing, strike1, strike2, strike3, strike4);
		Dual<double> eurDelta = calcCvaMountainByAnalytic(100, 0.0, 0.3,
			payoff, 10.0, 10, undEnum);
		Dual<double> eurVega = calcCvaMountainByAnalytic(100, 0.0, 0.3,
			payoff, 10.0, 10, volEnum);
		std::cout << eurDelta.value() << ',' << eurDelta.deriv() <<
			',' << eurVega.deriv() << std::endl;
	} //	cvaMountainTrueValue
} //namespace cva