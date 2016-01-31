#include "CvaCalculator.h"
#include "CvaCalculatorByAnalytic.h"
namespace cva {

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