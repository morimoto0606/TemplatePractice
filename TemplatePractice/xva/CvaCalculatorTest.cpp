#include "Test.h"
#include "CvaCalculator.h"

namespace cva {
	void 	calcCvaByRegressionFwdTest()
	{
		std::cout << "CvaCalculatorTest" << std::endl;
		Forward payoff(1.0, -100.0);

		Dual<double> cvaExplicit =
			calcCvaByRegression(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000, shockTypeEnum::undEnum, 1, false);
		std::cout << "cvaExplicit = " << cvaExplicit.value()
			<< ',' << "cvaExplicit deriv = " << cvaExplicit.deriv() << std::endl;

		Dual<double> cvaImplicit =
			calcCvaByRegression(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000, shockTypeEnum::undEnum, 1, true);
		std::cout << "cvaImplict = " << cvaImplicit.value() 
			<< ',' << "cvaImplicit deriv = " << cvaImplicit.deriv() << std::endl;

		Dual<double> cvaFwdAnalyticEx =
			calcCvaByAnalytic(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000, shockTypeEnum::undEnum, 1,
				productTypeEnum::eurEnum, false);
		std::cout << "cvaByAnalyticForwardExplict = " << cvaFwdAnalyticEx.value()
			<< ',' << "cvaByAnalyticForwardExplict deriv = " << cvaFwdAnalyticEx.deriv() << std::endl;

		Dual<double> cvaFwdAnalyticIm =
			calcCvaByAnalytic(
				100, 0.0, 0.3, payoff, 10.0, 10, 1000, 1000, shockTypeEnum::undEnum, 1, 
				productTypeEnum::eurEnum, true);
		std::cout << "cvaByAnalyticForwardImplict= " << cvaFwdAnalyticIm.value()
			<< ',' << "cvaByAnalyticForwardImplict deriv = " << cvaFwdAnalyticIm.deriv() << std::endl;


	}
} //namespace cva