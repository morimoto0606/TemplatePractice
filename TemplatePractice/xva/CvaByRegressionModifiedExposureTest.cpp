#include "CvaCalculator.h"
#include "RegressionExposure.h"

#include "Test.h"

namespace cva {
	void cvaEuropeanRegressionModifiedExposureTest(const double gearing,
		const double strike, const double shiftAmount,
		const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum, const std::size_t numOfBasis,
		const std::size_t pathLoop, const LoopTypeEnum loopType)
	{
		European payoff(gearing, strike, shiftAmount);
		for (std::size_t seed = 1; seed <= seedLoop; ++seed) {
			std::size_t pathNum = 1000;
			std::cout << "European convergence test : RegressionExposure" << std::endl;
			std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
			for (std::size_t i = 1; i <= pathLoop; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure<European, double>(
					100, 0.0, 0.3, payoff, 10.0, 10, regNum, pathNum, numOfBasis,
					undEnum, seed, false, false, 
					EuropeanCalculator(0.0, gearing, strike, shiftAmount, 10));
				if (loopType == pathEnum) { pathNum *= 2; }
				else if (loopType == regressionEnum) { regNum *= 2; }
				else {
					pathNum *= 2;
					regNum *= 2;
				}							
				std::cout << valEUnd.value() << std::endl;
			}
		}
	}//void cvaEuropeanRegressionExposure

	void cvaMountainRegressionModifiedExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4,
		const double shiftAmount,
		const double maturity, const std::size_t gridNum, 
		const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum, const std::size_t numOfBasis,
		const std::size_t pathLoop, const LoopTypeEnum loopType)
	{
		Mountain payoff(gearing, strike1, strike2, strike3, strike4, shiftAmount);
		std::cout << "Mountain convergence test : RegressionExposure" << std::endl;
		std::cout << "valEUnd, valIUnd, valEdx, valIdx, valEdsigma, valIdsigma" << std::endl;
		for (std::size_t seed = 1; seed <= seedLoop; ++seed) {
			for (std::size_t i = 1; i <= pathLoop; ++i) {
				Dual<double> valEUnd = calcCvaByRegressionExposure<Mountain, double>(
					100, 0.0, 0.3, payoff, maturity, gridNum, regNum, pathNum, numOfBasis, undEnum, seed,
					false, false);
				if (loopType == pathEnum) { pathNum *= 2; }
				else if (loopType == regressionEnum) { regNum *= 2; }
				else {
					pathNum *= 2;
					regNum *= 2;
				}			
				std::cout << valEUnd.value() << ',' << std::endl;
			}
		}
	}//void cvaEuropeanRegressionExposure




} //namespace cva