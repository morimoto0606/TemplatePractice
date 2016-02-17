#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>

namespace cva {
	enum LoopTypeEnum { pathEnum, regressionEnum, bothEnum };
	void pathTest();
	void europeanTest();
	void payoffTest();
	void payoffCrtpTest();
	void payoffDerivTest();
	void dualTest();
	void dualVectorTest();
	void dualCompositionTest();

	void lsmFunctionTest();
	void regressionTest();
	void optionByLsmTest();
	void greeksByLsmTest();
	void calcCvaByRegressionExposureTest();
	void calcCvaByAnalyticExposureTest();

	void cvaForwardAnalyticExposureTest(const double gearing,
		const double strike,
		std::size_t pathNum, const std::size_t seedLoop,
		const std::size_t pathLoop);

	void cvaForwardRegressionExposureTest(const double gearing,
		const double strike, const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum, const std::size_t numOfBasis,
		const std::size_t pathLoop, const LoopTypeEnum loopType);

	void cvaForwardTrueValueTest(const double gearing,
		const double strike);

	void cvaEuropeanAnalyticExposureTest(const double gearing,
		const double strike, const double payoffShift,
		std::size_t pathNum, const std::size_t seedLoop,
		const std::size_t pathLoop);

	void cvaEuropeanRegressionExposureTest(const double gearing,
		const double strike, const double payoffShift,
		const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum, const std::size_t numOfBasis,
		const std::size_t pathLoop, const LoopTypeEnum loopType);

	void cvaEuropeanTrueValueTest(const double gearing,
		const double strike);

	void cvaMountainTrueValueTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4,
		const double maturity, const std::size_t gridNum);

	void cvaMountainAnalyticExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4,
		const double payoffShift,
		const double maturity, const std::size_t gridNum,
		std::size_t pathNum, const std::size_t seedLoop,
		const std::size_t pathLoop);

	void cvaMountainRegressionExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4,
		const double payoffShift,
		const double maturity, const std::size_t gridNum,
		const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum, const std::size_t numOfBasis,
		const std::size_t pathLoop, const LoopTypeEnum loopType);

	void cvaEuropeanRegressionModifiedExposureTest(const double gearing,
		const double strike, const double shiftAmount,
		const std::size_t seedLoop,
		std::size_t  pathNum, std::size_t regNum, const std::size_t numOfBasis,
		const std::size_t pathLoop, const LoopTypeEnum loopType);
}
#endif