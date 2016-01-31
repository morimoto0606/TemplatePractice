#include "CvaCalculator.h"
#include "RegressionExposure.h"

#include "Test.h"

namespace cva {
	//Forward 
	void 	calcCvaByRegressionExposureTest()
	{
		std::cout << "CvaCalculatorTest" << std::endl;
		Forward payoff(1.0, 100.0);

		Dual<double> cvaExplicit =
			calcCvaByRegressionExposure<Forward, double>(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000,
				shockTypeEnum::undEnum, 1, false, false);
		std::cout << "cvaExplicit = " << cvaExplicit.value()
			<< ',' << "cvaExplicit deriv = " << cvaExplicit.deriv() << std::endl;

		Dual<double>  cvaImplicit =
			calcCvaByRegressionExposure<Forward, double>(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000, 
				shockTypeEnum::undEnum, 1, true, false);
		std::cout << "cvaImplict = " << cvaImplicit.value()
			<< ',' << "cvaImplicit deriv = " << cvaImplicit.deriv() << std::endl;

		std::cout << "CvaCalculatorTest" << std::endl;
		European payoffE(1.0, 100.0);

		cvaExplicit =
			calcCvaByRegressionExposure<European, double>(
				100, 0.0, 0.3, payoffE, 10.0, 10, 1000, 1000, 
				shockTypeEnum::undEnum, 1, false, false);
		std::cout << "cvaExplicit = " << cvaExplicit.value()
			<< ',' << "cvaExplicit deriv = " << cvaExplicit.deriv() << std::endl;
		
		cvaImplicit =
			calcCvaByRegressionExposure<European, double>(
				100, 0.0, 0.3, payoffE, 10.0, 10, 1000, 1000,
				shockTypeEnum::undEnum, 1, true, false);
		std::cout << "cvaImplict = " << cvaImplicit.value()
			<< ',' << "cvaImplicit deriv = " << cvaImplicit.deriv() << std::endl;

	}
	

	void cvaForwardRegressionExposureTest(const double gearing,
		const double strike, const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum,
		const std::size_t pathLoop, const LoopTypeEnum loopType)
	{
		Forward payoff(gearing, strike);
		std::cout << "Forward convergence test : RegressionExposure" << std::endl;
		std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;

		for (std::size_t seed = 1; seed <= seedLoop; ++seed) {
			for (std::size_t i = 1; i <= pathLoop; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, undEnum, seed,
					false, false);
				Dual<double> valESigma = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, volEnum, seed,
					false, false);
				Dual<double> valIUnd = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, undEnum, seed,
					true, false);
				Dual<double> valISigma = calcCvaByRegressionExposure<Forward, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, volEnum, seed,
					true, false);
				if (loopType == pathEnum) { pathNum *= 2; }
				else if (loopType == regressionEnum) { regNum *= 2; }
				else { 
					pathNum *= 2;
					regNum *= 2;
				}				
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//cvaForwardRegressionExposure


	void cvaEuropeanRegressionExposureTest(const double gearing,
		const double strike, const double shiftAmount,
		const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum,
		const std::size_t pathLoop, const LoopTypeEnum loopType)
	{
		European payoff(gearing, strike, shiftAmount);
		for (std::size_t seed = 1; seed <= seedLoop; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "European convergence test : RegressionExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= pathLoop; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum,
					undEnum, seed, false, false);
				Dual<double> valESigma = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, volEnum, seed,
					false, false);
				Dual<double> valIUnd = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, undEnum, seed,
					true, false);
				Dual<double> valISigma = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, volEnum, seed,
					true, false);
				Dual<double> valEUndShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, undEnum, seed,
					false, true);
				Dual<double> valESigmaShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, volEnum, seed,
					false, true);
				Dual<double> valIUndShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, undEnum, seed,
					true, true);
				Dual<double> valISigmaShock = calcCvaByRegressionExposure<European, Dual<double> >(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, volEnum, seed,
					true, true);
				if (loopType == pathEnum) { pathNum *= 2; }
				else if (loopType == regressionEnum) { regNum *= 2; }
				else {
					pathNum *= 2;
					regNum *= 2;
				}							
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//void cvaEuropeanRegressionExposure

	void cvaMountainRegressionExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4,
		const double shiftAmount,
		const double maturity, const std::size_t gridNum, 
		const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum,
		const std::size_t pathLoop, const LoopTypeEnum loopType)
	{
		Mountain payoff(gearing, strike1, strike2, strike3, strike4, shiftAmount);
		std::cout << "Mountain convergence test : RegressionExposure" << std::endl;
		std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
		for (std::size_t seed = 1; seed <= seedLoop; ++seed) {
			for (std::size_t i = 1; i <= pathLoop; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, regNum, pathNum, undEnum, seed,
					false, false);
				Dual<double> valESigma = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, regNum, pathNum, volEnum, seed,
					false, false);
				Dual<double> valIUnd = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, regNum, pathNum, undEnum, seed,
					true, false);
				Dual<double> valISigma = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, regNum, pathNum, volEnum, seed,
					true, false);
				if (loopType == pathEnum) { pathNum *= 2; }
				else if (loopType == regressionEnum) { regNum *= 2; }
				else {
					pathNum *= 2;
					regNum *= 2;
				}			
				std::cout << valEUnd.value() << ',' << valIUnd.value() <<
					',' << valEUnd.deriv() << ',' << valIUnd.deriv() << ',' <<
					valESigma.deriv() << ',' << valISigma.deriv() << std::endl;
			}
		}
	}//void cvaEuropeanRegressionExposure




} //namespace cva