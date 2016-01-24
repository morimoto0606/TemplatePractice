#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

namespace cva {
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
	void calcCvaFwdTest();
	
	void cvaForwardAnalyticExposureTest(const double gearing,
		const double strike);
	void cvaForwardRegressionExposureTest(const double gearing,
		const double strike);	
	void cvaForwardTrueValueTest(const double gearing,
		const double strike);

	void calcCvaEurTest();
	void cvaEuropeanAnalyticExposureTest(const double gearing,
		const double strike);
	void cvaEuropeanRegressionExposureTest(const double gearing,
		const double strike);

	void cvaEuropeanTrueValueTest(const double gearing,
		const double strike);

	void cvaMountainTrueValueTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4);
	void cvaMountainAnalyticExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4);
	void cvaMountainRegressionExposureTest(const double gearing,
		const double strike1, const double strike2,
		const double strike3, const double strike4);


}
#endif