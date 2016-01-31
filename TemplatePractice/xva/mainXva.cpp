
#include "Test.h"


int main()
{
	cva::pathTest();
	cva::europeanTest();
	cva::payoffTest();
	cva::dualTest();
	cva::dualVectorTest();
	cva::dualCompositionTest();
	cva::lsmFunctionTest();
	cva::regressionTest();
	cva::optionByLsmTest();
	cva::greeksByLsmTest();
	
	cva::calcCvaByRegressionExposureTest();
	cva::calcCvaByAnalyticExposureTest();
	
	cva::cvaForwardTrueValueTest(1.0, 100.0);
	cva::cvaEuropeanTrueValueTest(1.0, 100.0);
	cva::cvaMountainTrueValueTest(1.0,
		90, 100, 110, 120, 10, 10);

	//ConvergenceTest seed 1, pathNum = regNum = 1000 * 2^n, n = 1,..,8
	//Analytic
	cva::cvaForwardAnalyticExposureTest(1.0, 100, 1000,
		1, 8);
	cva::cvaEuropeanAnalyticExposureTest(1.0, 100, 0.0, 1000,
		1, 8);
	cva::cvaMountainAnalyticExposureTest(1.0,
		90, 100, 110, 120, 0.0, 10, 10, 1000, 1, 8);

	//Regression
	cva::cvaForwardRegressionExposureTest(1.0, 100.0,
		1, 1000, 1000, 8, cva::LoopTypeEnum::bothEnum);
	cva::cvaEuropeanRegressionExposureTest(1.0, 100.0, 0.0,
		1, 1000, 1000, 8, cva::LoopTypeEnum::bothEnum);
	cva::cvaMountainRegressionExposureTest(1.0,
		90, 100, 110, 120, 0.0, 10.0, 10, 1, 10000, 10000,
		8, cva::LoopTypeEnum::bothEnum);
	//End ConvergenceTest


	////StaticalTest seed 1, ..., 100, pathNum = regNum = 10000 fix
	////Analytic Exposure
	//cva::cvaForwardAnalyticExposureTest(1.0, 100, 1000,
	//	100, 1);
	//cva::cvaEuropeanAnalyticExposureTest(1.0, 100, 0.0, 1000,
	//	100, 1);
	//cva::cvaMountainAnalyticExposureTest(1.0,
	//	110, 120, 130, 140, 0.0, 10, 10, 1000, 100, 1);
	////Regression Exposure
	//cva::cvaForwardRegressionExposureTest(1.0, 100.0,
	//	100, 10000, 10000, 1, cva::LoopTypeEnum::bothEnum);
	//cva::cvaEuropeanRegressionExposureTest(1.0, 100.0, 0.0,
	//	100, 10000, 10000, 1, cva::LoopTypeEnum::bothEnum);
	//cva::cvaMountainRegressionExposureTest(1.0,
	//	110, 120, 130, 140, 0.0, 10.0, 10, 100, 10000, 10000,
	//	1, cva::LoopTypeEnum::bothEnum);
	////End StaticalTest


	//ConvergenceTest seed 1, pathNum = regNum = 1000 * 2^n, n = 1,..,8
	//Analytic
	cva::cvaEuropeanAnalyticExposureTest(1.0, 100, -5.0, 1000,
		1, 1);
	cva::cvaMountainAnalyticExposureTest(1.0,
		90, 100, 110, 120, -0.10, 10, 10, 1000, 8, 1);

	//Regression
	cva::cvaEuropeanRegressionExposureTest(1.0, 100.0, -5.0,
		1, 1000, 1000, 1, cva::LoopTypeEnum::bothEnum);
	cva::cvaMountainRegressionExposureTest(1.0,
		90, 100, 110, 120, -0.10, 10.0, 10, 1, 1000, 1000,
		8, cva::LoopTypeEnum::bothEnum);
	//End ConvergenceTest

	int i = 0;
	std::cin >> i;
	return i;
}