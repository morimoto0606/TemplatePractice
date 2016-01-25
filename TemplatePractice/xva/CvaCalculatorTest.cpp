#include "Test.h"
#include "CvaCalculator.h"

namespace cva {

	//Forward 
	void 	calcCvaFwdTest()
	{
		std::cout << "CvaCalculatorTest" << std::endl;
		Forward payoff(1.0, 100.0);

		Dual<double> cvaExplicit =
			calcCvaByRegressionExposure<Forward, double>(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000,
				shockTypeEnum::undEnum, 1, false, false);
		std::cout << "cvaExplicit = " << cvaExplicit.value()
			<< ',' << "cvaExplicit deriv = " << cvaExplicit.deriv() << std::endl;

		Dual<double> cvaImplicit =
			calcCvaByRegressionExposure<Forward, double>(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000, 
				shockTypeEnum::undEnum, 1, true, false);
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
				Dual<double> valEUnd = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, undEnum, seed,
					false, false);
				Dual<double> valESigma = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, volEnum, seed,
					false, false);
				Dual<double> valIUnd = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, undEnum, seed,
					true, false);
				Dual<double> valISigma = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, volEnum, seed,
					true, false);
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
			calcCvaByRegressionExposure<European, double>(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000, 
				shockTypeEnum::undEnum, 1, false, false);
		std::cout << "cvaExplicit = " << cvaExplicit.value()
			<< ',' << "cvaExplicit deriv = " << cvaExplicit.deriv() << std::endl;

		Dual<double> cvaImplicit =
			calcCvaByRegressionExposure<European, double>(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000,
				shockTypeEnum::undEnum, 1, true, false);
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
				Dual<double> valEUnd = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, 
					undEnum, seed, false, false);
				Dual<double> valESigma = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, volEnum, seed,
					false, false);
				Dual<double> valIUnd = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, undEnum, seed,
					true, false);
				Dual<double> valISigma = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, volEnum, seed,
					true, false);
				Dual<double> valEUndShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, undEnum, seed,
					false, true);
				Dual<double> valESigmaShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, volEnum, seed,
					false, true);
				Dual<double> valIUndShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, undEnum, seed,
					true, true);
				Dual<double> valISigmaShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, pathNum, pathNum, volEnum, seed,
					true, true);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valEUndShock.value() << ',' << valIUnd.value() << ',' << valIUndShock.value() << ',' <<
					',' << valEUnd.deriv() << ',' << valEUndShock.deriv() << ',' << valIUnd.deriv() << ',' << valIUndShock.deriv() << ',' <<
					valESigma.deriv() << ',' << valESigmaShock.deriv() << ',' << valISigma.deriv()  << ','  << valISigmaShock.deriv() << std::endl;
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
		const double strike3, const double strike4,
		const double maturity, const std::size_t gridNum)
	{
		Mountain payoff(gearing, strike1, strike2, strike3, strike4);
		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "Mountain convergence test : analyticExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= 8; ++i) {
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

	void cvaMountainRegressionExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4,
		const double maturity, const std::size_t gridNum)
	{
		Mountain payoff(gearing, strike1, strike2, strike3, strike4);
		for (std::size_t seed = 1; seed <= 1; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "Mountain convergence test : RegressionExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= 8; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, pathNum, undEnum, seed,
					false, false);
				Dual<double> valESigma = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, pathNum, volEnum, seed,
					false, false);
				Dual<double> valIUnd = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, pathNum, undEnum, seed,
					true, false);
				Dual<double> valISigma = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, pathNum, pathNum, volEnum, seed,
					true, false);
				pathNum *= 2;
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//void cvaEuropeanRegressionExposure

	void cvaMountainTrueValueTest(const double gearing,
		const double strike1, const double strike2, 
		const double strike3, const double strike4,
		const double maturity, const std::size_t gridNum)
	{
		std::cout << "Cva Mountain True Value" << std::endl;
		Mountain payoff(gearing, strike1, strike2, strike3, strike4);
		Dual<double> eurDelta = calcCvaMountainByAnalytic(100, 0.0, 0.3,
			payoff, maturity, gridNum, undEnum);
		Dual<double> eurVega = calcCvaMountainByAnalytic(100, 0.0, 0.3,
			payoff, maturity, gridNum, volEnum);
		std::cout << eurDelta.value() << ',' << eurDelta.deriv() <<
			',' << eurVega.deriv() << std::endl;
	} //	cvaMountainTrueValue
} //namespace cva