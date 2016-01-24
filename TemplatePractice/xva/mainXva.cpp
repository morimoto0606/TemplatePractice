#include <iostream>
#include "PayOff.h"
#include "Dual.h"
#include "Functions.h"
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/io.hpp>   
#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/make_shared.hpp>
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
	
	//cva::calcCvaFwdTest();
	//cva::calcCvaEurTest();
	
	//cva::cvaForwardTrueValueTest(1.0, 100.0);
	//cva::cvaForwardAnalyticExposureTest(1.0, 100);
	//cva::cvaForwardRegressionExposureTest(1.0, 100);
	
	cva::cvaEuropeanTrueValueTest(1.0, 50.0);
	cva::cvaEuropeanAnalyticExposureTest(1.0, 50.0);
	cva::cvaEuropeanRegressionExposureTest(1.0, 50.0);

	cva::cvaMountainTrueValueTest(1.0,
		110, 120, 130, 140, 10, 10);
	cva::cvaMountainAnalyticExposureTest(1.0,
		110, 120, 130, 140, 10, 10);

	cva::cvaMountainRegressionExposureTest(1.0,
		110, 120, 130, 140, 10.0, 10);

	int i = 0;
	std::cin >> i;
	return i;
}